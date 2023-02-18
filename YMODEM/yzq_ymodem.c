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
    杂项问题：
    8.24:第二帧的帧头错误怀疑时缓存问题
    缓存满后停止接受数据(如:关闭中断)
    20220825：第二帧的帧头错误问题进度：
    关闭中断确实时会造成影响：读过程中，关闭中断不允许写，但未读够需要的数据，
    导致一直卡在反复读却没有数据传入的死循环中，最终引起超时；
    未解决第二帧，帧头会识别为SOH问题，现解决办法为：第二帧不进行SOH（128byte）
    识别
    20220829：第二帧的帧头错误问题进度：
    已解决：问题点为：YREC_NextPack分支中，头帧确认过程中，对头帧的接收没有进行
    等待，导致头帧被识别为上次缓存的头帧，导致后续出错（这个问题还受下述循环NAK影响）
    
    缓存问题：
    20220824：AllowState: 需要更改的接收状态
    return：若AllowState==HWhatStatus，则return上次状态
    20220825：已更改

    20220825：笔记：由于写数据和读数据的操作在数据定位标志tail和head前，
    当写打断读或写操作后，并不会造成数据覆盖，所以不用考虑读过程
    或写过程中中途被打断的情况

    20220826：笔记：缓冲可能还有些冗余比如：FullCacheFlag标志可以不采用，
    因为当HaveCach！= 0，即缓存有数据时head == tail，就可以表示缓存满，
    就不用用多余的标志进行判断

    20220826：笔记：环形缓冲可以升级为，传入参数为带有一个特征信息的结构体
    这样就能使用于多个缓冲区
    
    20220829：笔记：建议升级读缓存程序，加入读超时？（还是先不加，这样模块分离好些）


    ymodem协议问题：
    20220826：添加对帧序检测，比如第一帧序为0，第二帧必须为1，同时添加错误
    handle
    
    20220826：笔记：文件非常大时，帧序记录8位最大计数后又会从0开始记录
    
    20220829：由于现在使用的上位机，结束时没有两次回传EOT，对于结束帧处理变更为接收单次EOT
    20220829：上一观点为错误，最后一帧的EOT回传有些size的文件会出问题，最终找到问题为：带文
    件数据的最后一帧，上位机会根据剩余未传的文件数据大小进行判别，若size小于128，则本帧size
    为128byte类型，但是程序在128size判断时，判断128size后，没有将状态机状态变更为YREC_Buffer
    状态，从而导致YREC_Buffer态接收数据大小为1K，导致超时NAK，导致循环NAK
    
*/
#define H_ARRAY_SIZE(x)         (sizeof(x) / sizeof(x)[0])
#define CLEAN_CACH_FILL_DATE    0x00
#include "yzq_ymodem.h"
#include "stdio.h"
#include "at32f4xx.h"

/*=========================主要函数END============================*/

/*=========================环形缓存START============================*/
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
    // 加快速度
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
	pDate:需要写的指针
	DateSize:需要写的数据长度
	return: 
		-1:单次写入数据超过缓存大小
        -2：禁止写入
		-3:缓存不够将所有数据写入,需要等待数据读出,释放缓存
		 0:写入成功
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
	pRDate:需要读的指针
	RDateSize:需要读的数据长度
	return: 
		-1:单次读出数据超过缓存大小
		-2:缓存中无数据
		-3:缓存中的数据内容长度小于所要读出长度
		 0:读取成功
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
/*=========================环形缓存END============================*/



/*=========================YmodemReceiveStart============================*/
// 时间戳
volatile static uint32_t YmodemTimeStamp;
static uint8_t  YREC_FirstCnt = 0;
// 一帧1K的数据缓存区
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

// 测试用
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
 * @brief: 传入起始时间句柄，调用函数返回是否超时
 * @param {uint32_t*} StartTimeHandle：
 * @param {uint32_t} OutTime
 * @return 1：超时 0：未超时
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
 * @description: 数组每个数据移动一个位置
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
                本身多项式为X16+X12+X5+1，0x1021式去掉了X16的值，因为
                (crc << 1u) ^ 0x1021u会先将高位左移掉，结果与常规冗余校验
                一样
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
    // 帧序错误
    if(Pack[pPacketStru.YSeqLoca]!=(uint8_t)(~Pack[pPacketStru.YSeqOcLoca]))
    {
        return YERROR_FrameSequen;
    }
    // 校验错误
    uint16_t TempCrc = (Pack[pPacketStru.YCrchLoca]<<8) + 
                        Pack[pPacketStru.YCrclLoca];
    if(TempCrc!=Ycrc16(&Pack[pPacketStru.YDateLoca], pPacketStru.YDatelen))
    {
        return YERROR_Crc;
    }
    // 包数据无错误
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
        // 记录上次YReceiveState状态
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
                    // 定时发送握手请求
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
                // 握手成功
                YReceiveState = YREC_Buffer;
            } break;

            case YREC_First:
            {
                // 回调传入文件名
                if(YERROR_NotErro !=YRecFileNameHandle(&RecBuffer[pPacketSt.YDateLoca], pPacketSt.YDatelen))
                {
                    YErro = YERROR_RecHandle;
                    YReceiveState = YREC_Erro;
                    goto SwitchEnd;
                }
                // 清空缓存，增加健壮性
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
                // 清空缓存，增加健壮性
                H_CleanCach();
                YSendChar(ACK_Y);
                YReceiveState = YREC_NextPack;
            } break;

            case YREC_NextPack:
            {
                TempTick = YGetTick();
                while (YGetTick() - TempTick < REC_TIME_OUT) 
                {
                    // 定位头帧，确定该帧类型
                    while(0!=H_ReadCach(RecBuffer, 1))
                    {
                        if(YTimeOut(&TempTick, REC_TIME_OUT))
                        {
                            YReceiveState = YREC_Nak;
                            goto SwitchEnd;
                        }
                    }
                    // 有数据传输过来，比对
                    if (STX_Y==RecBuffer[0])
                    {
                        // 切换帧长度类型
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
                        // 切换帧长度类型
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
                // 校验有无错误
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
                        // 头帧
                        if(RecBuffer[pPacketSt.YSeqLoca]==0)
                        {
                            YREC_FirstCnt = 1;
                            YReceiveState = YREC_First;
                        }
                        else
                        {
                            // 第一帧错误
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
            // 结束
            case YREC_Eot:
            {
//                printf("YREC_Eot\r\n");
                uint32_t TiemCnt = YGetTick();
                uint8_t Ch[1] = {0};
                H_CleanCach();
                // 等待上位机回传EOT
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
                    // 确认发送完后，上位机会再发送一帧空白帧，此帧无用，直接ACK丢弃
                    YSendChar(ACK_Y);
                    YRecCommpleHandle(Str, Y_ARRAY_SIZE(Str));
                    // 数据接收完成，退出状态机
                    YReceiveState = YREC_EndRec;
                }
                // 收到一次EOT，但设备回复NAK后，上位机未再次发送EOT
                else if (Ch[0]!=EOT_Y)
                {
                    YReceiveState = YREC_Nak;
                }
//                printf("YREC_Eot END\r\n");
            } break;

            // 重复
            case YREC_Nak:
            {
                static uint8_t ErroCnt = 0;
//                printf("YREC_Nak\r\n");
                // 清空缓存
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
