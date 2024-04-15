# Qt中低功耗蓝牙模块使用

 发表于 2017-07-29 | 分类于 [c++ ](https://fsp1yjl.github.io/categories/c/)| [0 Comments](https://fsp1yjl.github.io/2017/07/29/2017Qt中低功耗蓝牙模块使用/#comments)

最近在Qt下使用opencv库，进行一些图像识别和处理相关的工作，主要是通过摄像头采集运动采样视频，然后进行一些跑姿分析和稳定性测试。但仅仅从视频帧来分析，还是有很多缺陷，后来就想着，如果结合公司的智能鞋垫产品，获取跑步实时的脚上各个部位的压力数据可以对视频分析提供很大的数据补充。跟硬件组的小伙伴聊了聊，得知可以通过蓝牙通讯，配对后实时获取鞋垫压力数据。从小伙伴那里搞来一套鞋垫样品，并拿了一份通讯协议列表，就抓紧搞起了。
得益于Qt详尽的文档说明，对照Qt官方[Bluetooth Low Enegy文档](http://doc.qt.io/qt-5/qtbluetooth-le-overview.html),再结合一下官网的例子，断断续续搞了一天，算是在我的客户端程序里看到鞋垫传过来的压力数据了。官网的文档流程讲得很清楚，这里自己还是给整个通讯的流程梳理一下。



> 1. 搜寻附近全部的蓝牙设备
> 2. 根据搜寻出的蓝牙设备信息，筛选出要连接的蓝牙设备进行连接
> 3. 建立连接后，去获取该蓝牙设备等services列表，根据约定好的服务uuid筛选出自己需要的服务
> 4. 发现对应的服务后，根据约定好的服务下characteristic特性id,创建特征对象，并监听特征对象内容的变化
> 5. 向客户端特征配置对象写入特征生效消息，开始接收外围蓝牙设备。

蓝牙模块代码如下：
bluedevice.h

```c++
#ifndef BLUEDEVICE_H
#define BLUEDEVICE_H
#include <QObject>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothDeviceInfo>
#include<QBluetoothUuid>
#include<QBluetoothServiceInfo>
#include<QLowEnergyController>
#include<QLowEnergyService>
#include<QLowEnergyDescriptor>
class BlueDevice: public QObject{
    Q_OBJECT
public:

    BlueDevice();
    QString getAddress(QBluetoothDeviceInfo device) const;
private:
        QList<QBluetoothDeviceInfo> device_list;  //存放搜索到到蓝牙设备列表
        QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;  //设备搜索对象
        QLowEnergyController *m_controler;   //单个蓝牙设备控制器
        QLowEnergyService *m_service; //服务对象实例
};

#endif // BLUEDEVICE_H
```



bluedevice.cpp

```c++
#include "bluedevice.h"
#include <QDebug>
#include<QTimer>

BlueDevice::BlueDevice() {
    qDebug() << "enter bludedevice constructor....";

    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    //每次发现新设备时触发
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this ,[this]() {
        qDebug() << "find a new bluebooth device";
    });
    
    //蓝牙设备搜索完成后，筛选出目标设备进行连接，并进行相关信号与槽函数的绑定
    connect(m_deviceDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::finished, this, [this]() {
        device_list = this->m_deviceDiscoveryAgent->discoveredDevices();

        //遍历显示设备详情
        QList<QBluetoothDeviceInfo>::iterator it;
        for(it=device_list.begin(); it != device_list.end(); it++) {
            
            // 外围蓝牙设备对象
            QBluetoothDeviceInfo tmp_device = *it;  
            QString device_name = tmp_device.name();
            //qDebug() <<"device name:::" << device_name;
            //qDebug() << "device address:::" << this->getAddress(tmp_device);
            
           //打印搜索出来的全部低功耗蓝牙
           if (tmp_device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
                qDebug() << " low Energy device ....";
                qDebug() <<"22222device name:::" << device_name;
              }
            
            //正则匹配目标设备，
            QString pattern_str = "^Eric.*";  //qt中正则匹配任意个字符，需要使用.*而不是*
            QRegExp rx(pattern_str);
            if(!rx.exactMatch(device_name)) {
                continue;
            }
            qDebug() <<"device name:::" << device_name;
            qDebug() << "device address:::" << this->getAddress(tmp_device);

            // 创建蓝牙设备控制器对象 
            m_controler = new QLowEnergyController(tmp_device, this);
            
            // 监听目标设备连接成功消息，连接成功后，搜索目标设备等服务列表
            connect(m_controler, &QLowEnergyController::connected, this, [this](){
                qDebug() << "m_controler connected ......";
                //必须要在连接建立后 执行开始寻找service的函数 
                //之前调试，就是因为没有在设备连接后主动请求获取服务列表信息，后续监听便没有触发
                m_controler->discoverServices();
            });
            
            // 监听发现服务消息，如果服务的uuid 为约定好的要使用服务类型，则进行后续处理
            connect(m_controler,&QLowEnergyController::serviceDiscovered, this, [this](QBluetoothUuid serviceUuid) {
                if(serviceUuid == QBluetoothUuid( quint16(0xffd0))) {  //我们用的服务类型是0xffd0对应的uuid
                    
                    //发现匹配的服务后，使用控制器对象创建服务对象
                    m_service = m_controler->createServiceObject(serviceUuid,this);
                    if(m_service) {

                        // 服务对象创建成功后，坚挺服务状态变化，如果状态变成已发现，则进行后续服务下特征对象获取
                        connect(m_service,&QLowEnergyService::stateChanged, this, [this]() {
                            qDebug() << "service state change" << m_service->state() << ",||||||";

                            //发现服务, 建立characteristic对象实例
                            if(m_service->state() == QLowEnergyService::ServiceDiscovered) {
                                QLowEnergyCharacteristic hrChar = m_service->characteristic(QBluetoothUuid(quint16(0xfff6)));
                                if(!hrChar.isValid()) {
                                    qDebug() << "characteristic fff6 error:::";
                                }
                                // 设置特征对象可用
                                //enable the chracteristic notification by write 0x01 to client characteristic configuration
                                QLowEnergyDescriptor m_notificationDesc = hrChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                                if (m_notificationDesc.isValid()) {
                                    if(hrChar.properties() & QLowEnergyCharacteristic::Notify) {
                                        qDebug() << "";
                                    }
                                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                                }
                            }
                        });

                        // 通过监听特征对象的变化，不断获得鞋垫压力数据。 
                        connect(m_service,&QLowEnergyService::characteristicChanged, this,
                                [this](QLowEnergyCharacteristic c,QByteArray value) {
                                    qDebug() << "characteristicChanged state change::" <<c.uuid()<< ",||||||";
                                    qDebug() << "value length::" << value.length();
                                    qDebug() << "value length::" << value;

                                    QByteArray sub_1 = value.mid(0,2);
                                    QByteArray sub_2 = value.mid(2,2);
                                    QByteArray sub_3 = value.mid(4,2);

                                    bool ok;
                                    // num 1,2,3  分别对应三个压力感应点的压力值
                                    int num_1 =  QString(sub_1.toHex()).toInt(&ok,16);
                                    qDebug() << "num_1:::" << num_1;
                                    int num_2 =  QString(sub_2.toHex()).toInt(&ok,16);
                                    qDebug() << "num_1:::" << num_2;
                                    int num_3 =  QString(sub_3.toHex()).toInt(&ok,16);
                                    qDebug() << "num_1:::" << num_3;

                                }
                        );
                        
                        // 触发服务详情发现函数 ，不要忘记调用
                        m_service->discoverDetails();
                    }
                }
            });

            connect(m_controler,&QLowEnergyController::discoveryFinished, this, [this]() {
                qDebug() << "finish service discovery";
            });

            //连接外围设备
            m_controler->connectToDevice();

            //QTimer *timer = new QTimer(this);
            //connect(timer, &QTimer::timeout, this, [this](){ qDebug() <<"state:::" <<  this->m_controler->state();});
            //timer->start(1000);
        }
    });
   
    // 开始外围设备搜索
    m_deviceDiscoveryAgent->start();

}

// mac和其他系统上address获取有少许差异，参见官方文档
QString BlueDevice::getAddress(QBluetoothDeviceInfo device) const
{
#ifdef Q_OS_MAC
    // On OS X and iOS we do not have addresses,
    // only unique UUIDs generated by Core Bluetooth.
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

//void BlueDevice::getNewService(QBluetoothServiceInfo info) {
//    qDebug() << "ppppp uuuuuuuuuu";
//}
```



tips:
1.要使用qt蓝牙模块, 项目的 .pro要声明使用
2.有了lambda函数后，不用再一个个声明和创建具名槽函数的感觉挺好，就是代码成一坨了
3.虽然说是低功耗蓝牙，但还是要记得用完后断开和外设店连接，之前忘记断开，一晚上一个纽扣电池的点就被耗光了
4.[GATT Profile 简介](https://www.race604.com/gatt-profile-intro)

[# Qt](https://fsp1yjl.github.io/tags/Qt/) [# 低功耗蓝牙](https://fsp1yjl.github.io/tags/低功耗蓝牙/)

[《人类简史》一读杂记](https://fsp1yjl.github.io/2017/07/13/2017《人类简史》一读杂记/)

<iframe id="dsq-app840" name="dsq-app840" allowtransparency="true" frameborder="0" scrolling="no" tabindex="0" title="Disqus" width="100%" src="https://disqus.com/recommendations/?base=default&amp;f=buqisuitu&amp;t_u=https%3A%2F%2Ffsp1yjl.github.io%2F2017%2F07%2F29%2F2017Qt%25E4%25B8%25AD%25E4%25BD%258E%25E5%258A%259F%25E8%2580%2597%25E8%2593%259D%25E7%2589%2599%25E6%25A8%25A1%25E5%259D%2597%25E4%25BD%25BF%25E7%2594%25A8%2F&amp;t_d=%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20Qt%E4%B8%AD%E4%BD%8E%E5%8A%9F%E8%80%97%E8%93%9D%E7%89%99%E6%A8%A1%E5%9D%97%E4%BD%BF%E7%94%A8%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20&amp;t_t=%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20Qt%E4%B8%AD%E4%BD%8E%E5%8A%9F%E8%80%97%E8%93%9D%E7%89%99%E6%A8%A1%E5%9D%97%E4%BD%BF%E7%94%A8%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20#version=3b8336c2a620b47aa2fac91f7787d2b1" horizontalscrolling="no" verticalscrolling="no" style="width: 660px; border: none !important; overflow: hidden !important; height: 270px !important; display: inline !important; box-sizing: border-box !important;"></iframe>