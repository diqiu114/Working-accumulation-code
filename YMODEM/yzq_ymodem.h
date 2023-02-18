/*
 * @Date: 2022-08-17 14:25:54
 * @Autor: YangZhiQiang
 * @LastEditors: YangZhiQiang
 * @Description: 
 * @CodingFormat: gb2312
 * @LastEditTime: 2022-08-29 08:46:45
 * @FilePath: yzq_ymodem.h
 * @Else: 
 */
#ifndef __YZQ_YMODEM_H
#define __YZQ_YMODEM_H

#define SOH_Y   ((uint8_t)0x01)
#define STX_Y   ((uint8_t)0x02)
#define EOT_Y   ((uint8_t)0x04)
#define ACK_Y   ((uint8_t)0x06)
#define NAK_Y   ((uint8_t)0x15)
#define CAN_Y   ((uint8_t)0x18)
#define CHARC_Y 'C'

#define YTYPE_SIZE              1u
#define YSEQ_SIZE               1u
#define YSEQOC_SIZE             1u
#define YDATE_SIZE_1K           1024u
#define YDATE_SIZE_128          128u
#define YCRCH_SIZE              1u
#define YCRCL_SIZE              1u

#define Y_ARRAY_SIZE(x)     (sizeof(x) / sizeof(x)[0])
    
// 环形缓冲长度
#define H_BUFF_LENGTH       1500
// 握手信号'C'循坏发送间隔时间
#define YReceiveDateDelay   500     

// 接收超时时间
//#define TIME_OUT                    3000 // 3000个Tick单位，这里1个tick为1ms
// 握手超时时间3000个Tick单位，这里1个tick为1ms
#define SHAKE_HANDS_TIME_OUT        3000    
// 接收数据超时时间1000个Tick单位，这里1个tick为1ms
#define REC_TIME_OUT                1000
// 接收结束数据标志超时时间，这里1个tick为1ms
#define YREC_EOT_TIME_OUT           2000   

// 传输完成打印一些信息 uint8_t* Str = REC_COMMPLE_INFO;
#define REC_COMMPLE_INFO    "传输完成,这里可以打印一些信息\r\n"
// 错误后回复NAK的最大次数
#define NAK_ERROR_MAX_CNT   10

#include "stdint.h"

typedef enum
{
    Hdisable = 0,
    Henable,
    HWhatStatus,
}t_UserStateH;

// 状态记录时间线
typedef enum
{
    TOld = 0,
    TNow,
    TNum,
}t_TimeLine;

// 错误类型
typedef enum 
{
    YERROR_NotErro = 0,
    YERROR_Crc, 
    YERROR_FileName,
    YERROR_NoPack,
    // 帧序与帧序取反对应不上
    YERROR_FrameSequen,
    // 下帧==上帧++
    YERROR_FrameSort,
    YERROR_OutTime,
    // 接收数据后回调产生错误
    YERROR_RecHandle,
    YERROR_Can,
    YERROR_Nak,
    YERROR_EndRec,
}t_YERROR;

// 接收状态
typedef enum
{
    YREC_Ready= 0,
    YREC_Buffer,
    YREC_NextPack,
    YREC_First,
    // 正式接收
    YREC_Norm,
    YREC_Eot,
    YREC_EndRec,
    YREC_Erro,
    YREC_Nak
}t_ReceiveState;

typedef struct 
{
	uint8_t  DateBuffer[H_BUFF_LENGTH];
	uint8_t  FullCacheFlag:1;
	uint8_t  CachHaveDate:1;
	uint16_t Head;
	uint16_t Tail;
}t_ReceiveCach;

typedef struct 
{
   uint16_t YTypeLoca:1;        // 0
   uint16_t YSeqLoca:1;         // 1
   uint16_t YSeqOcLoca:2;        // 0x0002
   uint16_t YDateLoca:2;          // 0x0003
   uint16_t YCrchLoca:11;          // 0x0403
   uint16_t YCrclLoca:11;          // 0x0404
   uint16_t YDatelen:11;           // 0x0400
   uint16_t YPackLen:11;           // 0x0405
}t_PacketStru;

// // 本结构体的位域还没有完善，不使用该方法，丢弃
// typedef struct 
// {
//     uint8_t     YType:2;
//     uint8_t     YSeq:2;
//     uint8_t     YSeqOC;
//     uint16_t    YDateLength;
//     uint16_t    YCRC;
//     uint8_t     YData[YDATE_SIZE_1K];
// }t_YmodemRec;

// 必须调用，否则接收不到数据
int H_WriteCach(uint8_t* pDate, uint16_t DateSize);
// 必须调用，否则无法产生时间戳
void YTick(void);
// 必须调用，此为ymodem协议启动
void YReceiveDate(void);
// 用户必须实现，否则回复不了数据
void YSendChar(uint8_t ch);
// 用户可实现，实现后必须有return且==YERROR_NotErro时协议正常进行此为发生错误的回调
t_YERROR YErroHandle(t_YERROR ErrorClass);
// 用户可实现，该函数为接收头帧文件名后回调，实现后必须有return且==YERROR_NotErro时协议正常进行
t_YERROR YRecFileNameHandle(uint8_t* FileName, uint8_t FileNameSize);
// 用户可实现，该函数为正确接收一帧数据后回调，实现后必须有return且==YERROR_NotErro时协议正常进行
t_YERROR YPackRecOkHandle(uint8_t* pPack, uint16_t PackLength);
//用户可实现，该函数为正确接收所有数据后回调，,携带信息Info为REC_COMMPLE_INFO
t_YERROR YRecCommpleHandle(uint8_t* Info, uint16_t InfoLength);

#endif // !__YZQ_YMODEM_H

