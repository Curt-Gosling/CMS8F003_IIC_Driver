/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
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

/*****************************************************************************/
/** \file demo_timer.h
**
**
**
** History:
** - 
*****************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms8f003.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/


/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/
extern volatile bit flag_2ms;
extern volatile bit flag_10ms;
extern volatile bit flag_4ms;
extern volatile bit flag_100ms;
extern volatile bit flag_500ms;
extern volatile bit flag_10s;
extern volatile bit flag_15s;
extern volatile unsigned char counter_2ms;
extern volatile unsigned char counter_10ms;
extern volatile unsigned char counter_4ms;
extern volatile unsigned char counter_100ms;
extern volatile unsigned char counter_500ms;
extern volatile unsigned char counter_10s;
extern volatile unsigned char counter_15s;
extern volatile unsigned char delay01_5min;
extern volatile unsigned char delay02_5min;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/******************************************************************************
 ** \brief	 TMR1_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void TMR1_Config(void);
void TMR0_Config(void);
void IRQHandler_call(void);



#endif 






