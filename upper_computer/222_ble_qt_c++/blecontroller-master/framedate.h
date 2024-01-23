#ifndef FRAMEDATE_H
#define FRAMEDATE_H

#include <QObject>

#define DATE_SIZE   13
class FrameDate : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        BAND_Start = 0,
        BAND_698 = BAND_Start,
        BAND_728,   // 下
        BAND_776,    // 223四频没有这个
        BAND_746,   // 下
        BAND_824,
        BAND_869,   // 下
        BAND_1710,
        BAND_2110,  // 下
        BAND_1850,
        BAND_1930,  // 下
        BAND_END,
        BAND_ERROR,
    }Band_t;
    typedef enum
    {
        IdStart = 0,
        RuIdStart = 0,
        Ru_1      = RuIdStart,
        Ru_2,
        RuIdEnd,

        Mu_1 = RuIdEnd,
        IdEnd,
        IdError,
    } RuMuId_t;
    typedef enum
    {
        AisAnswerNull,
        AisBandInfo,
        AisAnswerState,
        AisAnswerEnd,

        AisSetNull = 0x80,
        AisGetInfo,
        AisSetGain,
        AisSetLinkEnable,
        AisSaveDate,
        AisSetEnd,
    } AisCmd_t;
    typedef enum
    {
        BIAddr,
        BiCmd,
        BINameLow8,
        BINameHight8,
        BISignalStrength,
        BILinkState,
        BIMinGain,
        BIMaxGain,
        BIAttVal,
        BIEnableState,
        BILinkGainIng,
    } BandInfoStruct_t;
    typedef enum
    {
        BandNull = 0,
        // 频段状态指示
        BandNorm,
        BandRetainTooLarge,
        BandLargeSing,
        BandClose,
        BandCloseAppSet,    // 手机APP设置
        BandSec,                // 自激震荡
        BandCloseWaitCheck,
        BandCloseRmItt,     //
        // 系统状态指示
        SysWait,                // 这个状态会让APP仍在运行但所有操作停止
        SysNorm,
        SysTest,
        SysStateImd,
        BandStateEnd,
    }BandState_t;
    struct tBandName
    {
        FrameDate::Band_t   EnumName;
        uint16_t NumName;
        QString StrName;
        tBandName() {};
    };
    typedef struct {
        QString Str;
        RuMuId_t EnumId;
    }DeviceName_t;

    typedef struct BandInfo_t
    {
        BandInfo_t() {std::memset(this, NULL, sizeof(BandInfo_t));}
        AisCmd_t Cmd;
        bool SetSucced;

        QString BandNum;
        QString Device;
        int     SingStrength;
        QString LinkState;
        int     MinGain;
        int     MaxGain;
        int     AttVal;
        bool    EnableState;
        int     LinkGainIng;
        bool    InfoHasDate;

    }BandInfo_t;

    struct tBandName BandName[FrameDate::BAND_END];
    DeviceName_t DeviceName[RuMuId_t::IdEnd];
    QString StateName[BandState_t::BandStateEnd];

    explicit FrameDate(QObject *parent = nullptr);
    // 设置频段使能
    QByteArray setEnable(RuMuId_t Id, Band_t Band, bool IsEnable);
    QByteArray getBandInfo(RuMuId_t Id, Band_t Band);
    QByteArray setGain(RuMuId_t Id, Band_t Band, uint8_t Value);
    QByteArray setSaveDate(RuMuId_t Id);
    // 解析数据帧
    // getBandInfo返回帧解析
    BandInfo_t getFrameInfo(QByteArray Date);

signals:

private:
    QString BandList[10];
    QString DeviceList[3];
    bool DevAndBandIsLegal(QString Device, QString Band);
    QString BandReversedOrder(QString Band);
    BandInfo_t BandInfoIng;


    void convertStringToHex(const QString &str, QByteArray &byteData);
    char convertCharToHex(char ch);
    QByteArray frameToDate(QByteArray frame);
};

#endif // FRAMEDATE_H
