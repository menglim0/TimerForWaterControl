#include "led.h"
#include "delay.h"
#include "sys.h"
#include "TM1637.h"
#include "button.h"
#include <stdbool.h>

#define LED1_On() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define LED2_On() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define LED1_Off() GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define LED2_Off() GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define Int_1Min 60

uint32_t Delay_Cnt,total_delay_Time=180;

uint8_t Button_Right_Status,Button_Left_Status,Button_Left_DelayCnt,Button_Right_DelayCnt;


uint8_t display_10min,display_1min,display_10s,display_1s,display_point,pulse_hold_time;

bool FlowDelayTime;

typedef enum 
{
	Not_PushDown,
	LongPushDown,
	ShortPushDown
}Button_State; 

Button_State Button_Right_State,Button_Left_State;

typedef enum 
{
	Normal_Cnt,
	Set_CountUp,
	Set_CountDown,
	Config_Set,
	Config_Cancel
}Counter_State; 

Counter_State Counter_State_control;

 int main(void)
 {	
	delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯	  
	LED_Init();		  	//³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	TM1637_Init();
	 Button_Init();
	while(1)
	{
	
		Button_Right_Status=Button_Right;
		Button_Left_Status=Button_Left;
		
		if(Bit_SET==Button_Right_Status)
		{
			Button_Right_DelayCnt++;
			if(Button_Right_DelayCnt>10&&Counter_State_control==Normal_Cnt)
			{
			Counter_State_control=Set_CountDown;
			total_delay_Time = total_delay_Time-Int_1Min;	
			LED2_Off();//LED1Êä³ö¸ß
				Button_Right_DelayCnt=0;
			}
		}
		else if(Bit_RESET==Button_Right_Status&&Counter_State_control!=Normal_Cnt)
		{
				Button_Right_DelayCnt++;
					if(Button_Right_DelayCnt>10&&Counter_State_control== Set_CountDown)
					{		
					Counter_State_control=Normal_Cnt;
						Button_Right_DelayCnt=0;
					}

		}
		
		if(Bit_SET==Button_Left_Status)
		{
			Button_Left_DelayCnt++;
			if(Button_Left_DelayCnt>10&&Counter_State_control==Normal_Cnt)
			{
			Counter_State_control=Set_CountUp;
			total_delay_Time = total_delay_Time+Int_1Min;	
			LED2_Off();//LED1Êä³ö¸ß
				Button_Left_DelayCnt=0;
			}
		}
		else if(Bit_RESET==Button_Right_Status&&Counter_State_control!=Normal_Cnt)
		{
				Button_Left_DelayCnt++;
					if(Button_Left_DelayCnt>10&&Counter_State_control== Set_CountUp)
					{		
					Counter_State_control=Normal_Cnt;
						Button_Left_DelayCnt=0;
					}

		}
		/*
		if(Bit_SET==Button_Right_Status)
		{
			Button_Right_DelayCnt++;
			if(Button_Right_DelayCnt>100&&Button_Right_State==Normal_Cnt)
			{
			Button_Right_State=LongPushDown;
			LED2_Off();//LED1Êä³ö¸ß
			}
		else if(Button_Right_DelayCnt>10&&Counter_State_control== Set_CountUp)
		{
			Button_Right_State=ShortPushDown;
		total_delay_Time--;
		}
		
		
			
		LED1_On(); //LED0Êä³öµÍ
		
		}		
		else if(Bit_SET==Button_Left_Status)
		{
		Button_Left_DelayCnt++;
		if(Button_Left_DelayCnt>100&&Button_Left_State==Normal_Cnt)
		{
			Button_Left_State=LongPushDown;
		  LED1_Off(); //LED0Êä³öµÍ
			}
		else if(Button_Left_DelayCnt>10&&Counter_State_control== Set_CountDown)
		{
		Button_Left_State=ShortPushDown;
		total_delay_Time++;
		}
		
		//LED2_On();//LED1Êä³ö¸
		}
		else
		{
			if(Button_Left_State==ShortPushDown&&Counter_State_control== Config_Set)
			{
				Counter_State_control= Set_CountUp;
			}
			else if(Button_Right_State==ShortPushDown&&Counter_State_control== Config_Set)
			{
				Counter_State_control= Set_CountDown;
			}
			else if(Button_Right_State==LongPushDown&&Counter_State_control== Normal_Cnt)
			{
				Counter_State_control= Config_Set;
			}
			else if(Button_Left_State==LongPushDown&&Counter_State_control== Config_Set)
			{
				Counter_State_control= Config_Cancel;
			}
			
			Button_Left_State=Not_PushDown;
			Button_Right_State=Not_PushDown;
			
			
		LED1_On(); //LED0Êä³öµÍ
		//LED2_On();//LED1Êä³ögao
		}*/

		delay_ms(13);
		Delay_Cnt++;
	
		/*
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//LED0Êä³ö¸ß
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);//LED1Êä³öµÍ
		*/
		//delay_ms(1000);
		//TM1637_NixieTubeDisplay();
		if(Delay_Cnt>=80)
		{
			if(Flow_On==Bit_SET)
			{
				if(total_delay_Time==0)
				{
				;}
				else
				{
				total_delay_Time--;
					pulse_hold_time=0;
				}
			}
			else
			{
				total_delay_Time=1800;
			}
			
			if(total_delay_Time==0&&FlowDelayTime==false)
			{
			LED2_On();//LED1Êä³ö¸
				FlowDelayTime=true;
			}
			display_10min = total_delay_Time/600;
			display_1min = total_delay_Time/60%10;
			display_10s = total_delay_Time%60/10;
			display_1s = total_delay_Time%60%10;
			
			display_point=!display_point;
			TM1637_AdressDisplay(display_10min,display_1min,display_10s,display_1s,display_point);
			//TM1637_AdressDisplay(1,2,3,9,display_point);
			Delay_Cnt=0;
		}
		
		if(FlowDelayTime==true)
		{
			
			if(pulse_hold_time>=10)
			{
			LED2_Off();
			}
			else
			{
				pulse_hold_time++;
			}
		}
	}
 }


