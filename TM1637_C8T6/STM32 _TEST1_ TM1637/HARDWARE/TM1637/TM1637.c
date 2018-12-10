/******************************Copyright (c)***********************************
*                Jiangsu Zhihai Electronic Technology Co., Ltd.
*                      Research & Development Department
*
*													www.smarthealth-tech.com
*
-------------------------------------------------------------------------------
* @file    TM1637.h
* @author  GU DONGDONG
* @date    2015-11-25  
*******************************************************************************/
#include "TM1637.h"
#include "delay.h"
/** Write multiple bits in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 */
 
unsigned char DisplayNumber_ComNegtive[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void TM1637_Delay_us(unsigned  int Nus)
{
 for(;Nus>0;Nus--)
	{
	  __nop();
	 	__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
}
//#define TM1637_CLK_Low()    GPIO_ResetBits(GPIOC,GPIO_Pin_2)   
//#define TM1637_CLK_High()   GPIO_SetBits(GPIOC,GPIO_Pin_2)
//#define TM1637_DIO_Low()    GPIO_ResetBits(GPIOC,GPIO_Pin_3)   
//#define TM1637_DIO_High()   GPIO_SetBits(GPIOC,GPIO_Pin_3)
void TM1637_Start(void)
{
	TM1637_DIO_OUT(); 
  TM1637_CLK = 1;
	TM1637_DIO = 1;
	delay_us(2);
	TM1637_DIO = 0;
}
void TM1637_Ack(void)
{
	TM1637_DIO_IN(); 
  TM1637_CLK = 0;
	TM1637_Delay_us(5);
	while(TM1637_READ_DIO);
	TM1637_CLK = 1;
	delay_us(2);
	TM1637_CLK = 0;
}
void TM1637_Stop(void)
{
	TM1637_DIO_OUT(); 
	TM1637_CLK = 0;
	delay_us(2);
	TM1637_DIO = 0;
	delay_us(2);
	TM1637_CLK = 1;
	delay_us(2);
	TM1637_DIO = 1;
}
void TM1637_WriteByte(unsigned char oneByte)
{
 unsigned char i;
	TM1637_DIO_OUT(); 
	for(i=0;i<8;i++)
	{
	 TM1637_CLK = 0;
		if(oneByte&0x01)
		{
			TM1637_DIO = 1;
		}
		else
		{
			TM1637_DIO = 0;
		}
		delay_us(3);
		oneByte=oneByte>>1;
		TM1637_CLK = 1;
		delay_us(3);
	}
}

unsigned char TM1637_ScanKey(void)
{
	unsigned char reKey,i;
	TM1637_Start();
	TM1637_WriteByte(0x42);
	TM1637_Ack();
	TM1637_DIO = 1;
	TM1637_DIO_IN(); 
	for(i=0;i<8;i++)
	{
	  TM1637_CLK = 0;
		reKey=reKey>>1;
		delay_us(30);
		TM1637_CLK = 1;
		if(TM1637_READ_DIO)
		{
		  reKey=reKey|0x80;
		}
		else
		{
		  reKey=reKey|0x00;
		}
		delay_us(30);
	}
  TM1637_Ack();
	TM1637_Stop();
	return(reKey);
}
void TM1637_NixieTubeDisplay(void)
{
	unsigned char i;
	TM1637_Start();
	TM1637_WriteByte(0x40);
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0xC0);
	TM1637_Ack();
		
	for(i=0;i<6;i++)
	{
		TM1637_WriteByte(0x80);
		TM1637_Ack();
	}
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0x88);
	TM1637_Ack();
	TM1637_Stop();
}

void TM1637_AdressDisplay(uint8_t num1,uint8_t num2,uint8_t num3,uint8_t num4,char dp)
{
	//unsigned char i;
	TM1637_Start();
	TM1637_WriteByte(0x44);
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	TM1637_WriteByte(0xC0);
	TM1637_Ack();
	TM1637_WriteByte(DisplayNumber_ComNegtive[num1]);
	TM1637_Ack();
	TM1637_Stop();
	TM1637_Start();
	
	
		TM1637_WriteByte(0xC1);
		TM1637_Ack();
	if(dp==1)
	{
		TM1637_WriteByte(DisplayNumber_ComNegtive[num2]|0x80);
	}
	else
	{
	TM1637_WriteByte(DisplayNumber_ComNegtive[num2]);
	}
		TM1637_Ack();
		TM1637_Stop();
		TM1637_Start();
	
	
		TM1637_WriteByte(0xC2);
		TM1637_Ack();
		TM1637_WriteByte(DisplayNumber_ComNegtive[num3]);
		TM1637_Ack();
		TM1637_Stop();
		TM1637_Start();
	
	
		TM1637_WriteByte(0xC3);
	  TM1637_Ack();
		TM1637_WriteByte(DisplayNumber_ComNegtive[num4]);
		TM1637_Ack();
		TM1637_Stop();
			
		TM1637_Start();
		TM1637_WriteByte(0xC4);
		TM1637_Ack();
		TM1637_WriteByte(0x4f);
		TM1637_Ack();
		TM1637_Stop();
			
		TM1637_Start();
		TM1637_WriteByte(0xC5);
		TM1637_Ack();
		TM1637_WriteByte(0x4f);
		TM1637_Ack();	
		TM1637_Stop();
		
	TM1637_Start();
	TM1637_WriteByte(0x8B);
	TM1637_Ack();
	TM1637_Stop();
}

void TM1637_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;				  
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
 GPIO_Init(GPIOB, &GPIO_InitStructure);					  

}
 


