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
/** \file isr.c
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
 ** \brief	 INT0 interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void INT0_IRQHandler(void)  interrupt INT0_VECTOR
{

}
/******************************************************************************
 ** \brief	 Timer 0 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer0_IRQHandler(void)  interrupt TMR0_VECTOR 
{

}
/******************************************************************************
 ** \brief	 INT0 interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void INT1_IRQHandler(void)  interrupt INT1_VECTOR
{
	;
}
/******************************************************************************
 ** \brief	 Timer 1 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void Timer1_IRQHandler(void)  interrupt TMR1_VECTOR 
{
		if(PIR1&0x08)
		{
		//---------------------------------------
			TMR1L += 0x30;
			TMR1H += 0xF8;			//重新赋初值，在赋值前Timer1已有计数，故在该基础上加初值
													//在进入中断等过程中其实Time是一直在计数的
			nop_();							//TMR1L,TMR1H执行后需要一个nop
		//---------------------------------------	
			PIR1 &= 0xF7;				//清中断标志位
			nop_();							//PIRx执行后需要一个nop
			
			IRQHandler_call();	//回调计时函数
			
		}
}
/******************************************************************************
 ** \brief	 UART send interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void UARTTX_IRQHandler(void)  interrupt UARTTX_VECTOR 
{

}

/******************************************************************************
 ** \brief	 UART receive interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
void UARTRX_IRQHandler(void)  interrupt UARTRX_VECTOR 
{

}

/******************************************************************************
 ** \brief	 ADC interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void ADC_IRQHandler(void)  interrupt ADC_VECTOR 
{

}

/******************************************************************************
 ** \brief	 PWM interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void PWM_IRQHandler(void)  interrupt PWM_VECTOR
{

}

/******************************************************************************
 ** \brief	IIC interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void IIC_IRQHandler(void)  interrupt IIC_VECTOR 
{
		// 时序动作完成后自动触发中断
    if(PIR2 & 0x02)			// 检查IIC中断
    {
        PIR2 &= 0xFD;  	// 清IICIF标志位
        nop_(); 
        // 执行IIC事务状态机
        IIC_StateMachine_ISR();
    }
}

/******************************************************************************
 ** \brief	IIC bus conflict interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void BCLIF_IRQHandler(void)  interrupt BCLIF_VECTOR 
{
	;
}

/******************************************************************************
 ** \brief	CCP interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void CCP_IRQHandler(void)  interrupt CCP_VECTOR 
{
	;
}

/******************************************************************************
 ** \brief	 GPIO 0 interrupt service function
 **	
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P0EI_IRQHandler(void)  interrupt PORT0_VECTOR 
{
	
}
/******************************************************************************
 ** \brief	 GPIO 1 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P1EI_IRQHandler(void)  interrupt PORT1_VECTOR 
{
	;
}
/******************************************************************************
 ** \brief	 GPIO 2 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P2EI_IRQHandler(void)  interrupt PORT2_VECTOR 
{
 ;
}
/******************************************************************************
 ** \brief	 GPIO 3 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void P3EI_IRQHandler(void)  interrupt PORT3_VECTOR 
{
	;
}

/********************************************************************************
 ** \brief	 ACMP interrupt service function
 **			
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void CMP_IRQHandler(void)  interrupt CMP_VECTOR 
{
	
}

/******************************************************************************
 ** \brief	SPI interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void SPI_IRQHandler(void)  interrupt SPI_VECTOR 
{
	;
}















