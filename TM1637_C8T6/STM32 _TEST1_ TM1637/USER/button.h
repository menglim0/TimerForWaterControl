#ifndef __BUTTON_H
#define __BUTTON_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define Button_Left PBin(10)	// Left button input from PB10
#define Button_Right PBin(11)	// Right button input from PB11

#define Flow_On PBin(7)	// Right button input from PB11
//#define Button_Left GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
//#define Button_Right GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)

void Button_Init(void);//��ʼ��

		 				    
#endif

