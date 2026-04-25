/*	include files
*****************************************************************************/
#include "iic.h"
#include "uart.h"
#include "stdio.h"
/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/
#define 	IIC_SCL_IO				P04		//SCL，时钟口
#define 	IIC_SDA_IO				P05		//SDA，数据口

#define		TRUE					1
#define		FALSE					0
/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/
// IIC操作状态定义
typedef enum {
    IIC_IDLE,        // 空闲
    IIC_BUSY,        // 忙
    IIC_ERROR        // 操作失败
} IIC_Status_t;
static IIC_Status_t IIC_Status = IIC_IDLE;

// IIC事务上下文
typedef struct {
    unsigned char Step;			//时序步骤
    unsigned char DevAddr;	//设备地址+写
    unsigned char RegAddr;	//设备寄存器地址
    unsigned char NeedNack;	//ACK应答标记
} IIC_Context_t;
static IIC_Context_t iic_ctx = {0};

volatile unsigned char IIC_TxData;
volatile unsigned char IIC_RxData;

/**********************************************************
 * 函数：IIC_Read_Adress_Byte
 * 功能：发起读操作（异步）
 **********************************************************/
void IIC_Read_Adress_Byte(unsigned char Dev_Addr, unsigned char Reg_Addr)
{
    if(IIC_Status != IIC_IDLE){
				return;
		}
		
    IIC_Status = IIC_BUSY;
    iic_ctx.Step = 1;

    iic_ctx.DevAddr = Dev_Addr;
    iic_ctx.RegAddr = Reg_Addr;
    iic_ctx.NeedNack = 1;

    IICCON2 |= 0x01; // START 
}
/**********************************************************
 * 函数：IIC_Write_One_Byte
 * 功能：发起写操作（异步）
 **********************************************************/
void IIC_Write_One_Byte(unsigned char Dev_Addr, unsigned char Reg_Addr, unsigned char Rdata)
{
    if(IIC_Status != IIC_IDLE) return;

    IIC_Status = IIC_BUSY;
    iic_ctx.Step = 1;

    iic_ctx.DevAddr = Dev_Addr;
    iic_ctx.RegAddr = Reg_Addr;
    IIC_TxData = Rdata;

    IICCON2 |= 0x01; // START
}

// IIC读写事务状态机
void IIC_StateMachine_ISR(void)
{
    switch(iic_ctx.Step){
        case 1: 
            IICBUF = iic_ctx.DevAddr; //发设备地址+写
            iic_ctx.Step = 2;	
            break;
        case 2:  
            IICBUF = iic_ctx.RegAddr; //发寄存器地址
            iic_ctx.Step = 3;
            break;
        // ========== 读流程分支 ==========
        case 3: 
            if(iic_ctx.NeedNack){
                IICCON2 |= 0x02; //RESTART
                iic_ctx.Step = 4;
            }
						// ========== 写流程分支 ==========
            else {
                IICBUF = 0x30; 	//发送数据
                iic_ctx.Step = 8;
            }
            break;
        case 4: 
            IICBUF = iic_ctx.DevAddr|0x01; //发设备地址+读
            iic_ctx.Step = 5;
            break;
        case 5: 
            IICCON2 |= 0x08; //读取数据
            iic_ctx.Step = 6;
            break;
				case 6: 
						IIC_RxData = IICBUF;	// 保存接收到的数据
						IICCON2 |= 0x20;      // ACKDT = 1，即 NACK    
						IICCON2 |= 0x10;      // ACKEN = 1，启动应答序列
						iic_ctx.Step = 7;
						break;
				case 7:
						IICCON2 |= 0x04; // STOP
						iic_ctx.Step = 9;
						break;
        case 8:
            IICCON2 |= 0x04; //STOP
            iic_ctx.Step = 9;
            break;
        case 9:
            IIC_Status = IIC_IDLE;
            iic_ctx.Step = 0;
            iic_ctx.NeedNack = 0;
            break;
        default:
            IIC_Set_Master();
            IIC_Status = IIC_ERROR;
            iic_ctx.Step = 0;
            break;
    }

}
/***********************************************
函数名称：IIC_Set_Master
函数功能：IIC状态设置
入口参数：无
出口参数：无
备注：
************************************************/
void IIC_Set_Master()
{	
	IIC_SDA_IO = 1;					//SDA及SCL为输入口使能IIC后自动为漏极开路
	IIC_SCL_IO = 1;					
	IICADD = 0x24;					//时钟=FSYS/(4*(IICADD+4)) 100khz
	IICSTAT = 0x00;					
	IICCON = 0x20;					//主控模式
	IICCON2 = 0x00;
}

void IIC_Config(void)
{
	IICSEL = 0x00;	// IIC通讯口选择 SDA=P05, SCL=P04
  GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_4);		//初始化P04为输入口
  GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_5);		//初始化P05为输入口 
	IIC_Set_Master();
		// 开启IIC中断
		PIR2 &= 0xFD;         //清IICIF标志位
		nop_();
		PIE2 |= 0x02;         //使能IIC中断
		IRQ_ALL_ENABLE();	  	//使能中断
}


