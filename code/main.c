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
/** \file main.c
**
** 
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms8f003.h"
#include "iic.h"
#include "uart.h"
#include "stdio.h"
#include "timer.h"
/****************************************************************************/
/*	Local pre-processor symbols('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/


/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/
uint16_t times;

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/
extern uint8_t Sendbuffer[];
/*****************************************************************************
 ** \brief	 main
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/
void GPIO_config(void){

		GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3);
		P13 = 1;	//低电平导通
		GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_5);
		P15 = 1;	//低电平导通
		
}

int main(void)
{		
	
	OSCCON = 0x70;						//内部振荡器用作系统时钟
	
	IIC_Config();
	UART_Config();
	TMR1_Config();
						
	while(1)
	{		
			if(flag_10ms == 1){
					flag_10ms = 0;
					IIC_Write_One_Byte(0x02,0x13,0x30); 
			}		
			if(flag_100ms == 1){
					flag_100ms = 0;	
					IIC_Read_Adress_Byte(0x02,0x13);	//读写不能同时进行
					printf("IIC_RxData=0x%02x\r\n", (int)IIC_RxData);				
			}		
			
	}		
}




