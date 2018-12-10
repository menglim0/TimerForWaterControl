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
#ifndef TM1637_H
#define TM1637_H

#include "sys.h"

#define TM1637_CLK           PBout(13)  
#define TM1637_DIO           PBout(14)    
#define TM1637_READ_DIO      PBin(14) 
  
//IO·½ÏòÉèÖÃ
#define TM1637_DIO_IN()     {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=0x08<<24;}
#define TM1637_DIO_OUT()    {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=0x03<<24;}

 
void TM1637_Delay_us(unsigned  int Nus); 
void TM1637_Start(void);
void TM1637_Ack(void);
void TM1637_Stop(void);
void TM1637_WriteByte(unsigned char oneByte);
unsigned char TM1637_ScanKey(void);
void TM1637_NixieTubeDisplay(void);

//void TM1637_AdressDisplay(void);
void TM1637_AdressDisplay(uint8_t num1,uint8_t num2,uint8_t num3,uint8_t num4,char dp);

void TM1637_Init(void);
void TM1637LED_Init(void);
 
#endif
