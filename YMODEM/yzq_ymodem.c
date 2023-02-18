/*
 * @Date: 2022-08-17 14:25:15
 * @Autor: YangZhiQiang
 * @LastEditors: YangZhiQiang
 * @Description: 
 * @CodingFormat: gb2312
 * @LastEditTime: 2022-08-29 17:38:08
 * @FilePath: yzq_ymodem.c
 * @Else: 
 */

/*
    �������⣺
    8.24:�ڶ�֡��֡ͷ������ʱ��������
    ��������ֹͣ��������(��:�ر��ж�)
    20220825���ڶ�֡��֡ͷ����������ȣ�
    �ر��ж�ȷʵʱ�����Ӱ�죺�������У��ر��жϲ�����д����δ������Ҫ�����ݣ�
    ����һֱ���ڷ�����ȴû�����ݴ������ѭ���У���������ʱ��
    δ����ڶ�֡��֡ͷ��ʶ��ΪSOH���⣬�ֽ���취Ϊ���ڶ�֡������SOH��128byte��
    ʶ��
    20220829���ڶ�֡��֡ͷ����������ȣ�
    �ѽ���������Ϊ��YREC_NextPack��֧�У�ͷ֡ȷ�Ϲ����У���ͷ֡�Ľ���û�н���
    �ȴ�������ͷ֡��ʶ��Ϊ�ϴλ����ͷ֡�����º�������������⻹������ѭ��NAKӰ�죩
    
    �������⣺
    20220824��AllowState: ��Ҫ���ĵĽ���״̬
    return����AllowState==HWhatStatus����return�ϴ�״̬
    20220825���Ѹ���

    20220825���ʼǣ�����д���ݺͶ����ݵĲ��������ݶ�λ��־tail��headǰ��
    ��д��϶���д�����󣬲�����������ݸ��ǣ����Բ��ÿ��Ƕ�����
    ��д��������;����ϵ����

    20220826���ʼǣ�������ܻ���Щ������磺FullCacheFlag��־���Բ����ã�
    ��Ϊ��HaveCach��= 0��������������ʱhead == tail���Ϳ��Ա�ʾ��������
    �Ͳ����ö���ı�־�����ж�

    20220826���ʼǣ����λ����������Ϊ���������Ϊ����һ��������Ϣ�Ľṹ��
    ��������ʹ���ڶ��������
    
    20220829���ʼǣ�����������������򣬼������ʱ���������Ȳ��ӣ�����ģ������Щ��


    ymodemЭ�����⣺
    20220826����Ӷ�֡���⣬�����һ֡��Ϊ0���ڶ�֡����Ϊ1��ͬʱ��Ӵ���
    handle
    
    20220826���ʼǣ��ļ��ǳ���ʱ��֡���¼8λ���������ֻ��0��ʼ��¼
    
    20220829����������ʹ�õ���λ��������ʱû�����λش�EOT�����ڽ���֡������Ϊ���յ���EOT
    20220829����һ�۵�Ϊ�������һ֡��EOT�ش���Щsize���ļ�������⣬�����ҵ�����Ϊ������
    �����ݵ����һ֡����λ�������ʣ��δ�����ļ����ݴ�С�����б���sizeС��128����֡size
    Ϊ128byte���ͣ����ǳ�����128size�ж�ʱ���ж�128size��û�н�״̬��״̬���ΪYREC_Buffer
    ״̬���Ӷ�����YREC_Buffer̬�������ݴ�СΪ1K�����³�ʱNAK������ѭ��NAK
    
*/
#define H_ARRAY_SIZE(x)         (sizeof(x) / sizeof(x)[0])
#define CLEAN_CACH_FILL_DATE    0x00
#include "yzq_ymodem.h"
#include "stdio.h"
#include "at32f4xx.h"

/*=========================��Ҫ����END============================*/

/*=========================���λ���START============================*/
static t_ReceiveCach ReceiveCach = 
{
	.DateBuffer = {0},
	.FullCacheFlag = 0,
	.CachHaveDate = 0,
	.Head = 0,
	.Tail = 0,
};

static t_UserStateH AllowRec(t_UserStateH AllowState)
{   
    
    static t_UserStateH TempState = HWhatStatus;
    switch (AllowState)
    {
        case Henable:
        {
//            USART_Cmd(USART1, ENABLE);
            USART_INTConfig(USART1, USART_INT_RDNE, ENABLE);
            TempState = Henable;
        } break;

        case Hdisable:
        {
//            USART_Cmd(USART1, DISABLE);
            USART_INTConfig(USART1, USART_INT_RDNE, DISABLE);
            TempState = Hdisable;
        } break;

        case HWhatStatus:
        {
            return TempState;
        }
        default:
            break;
    }
    return TempState;
}

static int H_CleanCach(void)
{
    AllowRec(Hdisable);
    // �ӿ��ٶ�
//    for(uint16_t cnt = 0; cnt < H_ARRAY_SIZE(ReceiveCach.DateBuffer); cnt++)
//    {
//        ReceiveCach.DateBuffer[cnt] = CLEAN_CACH_FILL_DATE;
//    }
    ReceiveCach.Head = ReceiveCach.Tail;
    ReceiveCach.CachHaveDate = 0;
    ReceiveCach.FullCacheFlag = 0;
    AllowRec(Henable);
    return 0;
}

/*
	pDate:��Ҫд��ָ��
	DateSize:��Ҫд�����ݳ���
	return: 
		-1:����д�����ݳ��������С
        -2����ֹд��
		-3:���治������������д��,��Ҫ�ȴ����ݶ���,�ͷŻ���
		 0:д��ɹ�
*/

int H_WriteCach(uint8_t* pDate, uint16_t DateSize)
{
	uint16_t TempTail = ReceiveCach.Tail;
	if(DateSize > H_BUFF_LENGTH)
	{
		return -1;
	}
	for(uint16_t cnt = 0; cnt < DateSize; )
	{
		ReceiveCach.DateBuffer[ReceiveCach.Tail] = pDate[cnt];
		ReceiveCach.Tail++;
		cnt++;
		if(ReceiveCach.Tail==H_BUFF_LENGTH)
		{
			ReceiveCach.Tail = 0;
		}
		
		if(ReceiveCach.Tail==ReceiveCach.Head)
		{
			if(cnt < DateSize)
			{
				ReceiveCach.Tail = TempTail;
				return -3;
			}
			else
			{
				ReceiveCach.FullCacheFlag = 1;
				AllowRec(Hdisable);
			}
		}
	}
	ReceiveCach.CachHaveDate = 1;
	return 0;
}

/*
	pRDate:��Ҫ����ָ��
	RDateSize:��Ҫ�������ݳ���
	return: 
		-1:���ζ������ݳ��������С
		-2:������������
		-3:�����е��������ݳ���С����Ҫ��������
		 0:��ȡ�ɹ�
*/
static int H_ReadCach(uint8_t* pRDate, uint16_t RDateSize)
{
	uint16_t TempHead = ReceiveCach.Head;
	
	if(RDateSize > H_BUFF_LENGTH){
		return -1;
	}
	else if(!ReceiveCach.CachHaveDate)
	{
		return -2;
	}
    
	for(uint16_t cnt = 0; cnt < RDateSize; )
	{
		pRDate[cnt] = ReceiveCach.DateBuffer[ReceiveCach.Head];
		ReceiveCach.Head++;
		cnt++;
		if(ReceiveCach.Head==H_BUFF_LENGTH)
		{
			ReceiveCach.Head = 0;
		}
		if(ReceiveCach.Head==ReceiveCach.Tail)
		{
			if(cnt < RDateSize)
			{
				ReceiveCach.Head = TempHead;
				return -3;
			}
			else
			{
				ReceiveCach.CachHaveDate = 0;
				ReceiveCach.FullCacheFlag = 0;
			}
		}
    }
    AllowRec(Henable);
	return 0;
}
/*=========================���λ���END============================*/



/*=========================YmodemReceiveStart============================*/
// ʱ���
volatile static uint32_t YmodemTimeStamp;
static uint8_t  YREC_FirstCnt = 0;
// һ֡1K�����ݻ�����
static uint8_t  RecBuffer[YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE +
                         YDATE_SIZE_1K + YCRCH_SIZE + YCRCL_SIZE] = {0};
                         
//static uint16_t     ReceiveLength = sizeof(RecBuffer) / sizeof(RecBuffer[0]);

static const t_PacketStru YLoca_1k = 
{
    .YTypeLoca  = 0,
    .YSeqLoca   = YTYPE_SIZE,
    .YSeqOcLoca = YTYPE_SIZE + YSEQ_SIZE,
    .YDateLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE,
    .YCrchLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_1K,
    .YCrclLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_1K + YCRCH_SIZE,
    .YPackLen   = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_1K + YCRCH_SIZE + YCRCL_SIZE,
    .YDatelen   = YDATE_SIZE_1K,
};

static const t_PacketStru YLoca_128 = 
{
    .YTypeLoca  = 0,
    .YSeqLoca   = YTYPE_SIZE,
    .YSeqOcLoca = YTYPE_SIZE + YSEQ_SIZE,
    .YDateLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE,
    .YCrchLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_128,
    .YCrclLoca  = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_128 + YCRCH_SIZE,
    .YPackLen   = YTYPE_SIZE + YSEQ_SIZE + YSEQOC_SIZE + YDATE_SIZE_128 + YCRCH_SIZE + YCRCL_SIZE,
    .YDatelen   = YDATE_SIZE_128,
};

// ������
static const uint8_t* const StrReceiveState[] = 
{
    "YREC_Ready",
    "YREC_Buffer",
    "YREC_NextPack",
    "YREC_First",
    "YREC_Norm",
    "YREC_Eot",
    "YREC_EndRec",
    "YREC_Erro",
    "YREC_Nak",
};

static const uint8_t* const StrErrorClass[] = 
{
    "YERROR_NotErro",
    "YERROR_Crc",
    "YERROR_FileName",
    "YERROR_NoPack",
    "YERROR_FrameSequen",
    "YERROR_FrameSort",
    "YERROR_OutTime",
    "YERROR_RecHandle",
    "YERROR_Can",
    "YERROR_Nak",
    "YERROR_EndRec",
};

__weak t_YERROR YRecFileNameHandle(uint8_t* FileName, uint8_t FileNameSize)
{
    printf("FileName:%s\r\n", FileName);
    return YERROR_NotErro;
}

__weak t_YERROR YErroHandle(t_YERROR ErrorClass)
{
    printf("ErrorClass:%s\r\n", StrErrorClass[ErrorClass]);
    return YERROR_NotErro;
}

__weak t_YERROR YPackRecOkHandle(uint8_t* pPack, uint16_t PackLength)
{
   printf("YPackRecOkHandle\r\n");
    return YERROR_NotErro;
}
__weak t_YERROR YRecCommpleHandle(uint8_t* Info, uint16_t InfoLength)
{
    printf("Info:%s\r\n", Info);
    return YERROR_NotErro;
}

void YTick(void)
{
    YmodemTimeStamp++;
}

static uint32_t YGetTick(void)
{
    return YmodemTimeStamp;
}

/**
 * @Autor: YangZhiQiang
 * @LastEditors: YangZhiQiang
 * @brief: ������ʼʱ���������ú��������Ƿ�ʱ
 * @param {uint32_t*} StartTimeHandle��
 * @param {uint32_t} OutTime
 * @return 1����ʱ 0��δ��ʱ
 * @else: 
 */
int8_t YTimeOut(uint32_t* StartTimeHandle, uint32_t OutTime)
{
    uint32_t TempTick = YGetTick();
    if(TempTick - *StartTimeHandle > OutTime)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @Autor: YangZhiQiang
 * @LastEditors: YangZhiQiang
 * @description: ����ÿ�������ƶ�һ��λ��
 * @param {uint16_t*} Array
 * @param {uint8_t} ArraySize
 * @param {uint16_t} Filling
 * @return {*}
 */
static void MoveDate(uint8_t* Array, uint8_t ArraySize, uint16_t Filling)
{
	for(int cnt = 0; cnt < ArraySize; cnt++)
	{
		Array[cnt] = Array[cnt+1];
	}
	Array[ArraySize-1] = Filling;
}

__weak void YSendChar(uint8_t ch)
{
    USART_SendData(USART1, ch);
    while ( USART_GetFlagStatus(USART1, USART_FLAG_TRAC) == RESET );   
//    printf("YSendChar:0x%x\r\n", ch);
}

static uint16_t Ycrc16(uint8_t *data, uint16_t length)
{
  uint16_t crc = 0u;
  while (length)
  {
      length--;
      crc = crc ^ ((uint16_t)*data++ << 8u);
      for (uint8_t i = 0u; i < 8u; i++)
      {
          if (crc & 0x8000u)
          {
              /* 
                �������ʽΪX16+X12+X5+1��0x1021ʽȥ����X16��ֵ����Ϊ
                (crc << 1u) ^ 0x1021u���Ƚ���λ���Ƶ�������볣������У��
                һ��
              */
              crc = (crc << 1u) ^ 0x1021u;
          }
          else
          {
              crc = crc << 1u;
          }
      }
  }
  return crc;
}

t_YERROR YPackChak(uint8_t* Pack, uint16_t PackLenth)
{
    
//    printf("YPackChak\r\n"); 
//    for(uint16_t cnt = 0; cnt < PackLenth; cnt++)
//    {
//        printf("%x ", Pack[cnt]); 
//    }
//    printf("\r\n"); 
    t_PacketStru pPacketStru;
    if(PackLenth==YLoca_128.YPackLen)
    {
        pPacketStru = YLoca_128;
    }
    else if (PackLenth==YLoca_1k.YPackLen)
    {
        pPacketStru = YLoca_1k;
    }
    else
    {
        return YERROR_NoPack;
    }
    // ֡�����
    if(Pack[pPacketStru.YSeqLoca]!=(uint8_t)(~Pack[pPacketStru.YSeqOcLoca]))
    {
        return YERROR_FrameSequen;
    }
    // У�����
    uint16_t TempCrc = (Pack[pPacketStru.YCrchLoca]<<8) + 
                        Pack[pPacketStru.YCrclLoca];
    if(TempCrc!=Ycrc16(&Pack[pPacketStru.YDateLoca], pPacketStru.YDatelen))
    {
        return YERROR_Crc;
    }
    // �������޴���
    static uint8_t TempFrameSequen = 0;
    static uint8_t NotErroCnt = 0;
    if(NotErroCnt==0)
    {
        NotErroCnt = 1;
    }
    else
    {
        TempFrameSequen++;
    }

    if(TempFrameSequen!=Pack[pPacketStru.YSeqLoca])
    {
        return YERROR_FrameSort;
    }

    return YERROR_NotErro;
}

void YReceiveDate(void)
{
    uint32_t TempTick = YGetTick();
    t_ReceiveState YReceStaCach[TNum] = {YREC_Ready};
    t_PacketStru pPacketSt = YLoca_128;
    t_ReceiveState YReceiveState = YREC_Ready;
    t_YERROR YErro = YERROR_NotErro;
    
    H_CleanCach();
    while (YReceiveState !=YREC_EndRec)
    {
        // ��¼�ϴ�YReceiveState״̬
        MoveDate(YReceStaCach, Y_ARRAY_SIZE(YReceStaCach), YReceiveState);
        switch (YReceiveState)
        {
            case YREC_Ready:
            {
                while (YGetTick() - TempTick < SHAKE_HANDS_TIME_OUT) 
                {
                    H_ReadCach(RecBuffer, 1);
                    if ( SOH_Y==RecBuffer[0])
                    {
                        pPacketSt = YLoca_128;
                        break;
                    }
                    else if (STX_Y==RecBuffer[0])
                    {
                        pPacketSt = YLoca_1k;
                        break;
                    }
                    // ��ʱ������������
                    if( !( (YGetTick() - TempTick) % YReceiveDateDelay) )
                    {
                        YSendChar(CHARC_Y);
                        while(!( (YGetTick() - TempTick) % YReceiveDateDelay));
                    }
                }

                if( (YGetTick() - TempTick) >= SHAKE_HANDS_TIME_OUT)
                {
                    YErro = YERROR_OutTime;
                    YReceiveState = YREC_Erro;
                    goto SwitchEnd;
                }
                // ���ֳɹ�
                YReceiveState = YREC_Buffer;
            } break;

            case YREC_First:
            {
                // �ص������ļ���
                if(YERROR_NotErro !=YRecFileNameHandle(&RecBuffer[pPacketSt.YDateLoca], pPacketSt.YDatelen))
                {
                    YErro = YERROR_RecHandle;
                    YReceiveState = YREC_Erro;
                    goto SwitchEnd;
                }
                // ��ջ��棬���ӽ�׳��
                H_CleanCach();
                YSendChar(ACK_Y);
                YSendChar(CHARC_Y);
                YReceiveState = YREC_NextPack;
            } break;
            
            case YREC_Norm:
            {
                if(YERROR_NotErro !=YPackRecOkHandle(&RecBuffer[pPacketSt.YDateLoca], pPacketSt.YDatelen))
                {
                    YErro = YERROR_RecHandle;
                    YReceiveState = YREC_Erro;
                    goto SwitchEnd;
                }
                // ��ջ��棬���ӽ�׳��
                H_CleanCach();
                YSendChar(ACK_Y);
                YReceiveState = YREC_NextPack;
            } break;

            case YREC_NextPack:
            {
                TempTick = YGetTick();
                while (YGetTick() - TempTick < REC_TIME_OUT) 
                {
                    // ��λͷ֡��ȷ����֡����
                    while(0!=H_ReadCach(RecBuffer, 1))
                    {
                        if(YTimeOut(&TempTick, REC_TIME_OUT))
                        {
                            YReceiveState = YREC_Nak;
                            goto SwitchEnd;
                        }
                    }
                    // �����ݴ���������ȶ�
                    if (STX_Y==RecBuffer[0])
                    {
                        // �л�֡��������
                        pPacketSt = YLoca_1k;
                        YReceiveState = YREC_Buffer;
                        goto SwitchEnd;
                    }
                    else if (EOT_Y==RecBuffer[0])
                    {
                        YReceiveState = YREC_Eot;
                        goto SwitchEnd;
                    }
                    else if (CAN_Y==RecBuffer[0])
                    {
                        YErro = YERROR_Can;
                        YReceiveState = YREC_Erro;
                        goto SwitchEnd;
                    }
                    else if ( SOH_Y==RecBuffer[0])
                    {
                        // �л�֡��������
                        pPacketSt = YLoca_128;
                        YReceiveState = YREC_Buffer;
                        goto SwitchEnd;
                    }
                    else
                    {
                        YReceiveState = YREC_Nak;
                        goto SwitchEnd;
                    }
                }
            } break;
            
            case YREC_Buffer:
            {
                uint32_t TiemCnt = YGetTick();

                while(0!=H_ReadCach(&RecBuffer[pPacketSt.YSeqLoca], pPacketSt.YPackLen - 1))
                {
                    if(YTimeOut(&TiemCnt, REC_TIME_OUT))
                    {
                        YReceiveState = YREC_Nak;
                        goto SwitchEnd;
                    }
                }
                // У�����޴���
                t_YERROR TempError = YPackChak(RecBuffer, pPacketSt.YPackLen);
                switch (TempError)
                {
                case YERROR_NoPack:
                case YERROR_FrameSequen:
                case YERROR_Crc:
                {
                    YErroHandle(TempError);
                } break;
                
                case YERROR_NotErro:
                {
                    if(YREC_FirstCnt==0)
                    {
                        // ͷ֡
                        if(RecBuffer[pPacketSt.YSeqLoca]==0)
                        {
                            YREC_FirstCnt = 1;
                            YReceiveState = YREC_First;
                        }
                        else
                        {
                            // ��һ֡����
                            YErro = YERROR_FrameSort;
                            YReceiveState = YREC_Erro;
                            goto SwitchEnd;
                        }
                    }
                    else
                    {
                        YReceiveState = YREC_Norm;
                    }
                } break;
                
                default:
                    break;
                }
            } break;
            // ����
            case YREC_Eot:
            {
//                printf("YREC_Eot\r\n");
                uint32_t TiemCnt = YGetTick();
                uint8_t Ch[1] = {0};
                H_CleanCach();
                // �ȴ���λ���ش�EOT
                YSendChar(NAK_Y);
                while(0!=H_ReadCach(Ch, 1))
                {
                    if(YTimeOut(&TiemCnt, YREC_EOT_TIME_OUT))
                    {
                        YReceiveState = YREC_Nak;
                        goto SwitchEnd; 
                    }
                }
//                printf("Ch:0x%x\r\n", Ch[0]);
                if (Ch[0]==EOT_Y)
                {
                    uint8_t* Str = REC_COMMPLE_INFO;
                    YSendChar(ACK_Y);
                    YSendChar(CHARC_Y);
                    // ȷ�Ϸ��������λ�����ٷ���һ֡�հ�֡����֡���ã�ֱ��ACK����
                    YSendChar(ACK_Y);
                    YRecCommpleHandle(Str, Y_ARRAY_SIZE(Str));
                    // ���ݽ�����ɣ��˳�״̬��
                    YReceiveState = YREC_EndRec;
                }
                // �յ�һ��EOT�����豸�ظ�NAK����λ��δ�ٴη���EOT
                else if (Ch[0]!=EOT_Y)
                {
                    YReceiveState = YREC_Nak;
                }
//                printf("YREC_Eot END\r\n");
            } break;

            // �ظ�
            case YREC_Nak:
            {
                static uint8_t ErroCnt = 0;
//                printf("YREC_Nak\r\n");
                // ��ջ���
                H_CleanCach();
                YSendChar(NAK_Y);
                ErroCnt++;
                if(ErroCnt > NAK_ERROR_MAX_CNT)
                {
                    ErroCnt  = 0;
                    YErro = YERROR_Nak;
                    YReceiveState = YREC_Erro;
                    goto SwitchEnd;
                }
                YReceiveState = YREC_NextPack;
            } break;

            case YREC_Erro:
            {
//                printf("YREC_Erro\r\n");
                YSendChar(EOT_Y);
                YSendChar(EOT_Y);
                YSendChar(EOT_Y);
                YErroHandle(YErro);
                YErroHandle(YERROR_EndRec);
                YReceiveState = YREC_EndRec;
            } break;

            default:
            {
            }
            break;
        }
        SwitchEnd:{}
    }
}
/*=========================YmodemReceiveEnd============================*/
