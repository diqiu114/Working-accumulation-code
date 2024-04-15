#include "framedate.h"
#include <QDebug>
#include <iostream>

using namespace std;

FrameDate::FrameDate(QObject *parent)
    : QObject{parent}
{
    FrameDate::Band_t Band = FrameDate::BAND_Start;
    Band = FrameDate::BAND_698; BandName[Band].EnumName = FrameDate::BAND_698 , BandName[Band].NumName = 698 , BandName[Band].StrName = "BAND_698";
    Band = FrameDate::BAND_728; BandName[Band].EnumName = FrameDate::BAND_728 ; BandName[Band].NumName = 728 ; BandName[Band].StrName = "BAND_728" ;
    Band = FrameDate::BAND_776; BandName[Band].EnumName = FrameDate::BAND_776 ; BandName[Band].NumName = 776 ; BandName[Band].StrName = "BAND_776" ;
    Band = FrameDate::BAND_746; BandName[Band].EnumName = FrameDate::BAND_746 ; BandName[Band].NumName = 746 ; BandName[Band].StrName = "BAND_746" ;
    Band = FrameDate::BAND_824; BandName[Band].EnumName = FrameDate::BAND_824 ; BandName[Band].NumName = 824 ; BandName[Band].StrName = "BAND_824" ;
    Band = FrameDate::BAND_869; BandName[Band].EnumName = FrameDate::BAND_869 ; BandName[Band].NumName = 869 ; BandName[Band].StrName = "BAND_869" ;
    Band = FrameDate::BAND_1710;BandName[Band].EnumName = FrameDate::BAND_1710; BandName[Band].NumName = 1710; BandName[Band].StrName = "BAND_1710";
    Band = FrameDate::BAND_2110;BandName[Band].EnumName = FrameDate::BAND_2110; BandName[Band].NumName = 2110; BandName[Band].StrName = "BAND_2110";
    Band = FrameDate::BAND_1850;BandName[Band].EnumName = FrameDate::BAND_1850; BandName[Band].NumName = 1850; BandName[Band].StrName = "BAND_1850";
    Band = FrameDate::BAND_1930;BandName[Band].EnumName = FrameDate::BAND_1930; BandName[Band].NumName = 1930; BandName[Band].StrName = "BAND_1930";

    // 初始化BandInfoIng
    memset(&BandInfoIng, NULL, sizeof(BandInfoIng));

    FrameDate::RuMuId_t Id = RuMuId_t::IdStart;
    Id = Ru_1;FrameDate::DeviceName[Id].Str = "Ru_1";FrameDate::DeviceName[Id].EnumId = Id;
    Id = Ru_2;FrameDate::DeviceName[Id].Str = "Ru_2";FrameDate::DeviceName[Id].EnumId = Id;
    Id = Mu_1;FrameDate::DeviceName[Id].Str = "Mu_1";FrameDate::DeviceName[Id].EnumId = Id;

    FrameDate::BandState_t State = BandState_t::BandNull;
    State = BandNull            ; StateName[State] = "BandNull"                        ;
    State = BandNorm            ; StateName[State] = "BandNorm"                        ;
    State = BandRetainTooLarge  ; StateName[State] = "BandRetainTooLarge"              ;
    State = BandLargeSing       ; StateName[State] = "BandLargeSing"                   ;
    State = BandClose           ; StateName[State] = "BandClose"                       ;
    State = BandCloseAppSet     ; StateName[State] = "BandCloseAppSet"                 ;
    State = BandSec             ; StateName[State] = "BandSec"                      ;
    State = BandCloseWaitCheck  ; StateName[State] = "BandCloseWaitCheck"              ;
    State = BandCloseRmItt      ; StateName[State] = "BandCloseRmItt"                ;
    State = SysWait             ; StateName[State] = "SysWait"                  ;
    State = SysNorm             ; StateName[State] = "SysNorm"                         ;
    State = SysTest             ; StateName[State] = "SysTest"                         ;
    State = SysStateImd         ; StateName[State] = "SysStateImd"                     ;
    State = BandStateEnd        ; StateName[State] = "BandStateEnd"                  ;
}

QByteArray FrameDate::setEnable(RuMuId_t Id, Band_t Band, bool IsEnable)
{
    QByteArray RetVal;
    RetVal.resize(13);
    for(qsizetype i = 0; i < 13; i++) {
        RetVal[i] = 0;
    }
    qsizetype i = 0;
    int id = Id;
    uint8_t bandHight = this->BandName[Band].NumName >> 8;
    uint8_t bandLow = this->BandName[Band].NumName & 0xff;
    uint8_t enable = IsEnable;
    uint8_t Cmd = this->AisSetLinkEnable;
    RetVal[i] = id;
    RetVal[++i] = Cmd;
    RetVal[++i] = bandLow;
    RetVal[++i] = bandHight;
    RetVal[++i] = enable;
    qDebug() << __FUNCTION__<< "输出信息:" <<RetVal.toHex();
    return RetVal;
}

QByteArray FrameDate::getBandInfo(RuMuId_t Id, Band_t Band)
{
    QByteArray RetVal;
    RetVal.resize(13);
    for(qsizetype i = 0; i < 13; i++) {
        RetVal[i] = 0;
    }
    qsizetype i = 0;
    int id = Id;
    uint8_t bandHight = this->BandName[Band].NumName >> 8;
    uint8_t bandLow = this->BandName[Band].NumName & 0xff;
    uint8_t Cmd = this->AisGetInfo;
    RetVal[i] = id;
    RetVal[++i] = Cmd;
    RetVal[++i] = bandLow;
    RetVal[++i] = bandHight;
    qDebug() << __FUNCTION__<< "输出信息:" <<RetVal.toHex();
    return RetVal;
}

QByteArray FrameDate::setGain(RuMuId_t Id, Band_t Band, uint8_t Value)
{
    QByteArray RetVal;
    RetVal.resize(13);
    for(qsizetype i = 0; i < 13; i++) {
        RetVal[i] = 0;
    }
    qsizetype i = 0;
    int id = Id;
    uint8_t bandHight = this->BandName[Band].NumName >> 8;
    uint8_t bandLow = this->BandName[Band].NumName & 0xff;
    uint8_t Cmd = this->AisSetGain;
    RetVal[i] = id;
    RetVal[++i] = Cmd;
    RetVal[++i] = bandLow;
    RetVal[++i] = bandHight;
    RetVal[++i] = Value;
    qDebug() << __FUNCTION__<< "输出信息:" <<RetVal.toHex();
    return RetVal;
}

QByteArray FrameDate::setSaveDate(RuMuId_t Id)
{
    QByteArray RetVal;
    RetVal.resize(13);
    for(qsizetype i = 0; i < 13; i++) {
        RetVal[i] = 0;
    }
    qsizetype i = 0;
    int id = Id;
    uint8_t Cmd = this->AisSaveDate;
    RetVal[i] = id;
    RetVal[++i] = Cmd;
    qDebug() << __FUNCTION__<< "输出信息:" <<RetVal.toHex();
    return RetVal;
}

FrameDate::BandInfo_t FrameDate::getFrameInfo(QByteArray Date)
{
    BandInfo_t RetVal;
    QByteArray DetailDate = this->frameToDate(Date);
    QByteArray TestDate = DetailDate;
    if(!TestDate.size()) {
        RetVal.InfoHasDate = false;
        return RetVal;
    }
    switch (DetailDate.at(1)) {
    case AisBandInfo:{
        RetVal.Cmd = AisBandInfo;
    }break;
    case AisAnswerState:{
        RetVal.Cmd = AisAnswerState;
        RetVal.SetSucced = DetailDate.at(4);
        return RetVal;
    }break;
    default : {
        RetVal.InfoHasDate = false;
        return RetVal;
    }
    }
    int DateStartAdd = 0;
    unsigned int TestHight = DetailDate.at(DateStartAdd + BINameLow8);
    unsigned int TestLow = DetailDate.at(DateStartAdd + BINameHight8) << 8;
    int BandNum = (DetailDate.at(DateStartAdd + BINameLow8)&0xFF) +
            (DetailDate.at(DateStartAdd + BINameHight8) << 8);

    for(int Band = BAND_Start; Band < BAND_END; Band++) {
        if(BandNum==BandName[Band].NumName) {
            RetVal.BandNum = BandName[Band].StrName;
            RetVal.Device        = DeviceName[DetailDate.at(DateStartAdd + BIAddr)].Str;
            RetVal.SingStrength  = DetailDate.at(DateStartAdd + BISignalStrength);
            int cnt = DetailDate.at(DateStartAdd + BILinkState);
            RetVal.LinkState     = StateName[cnt];
//            qDebug() << "频段状态数据为：" << DetailDate.toHex().at(DateStartAdd + BILinkState);
            RetVal.MinGain       = DetailDate.at(DateStartAdd + BIMinGain);
            RetVal.MaxGain       = DetailDate.at(DateStartAdd + BIMaxGain);
            RetVal.AttVal        = DetailDate.at(DateStartAdd + BIAttVal);
            RetVal.EnableState   = DetailDate.at(DateStartAdd + BIEnableState);
            RetVal.LinkGainIng   = DetailDate.at(DateStartAdd + BILinkGainIng);
            RetVal.InfoHasDate   = true;
            return RetVal;
        }
    }
//
    return RetVal;
}

bool FrameDate::DevAndBandIsLegal(QString Device, QString Band)
{
    bool flag1;
    bool flag2;
    for(int i = 0; i < sizeof(DeviceList) / sizeof(DeviceList[1]); i++) {
        if(Device==DeviceList[i]) {
            flag1 = true;
        }
    }
    for(int i = 0; i < sizeof(BandList) / sizeof(BandList[1]); i++) {
        if(Band==BandList[i]) {
            flag2= true;
        }
    }

    if(flag1&&flag2) {
        return true;
    } else {
        return false;
    }
}

QString FrameDate::BandReversedOrder(QString Band)
{
    int High = Band.toInt() % 10;
    int Low = Band.toInt() / 10;
    int RetVal = Low * 10 + High;
    return QString::number(RetVal);
}

void FrameDate::convertStringToHex(const QString &str, QByteArray &byteData)
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
char FrameDate::convertCharToHex(char ch)
{
    if((ch >= '0') && (ch <= '9'))
         return ch-0x30;
     else if((ch >= 'A') && (ch <= 'F'))
         return ch-'A'+10;
     else if((ch >= 'a') && (ch <= 'f'))
         return ch-'a'+10;
    else return (-1);
}

// 去掉帧头帧尾，如果返回size为0，则帧错误
QByteArray FrameDate::frameToDate(QByteArray frame)
{
    int cntMax = frame.size();
    int CntHeadStart = 0;
    int CntTailEnd = 0;
    int stateForLoop = 0;
    int status = 0;
    QByteArray RetVal;
    do {
        switch (status)
        {
            case (0):
            {
                if (frame[CntHeadStart] == 'a')
                {
                    status = 1;
                }
            }
            break;

            case (1):
            {
                if (frame[CntHeadStart] == 't')
                {
                    status = 2;
                }
                else if (frame[CntHeadStart] == 'a')
                {
                    status = 1;
                }
                else
                {
                    status = 0;
                }
            }
            break;

            case (2):
            {
                if (frame[CntHeadStart] == '+')
                {
                    status = 3;
                }
                else if (frame[CntHeadStart] == 'a')
                {
                    status = 1;
                }
                else
                {
                    status = 0;
                }
            }
            break;

            case (3):
            {
                status = 4;
            }
            break;

            default:
            {
                break;
            }
        }
        CntHeadStart++;
        // 帧头匹配完成
        if(status==4) {
            // 跳过'A'
            CntHeadStart += 1;
            CntTailEnd = CntHeadStart;
            do {
                static uint8_t EndState;
                switch(frame[CntTailEnd]) {
                    case '\r': {
                        EndState = 1;
                    }break;
                    case '\n': {
                        if(EndState==1) {
                            EndState = 2;
                        } else {
                            EndState = 0;
                        }
                    }break;
                    default: {
                        EndState = 0;
                    }break;
                }
                CntTailEnd++;
                if(EndState==2) {
                    CntTailEnd -= 2; // 回车换行两个字符
                    break;
                }
            }while(--cntMax);
            break;
        }
    } while(--cntMax);

    if(CntHeadStart && (CntTailEnd > CntHeadStart)) {
        RetVal.resize(CntTailEnd - CntHeadStart);
        int j = 0;
        for(qsizetype i = CntHeadStart; i < CntTailEnd; i++) {
            RetVal[j] = frame.at(i);
            j++;
        }
        return RetVal;
    } else {
        RetVal.resize(0);
        return RetVal;
    }
}


