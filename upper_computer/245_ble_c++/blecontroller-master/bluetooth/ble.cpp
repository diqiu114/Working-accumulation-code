#include "ble.h"
#include <QBluetoothUuid>
#include <QLowEnergyDescriptor>

BLE::BLE(QObject *parent) : QObject(parent)
{
    init();
}

BLE::~BLE()
{
    delete m_LowController;
    delete m_DiscoveryAgent;
    servicesList.clear();
    characterList.clear();
    bleDevicesList.clear();
}

void BLE::init()
{
    m_DiscoveryAgent = new QBluetoothDeviceDiscoveryAgent();
//    m_DiscoveryAgent->setLowEnergyDiscoveryTimeout(4000);
    connect(m_DiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,[=](const QBluetoothDeviceInfo &info){
        if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration){
            qDebug()<<info.name()<<info.address().toString();
            bleDevicesList.append(info);
        }
    });
//    connect(m_DiscoveryAgent, QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error),[=](QBluetoothDeviceDiscoveryAgent::Error error){
//        if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError){
//            qDebug("The Bluetooth is powered off.");
//        }
//        else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError) {
//            qDebug("Writing or reading from the device resulted in an error.");
//        }
//    });

    connect(m_DiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, [=]() {
      if (bleDevicesList.isEmpty())
        qDebug("No Low Energy devices found...");
      else
        qDebug("Scan finished!");
      emit signal_scanFinished();
      isScanning = false;
      m_DiscoveryAgent->stop();
      FundTimer.stop();
    });
    FundTimer.setSingleShot(true);
    FundTimer.setInterval(3000);
    connect(&FundTimer, &QTimer::timeout, this,  [=](){
        if (bleDevicesList.isEmpty())
            qDebug("No Low Energy devices found...");
        else
            qDebug("Scanning timer over!");
        isScanning = false;
        emit m_DiscoveryAgent->finished();
    });

}

//开始扫描设备
void BLE::startScanDevices()
{
    //清空设备列表
    bleDevicesList.clear();
    //开始扫描
    m_DiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    if(m_DiscoveryAgent->isActive()){
        qDebug("Scanning.\n");
        isScanning = true;
        FundTimer.start();
    }
}

//连接设备
void BLE::connectDevice(QString address)
{
    for(auto dev : bleDevicesList){
        if(dev.address().toString() == address){
            nowDevice = dev;
        }
    }
    if(!nowDevice.isValid()){
        qDebug("Not a valid device");
        return;
    }

    servicesList.clear();
    characterList.clear();

    if (m_LowController && previousAddress != nowDevice.address().toString()) {
        m_LowController->disconnectFromDevice();
        delete m_LowController;
        m_LowController = nullptr;
    }

    if (!m_LowController) {
        m_LowController = QLowEnergyController::createCentral(nowDevice);
        connect(m_LowController, &QLowEnergyController::connected,[=](){
            qDebug("Device connect success.");
            m_LowController->discoverServices();
        });
//        connect(m_LowController, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error),[=](QLowEnergyController::Error){
//            qDebug()<<"Error : "+m_LowController->errorString();
//        });
        connect(m_LowController, &QLowEnergyController::disconnected,[=]{
            qDebug("Device disconnected.");
        });
        connect(m_LowController, &QLowEnergyController::serviceDiscovered,[=]{
            //
        });
        connect(m_LowController, &QLowEnergyController::discoveryFinished,[=]{
            qDebug("Services scan finished.");

            servicesUUIDList = m_LowController->services();
            for(auto s : servicesUUIDList){
                qDebug()<<s.toString();
            }
            emit signal_findservicesFinished();
        });
    }

    m_LowController->connectToDevice();
    previousAddress = nowDevice.address().toString();
}

void BLE::connectService(QString uuid)
{
    QLowEnergyService *service = nullptr;

    for(int i=0;i<servicesUUIDList.length();i++)
    {
        if(servicesUUIDList.at(i).toString() == uuid){
            service = m_LowController->createServiceObject(servicesUUIDList.at(i));
        }
    }

    if (!service)
        return;
    characterList.clear();


    if (service->state() == QLowEnergyService::DiscoveryRequired) {
        connect(service, &QLowEnergyService::stateChanged,this, &BLE::serviceDetailsDiscovered);
        service->discoverDetails();
        return;
    }

}

// 搜寻状态
void BLE::serviceDetailsDiscovered(QLowEnergyService::ServiceState newState)
{
    qDebug()<<"State : "<<newState;

    if (newState != QLowEnergyService::ServiceDiscovered) {
//        if (newState != QLowEnergyService::DiscoveringServices) {

//        }
        return;
    }
//    搜寻完成，对应的是服务详情（也就是特性值发现完成），
    service = qobject_cast<QLowEnergyService *>(sender());
    if (!service){
        return;
    }

    QLowEnergyCharacteristic hrChar = service->characteristic(QBluetoothUuid(quint16(0xff01)));
    if(!hrChar.isValid()) {
        qDebug() << "characteristic 0xfff1 error:::";
    }
    // 监听数据使能
    QLowEnergyDescriptor m_notificationDesc = hrChar.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
    if (m_notificationDesc.isValid()) {
        if(hrChar.properties() & QLowEnergyCharacteristic::Notify) {
            qDebug() << "";
        }
        service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
    }
    //BLE设备特征值改变，监听时，若有数据返还会触发槽
    connect(service, &QLowEnergyService::characteristicChanged,[=](const QLowEnergyCharacteristic &c, const QByteArray &value){
        QString Charuuid = c.uuid().toString();
        QString Value = value.toHex();
        qDebug()<<"BLE设备-"+Charuuid+"特性值发生变化："+ Value;
        // 保存数据
        this->SaveReceiveDate(value);
        // 产生信号
        emit signal_hasDateReceived();
    });
    //当特征读取请求成功返回其值时，发出此信号。
    connect(service,&QLowEnergyService::characteristicRead,[=](const QLowEnergyCharacteristic &c, const QByteArray &value){
        QString Charname = c.uuid().toString();
        QString Value = value.toHex();
        qDebug()<<"BLE设备-"+Charname+"特性值读取到的值："+ Value;
    });
    //当特性值成功更改为newValue时，会发出此信号。
    connect(service,&QLowEnergyService::characteristicWritten,[=](const QLowEnergyCharacteristic &c, const QByteArray &value){
        QString Charname = c.uuid().toString();
        QString Value = value.toHex();
        qDebug()<<"BLE设备-"+Charname+"特性值成功写入值："+ Value;
    });
    //描述符修改
    connect(service,&QLowEnergyService::descriptorWritten,[=](const QLowEnergyDescriptor &descriptor, const QByteArray &newValue){
        QString Charname = QString("%1").arg(descriptor.name());
        qDebug()<<"BLE设备-"+Charname+"描述符成功写入值："+ QString(newValue);
    });
    //各种错误信息
//    connect(service, static_cast<void(QLowEnergyService::*)(QLowEnergyService::ServiceError)>(&QLowEnergyService::error),
//            [=](QLowEnergyService::ServiceError newErrorr)
//    {
//        if(QLowEnergyService::NoError == newErrorr){
//            qDebug()<<"没有发生错误。\n";
//        }
//        if(QLowEnergyService::OperationError==newErrorr){
//            qDebug()<<"错误: 当服务没有准备好时尝试进行操作!\n";
//        }
//        if(QLowEnergyService::CharacteristicReadError==newErrorr){
//            qDebug()<<"尝试读取特征值失败!\n";
//        }
//        if(QLowEnergyService::CharacteristicWriteError==newErrorr){
//            qDebug()<<"尝试为特性写入新值失败!\n";
//        }
//        if(QLowEnergyService::DescriptorReadError==newErrorr){
//            qDebug()<<"尝试读取描述符值失败!\n";
//        }
//        if(QLowEnergyService::DescriptorWriteError==newErrorr){
//            qDebug()<<"尝试向描述符写入新值失败!\n";
//        }
//        if(QLowEnergyService::UnknownError==newErrorr){
//            qDebug()<<"与服务交互时发生未知错误!\n";
//        }
//    });

    characterList = service->characteristics();
    emit signal_findcharsFinished();

    for(auto s : characterList){
        qDebug()<<s.uuid();
    }

    for (const QLowEnergyCharacteristic &ch : characterList) {
        if(ch.isValid()){
            if(ch.properties() & QLowEnergyCharacteristic::Notify){
//                QLowEnergyDescriptor notice = ch.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
//                if(notice.isValid()){
//                    service->writeDescriptor(notice,QByteArray::fromHex("0100"));
//                }
            }

            if(ch.properties() & QLowEnergyCharacteristic::WriteNoResponse ||  ch.properties() & QLowEnergyCharacteristic::Write){
                QByteArray arr;
                arr.resize(20);
                for(int i=0;i<20;i++){
                    arr[i] = static_cast<char>(i);
                }

                service->writeCharacteristic(ch,arr);
            }
            if(ch.properties() & QLowEnergyCharacteristic::Read){
                service->readCharacteristic(ch);
            }
        }
    }
}

void BLE::convertStringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    byteData.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = convertCharToHex(hstr);
        lowhexdata = convertCharToHex(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}


//-----------
char BLE::convertCharToHex(char ch)
{
    if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
    else return (-1);
}

void BLE::SendMsg(QString text)
{
    if (!service){
        return;
    }
    QByteArray arr;
    arr.resize(20);
    this->convertStringToHex(text, arr);

    characterList = service->characteristics();
    for (const QLowEnergyCharacteristic &ch : characterList) {
        if(ch.isValid()){
            if(ch.properties() & QLowEnergyCharacteristic::WriteNoResponse || ch.properties() & QLowEnergyCharacteristic::Write){
//                arr = text.toLocal8Bit;
                service->writeCharacteristic(ch,arr);
                qDebug() << arr;
                break;
            }
        }
    }
}

void BLE::SendMsg(QByteArray Date)
{
    characterList = service->characteristics();
    for (const QLowEnergyCharacteristic &ch : characterList) {
        if(ch.isValid()){
            if(ch.properties() & QLowEnergyCharacteristic::WriteNoResponse || ch.properties() & QLowEnergyCharacteristic::Write){
                service->writeCharacteristic(ch,Date);
                qDebug() << Date;
                break;
            }
        }
    }
}

void BLE::SaveReceiveDate(QByteArray Date)
{
    this->ReceiveDate = Date;
}

QByteArray BLE::GetReceiveDate()
{
    return this->ReceiveDate;
}
