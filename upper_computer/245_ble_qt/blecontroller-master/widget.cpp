#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QMessageBox>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_ble = new BLE(this);
    pFrameDate = new FrameDate(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_scan_clicked()
{
    // 考虑做一个正在扫描的提示
    connect(m_ble,&BLE::signal_scanFinished,[=]{
        auto list = m_ble->getDevices();
        if(list.isEmpty())
            return ;
        ui->listWidget_dev->clear();
        ui->listWidgetBleName->clear();
        for(auto s : list){
            ui->listWidget_dev->addItem(s.address().toString());
            ui->listWidgetBleName->addItem(s.name());
        }
    });

    ui->listWidgetBleName->clear();
    ui->listWidget_character_7->clear();
    ui->listWidget_character_8->clear();
    ui->listWidget_dev->clear();
    ui->listWidget_services->clear();
    if(!m_ble->getScanning())
        m_ble->startScanDevices();
}


void Widget::on_pushButton_connect_clicked()
{
    connect(m_ble,&BLE::signal_findservicesFinished,[=]{
        auto list = m_ble->getServicesUUID();
        if(list.isEmpty())
            return ;
        ui->listWidget_services->clear();
        for(auto s : list){
            ui->listWidget_services->addItem(s.toString());
        }
    });

    m_ble->connectDevice(ui->listWidget_dev->currentItem()->text());
}

void Widget::on_pushButton_service_clicked()
{
    connect(m_ble,&BLE::signal_findcharsFinished,[=]{
        auto list = m_ble->getChars();
        if(list.isEmpty())
            return ;
        ui->listWidget_character_7->clear();
        for(auto s : list){
            if(s.uuid().toString()=="{0000fff2-0000-1000-8000-00805f9b34fb}") {
               ui->listWidget_character_7->addItem("设置数据");
            } else if(s.uuid().toString()=="{0000fff1-0000-1000-8000-00805f9b34fb}") {
                ui->listWidget_character_7->addItem("读取数据数据");
            } else
                ui->listWidget_character_7->addItem(s.uuid().toString());
            ui->listWidget_character_8->addItem(s.uuid().toString());
        }
        // 连接接收数据
        connect(m_ble,&BLE::signal_hasDateReceived, this, &Widget::activeDataReception);
    });
    m_ble->connectService(ui->listWidget_services->currentItem()->text());
}

void Widget::on_pushButtonGetBandInfo_clicked()
{
    FrameDate::RuMuId_t Device = this->whichDeviceInCheckBoxSelected();
    FrameDate::Band_t Band = this->whichBandInCheckBoxSelected();
    if(Band==FrameDate::BAND_ERROR) {
        return;
    }
    if(Device==FrameDate::IdError) {
        return;
    }
    QByteArray OutDate;
    OutDate = this->AddFrameHeadAndTail(pFrameDate->getBandInfo(Device, Band));
    qDebug() << "开始获取信息信息帧为：" << OutDate.toHex();
    m_ble->SendMsg(OutDate);
    ui->lineEditBand->clear();
    ui->lineEditBandEnable->clear();
    ui->lineEditBandGain->clear();
    ui->lineEditBandState->clear();
    ui->lineEditMaxGain->clear();
    ui->lineEditMinGain->clear();
    ui->lineEditDeviceNow->clear();
    ui->lineEditSignalStrength->clear();

}

bool Widget::txBandIsLegal(QString Str)
{
    const QString BandList[] = {
        "2110",
        "728",
    };
    for(int cnt = 0; cnt < sizeof(BandList) / sizeof(BandList[1]); cnt++) {
        if(Str==BandList[cnt])
            return true;
    }
    return false;
}

bool Widget::txDiverIsLegal(QString Str)
{
    const QString DiverList[] = {
        "Mu",
        "Ru1",
        "Ru2",
    };
    for(int cnt = 0; cnt < sizeof(DiverList) / sizeof(DiverList[1]); cnt++) {
        if(Str==DiverList[cnt])
            return true;
    }
    return false;
}

FrameDate::Band_t Widget::whichBandInCheckBoxSelected()
{
    if(ui->checkBox_BAND_698->isChecked()) {
        return FrameDate::BAND_698;
    }
    if(ui->checkBox_BAND_728->isChecked()) {
        return FrameDate::BAND_728;
    }
    if(ui->checkBox_BAND_776->isChecked()) {
        return FrameDate::BAND_776;
    }
    if(ui->checkBox_BAND_746->isChecked()) {
        return FrameDate::BAND_746;
    }
    if(ui->checkBox_BAND_824->isChecked()) {
        return FrameDate::BAND_824;
    }
    if(ui->checkBox_BAND_869->isChecked()) {
        return FrameDate::BAND_869;
    }
    if(ui->checkBox_BAND_1710->isChecked()) {
        return FrameDate::BAND_1710;
    }
    if(ui->checkBox_BAND_2110->isChecked()) {
        return FrameDate::BAND_2110;
    }
    if(ui->checkBox_BAND_1850->isChecked()) {
        return FrameDate::BAND_1850;
    }
    if(ui->checkBox_BAND_1930->isChecked()) {
        return FrameDate::BAND_1930;
    }
    QMessageBox::warning( this, tr("警告"), tr("没有频段选中"),
                         ::QMessageBox::Yes);//弹出警告窗口
    return FrameDate::BAND_ERROR;
}

FrameDate::RuMuId_t Widget::whichDeviceInCheckBoxSelected()
{
    if(ui->checkBox_Mu->isChecked()) {
        return FrameDate::Mu_1;
    }
    if(ui->checkBox_Ru1->isChecked()) {
        return FrameDate::Ru_1;
    }
    if(ui->checkBox_Ru2->isChecked()) {
        return FrameDate::Ru_2;
    }
    QMessageBox::warning( this, tr("警告"), tr("没有设备选中"),
                         ::QMessageBox::Yes);//弹出警告窗口
    return FrameDate::IdError;
}

QByteArray Widget::AddFrameHeadAndTail(QByteArray Date)
{
    QByteArray DateTemp;
    DateTemp.resize(13);
    for(qsizetype i = 0; i < 13; i++) {
        DateTemp[i] = Date.at(i);
    }
    QByteArray RetVal;
    RetVal += "at+A,";
    RetVal += DateTemp;
    RetVal += "\r\n";

    return RetVal;
}

// 接收到数据
void Widget::activeDataReception()
{
    QByteArray Date = m_ble->GetReceiveDate();
    qDebug() <<__FUNCTION__ << "out date:" << Date.toHex();
    FrameDate::BandInfo_t BandInfo = pFrameDate->getFrameInfo(Date);
    switch(BandInfo.Cmd) {
    case FrameDate::AisCmd_t::AisBandInfo: {
        ui->lineEditDeviceNow->setText(BandInfo.Device);
        ui->lineEditBand->setText(BandInfo.BandNum);
        if(BandInfo.EnableState) {
            ui->lineEditBandEnable->setText("打开状态");
        } else {
            ui->lineEditBandEnable->setText("关闭状态");
        }
        ui->lineEditBandState->setText(BandInfo.LinkState);
        ui->lineEditBandGain->setText(QString::number(BandInfo.LinkGainIng, 10));
        ui->lineEditMaxGain->setText(QString::number(BandInfo.MaxGain, 10));
        ui->lineEditMinGain->setText(QString::number(BandInfo.MinGain, 10));
        ui->lineEditSignalStrength->setText(QString::number(BandInfo.SingStrength, 10));
    }break;
    case FrameDate::AisCmd_t::AisAnswerState: {
        if(BandInfo.SetSucced) {
//            QMessageBox::information(this, "提示","设置成功");.
            ui->lineEditSetSucceed->setText("设置成功");
        } else {
            ui->lineEditSetSucceed->setText("设置失败");
//            QMessageBox::information(this, "提示","设置失败");
        }
    }break;
    default: {
        return;
    }
    }
}

void Widget::on_pushButtonGainSet_clicked()
{
    FrameDate::RuMuId_t Device = this->whichDeviceInCheckBoxSelected();
    FrameDate::Band_t Band = this->whichBandInCheckBoxSelected();
    ui->lineEditSetSucceed->clear();
    if(Band==FrameDate::BAND_ERROR) {
        return;
    }
    if(Device==FrameDate::IdError) {
        return;
    }
    uint8_t SetGainValue = ui->spinBoxSetGain->value();
    QByteArray SendVal = this->AddFrameHeadAndTail(pFrameDate->setGain(Device, Band, SetGainValue));
    m_ble->SendMsg(SendVal);
}

// 使能频段
void Widget::on_pushButtonEnableSet_clicked()
{
    FrameDate::RuMuId_t Device = this->whichDeviceInCheckBoxSelected();
    FrameDate::Band_t Band = this->whichBandInCheckBoxSelected();
    ui->lineEditSetSucceed->clear();
    if(Band==FrameDate::BAND_ERROR) {
        return;
    }
    if(Device==FrameDate::IdError) {
        return;
    }
    bool BandEnable;
    QByteArray OutDate;
    if(ui->checkBoxEnableSet->isChecked()) {
        BandEnable = true;
        qDebug() << "ChecBoxLinkEnable";
    } else {
        BandEnable = false;
        qDebug() << "ChecBoxLinkDisable";
    }
    OutDate = this->AddFrameHeadAndTail(pFrameDate->setEnable(Device, Band, BandEnable));
    qDebug() << OutDate.toHex();
    m_ble->SendMsg(OutDate);
}

void Widget::on_pushButtonSave_clicked()
{
    FrameDate::RuMuId_t Device = this->whichDeviceInCheckBoxSelected();
    FrameDate::Band_t Band = this->whichBandInCheckBoxSelected();
    ui->lineEditSetSucceed->clear();
    if(Band==FrameDate::BAND_ERROR) {
        return;
    }
    if(Device==FrameDate::IdError) {
        return;
    }
    QByteArray SendVal = this->AddFrameHeadAndTail(pFrameDate->setSaveDate(Device));
    m_ble->SendMsg(SendVal);
}

