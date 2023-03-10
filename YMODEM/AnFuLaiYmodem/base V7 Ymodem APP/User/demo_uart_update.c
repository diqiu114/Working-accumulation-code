/*
*********************************************************************************************************
*
*	模块名称 : 串口方式固件升级
*	文件名称 : demo_uart_update.c
*	版    本 : V1.0
*	说    明 : 串口方式固件升级
*
*	修改记录 :
*		版本号   日期         作者        说明
*		V1.0    2022-06-15   Eric2013    正式发布
*
*	Copyright (C), 2022-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"
#include "common.h"
#include "ymodem.h"


/*
*********************************************************************************************************
*	                                        函数
*********************************************************************************************************
*/
/* 仅允许本文件内调用的函数声明 */
static void JumpToApp(void);

/*
*********************************************************************************************************
*	                                       宏定义
*********************************************************************************************************
*/
#define AppAddr  0x08100000    /* APP地址 */


/*
*********************************************************************************************************
*	                                       变量
*********************************************************************************************************
*/
uint8_t UartRecBuf[248] ={0};
uint8_t FileName[1024];

/*
*********************************************************************************************************
*	函 数 名: DemoUartUpdate
*	功能说明: 串口烧录
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void DemoUartUpdate(void)
{
	/* Ymodem更新 */
	Ymodem_Receive(UartRecBuf, AppAddr);
	
	/* 跳转到APP */
	JumpToApp();
}

/*
*********************************************************************************************************
*	函 数 名: JumpToApp
*	功能说明: 跳转到应用JumpToApp
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void JumpToApp(void)
{
	uint32_t i=0;
	void (*AppJump)(void);         /* 声明一个函数指针 */
    
    /* 关闭全局中断 */
	DISABLE_INT(); 
    
    /* 设置所有时钟到默认状态，使用HSI时钟 */
	HAL_RCC_DeInit();
    
	/* 关闭滴答定时器，复位到默认值 */
	SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

	/* 关闭所有中断，清除所有中断挂起标志 */
	for (i = 0; i < 8; i++)
	{
		NVIC->ICER[i]=0xFFFFFFFF;
		NVIC->ICPR[i]=0xFFFFFFFF;
	}	

	/* 使能全局中断 */
	ENABLE_INT();

	/* 跳转到应用程序，首地址是MSP，地址+4是复位中断服务程序地址 */
	AppJump = (void (*)(void)) (*((uint32_t *) (AppAddr + 4)));

	/* 设置主堆栈指针 */
	__set_MSP(*(uint32_t *)AppAddr);
	
	/* 在RTOS工程，这条语句很重要，设置为特权级模式，使用MSP指针 */
	__set_CONTROL(0);

	/* 跳转到系统BootLoader */
	AppJump(); 

	/* 跳转成功的话，不会执行到这里，用户可以在这里添加代码 */
	while (1)
	{

	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
