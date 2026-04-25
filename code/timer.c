/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by CMS LLC.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/****************************************************************************/
/** \file demo_timer.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "timer.h"
/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
****************************************************************************/

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/
/******************************************************************************
** \brief	 TMR1_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
/*-------------------------------------------
备注：	  定时时间计算方法
          定时时间T = {1/[(Fosc)*预分频比)]}*(65535-[TMR1H:TMR1L])
          本程序计算示例：
          T = {1/[(16)*8]}*(65536 - 63536)
		        = 1000 us
-------------------------------------------*/
void TMR1_Config(void)
{
	/*
	(1)设置Timer的运行模式
	*/	
	T1CON = 0x30;				//使用内部时钟源Fosc，预分频比为1:8			
	/*                  
	(2)设置Timer周期     
	*/	                
	TMR1L = 0x30;			  //赋初值
	TMR1H = 0xF8;	
	nop_();							//TMR1L,TMR1H执行后需要一个nop
	/*
	(3)开启中断
	*/
	PIR1 &= 0xF7;				//清中断标志位
	nop_();							//PIRx执行后需要一个nop
	PIE1 |= 0X08;				//允许Timer1中断
	/*
	(4)设置Timer中断优先级
	*/	
	//IRQ_SET_PRIORITY(IRQ_TMR1); //如果选择Timer1中断为高优先级，打开此语句
	IRQ_ALL_ENABLE();	  //使能中断

	/*
	(5)开启Timer
	*/
	T1CON |= 0x01;		//开启Timer1
}



volatile bit flag_2ms;
volatile bit flag_10ms;
volatile bit flag_4ms;
volatile bit flag_100ms;
volatile bit flag_500ms;
volatile bit flag_10s;
volatile bit flag_15s;
volatile unsigned char counter_2ms = 0;
volatile unsigned char counter_10ms = 0;
volatile unsigned char counter_4ms = 0;
volatile unsigned char counter_100ms = 0;
volatile unsigned char counter_500ms = 0;
volatile unsigned char counter_10s = 0;
volatile unsigned char counter_15s = 0;
volatile unsigned char delay01_5min;
volatile unsigned char delay02_5min;

void IRQHandler_call(void){
	
	//定时触发系统
	if(++counter_2ms >= 2){
			counter_2ms = 0;
			flag_2ms = 1;
		if(++counter_4ms >= 2){
				counter_4ms = 0;
				flag_4ms = 1;
		}
		if(++counter_10ms >= 5){
				counter_10ms = 0;
				flag_10ms = 1;					
			if(++counter_100ms >= 10){
					counter_100ms = 0;
					flag_100ms = 1;						
				if(++counter_500ms >= 5){
						counter_500ms = 0;
						flag_500ms = 1;
						if(++counter_10s >= 20){
							counter_10s = 0;	//休眠专用
							flag_10s = 1;
						}
						if(++counter_15s >= 30){
							counter_15s = 0;
							flag_15s = 1;	
							if(delay01_5min > 0){
								delay01_5min--;
							}
							if(delay02_5min > 0){
								delay02_5min--;
							}							
						}						
					}
				}
			}
		}
}

























