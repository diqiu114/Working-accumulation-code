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
    
// ���λ��峤��
#define H_BUFF_LENGTH       1500
// �����ź�'C'ѭ�����ͼ��ʱ��
#define YReceiveDateDelay   500     

// ���ճ�ʱʱ��
//#define TIME_OUT                    3000 // 3000��Tick��λ������1��tickΪ1ms
// ���ֳ�ʱʱ��3000��Tick��λ������1��tickΪ1ms
#define SHAKE_HANDS_TIME_OUT        3000    
// �������ݳ�ʱʱ��1000��Tick��λ������1��tickΪ1ms
#define REC_TIME_OUT                1000
// ���ս������ݱ�־��ʱʱ�䣬����1��tickΪ1ms
#define YREC_EOT_TIME_OUT           2000   

// ������ɴ�ӡһЩ��Ϣ uint8_t* Str = REC_COMMPLE_INFO;
#define REC_COMMPLE_INFO    "�������,������Դ�ӡһЩ��Ϣ\r\n"
// �����ظ�NAK��������
#define NAK_ERROR_MAX_CNT   10

#include "stdint.h"

typedef enum
{
    Hdisable = 0,
    Henable,
    HWhatStatus,
}t_UserStateH;

// ״̬��¼ʱ����
typedef enum
{
    TOld = 0,
    TNow,
    TNum,
}t_TimeLine;

// ��������
typedef enum 
{
    YERROR_NotErro = 0,
    YERROR_Crc, 
    YERROR_FileName,
    YERROR_NoPack,
    // ֡����֡��ȡ����Ӧ����
    YERROR_FrameSequen,
    // ��֡==��֡++
    YERROR_FrameSort,
    YERROR_OutTime,
    // �������ݺ�ص���������
    YERROR_RecHandle,
    YERROR_Can,
    YERROR_Nak,
    YERROR_EndRec,
}t_YERROR;

// ����״̬
typedef enum
{
    YREC_Ready= 0,
    YREC_Buffer,
    YREC_NextPack,
    YREC_First,
    // ��ʽ����
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

// // ���ṹ���λ��û�����ƣ���ʹ�ø÷���������
// typedef struct 
// {
//     uint8_t     YType:2;
//     uint8_t     YSeq:2;
//     uint8_t     YSeqOC;
//     uint16_t    YDateLength;
//     uint16_t    YCRC;
//     uint8_t     YData[YDATE_SIZE_1K];
// }t_YmodemRec;

// ������ã�������ղ�������
int H_WriteCach(uint8_t* pDate, uint16_t DateSize);
// ������ã������޷�����ʱ���
void YTick(void);
// ������ã���ΪymodemЭ������
void YReceiveDate(void);
// �û�����ʵ�֣�����ظ���������
void YSendChar(uint8_t ch);
// �û���ʵ�֣�ʵ�ֺ������return��==YERROR_NotErroʱЭ���������д�Ϊ��������Ļص�
t_YERROR YErroHandle(t_YERROR ErrorClass);
// �û���ʵ�֣��ú���Ϊ����ͷ֡�ļ�����ص���ʵ�ֺ������return��==YERROR_NotErroʱЭ����������
t_YERROR YRecFileNameHandle(uint8_t* FileName, uint8_t FileNameSize);
// �û���ʵ�֣��ú���Ϊ��ȷ����һ֡���ݺ�ص���ʵ�ֺ������return��==YERROR_NotErroʱЭ����������
t_YERROR YPackRecOkHandle(uint8_t* pPack, uint16_t PackLength);
//�û���ʵ�֣��ú���Ϊ��ȷ�����������ݺ�ص���,Я����ϢInfoΪREC_COMMPLE_INFO
t_YERROR YRecCommpleHandle(uint8_t* Info, uint16_t InfoLength);

#endif // !__YZQ_YMODEM_H

