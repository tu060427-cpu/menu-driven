#include "stm32f10x.h"                  // Device header#include "Delay.h"
#include "LED.h"
#include "Timer.h"
#include "OLED.h"
#include "Motor.h"
#include "PWM.h"
#include "Delay.h"
#include "Key.h"

uint8_t menu_changed = 1;//刷新状态
uint8_t cursor = 1;//光标

extern volatile uint16_t Key_Num;

int main(void)
{
	LED_Init();
	OLED_Init();
	Motor_Init();
	Timer_Init();
	Key_Init();
	
	
	while (1)
	{	
		if(Key_Num == 1)
		{
			cursor = cursor + 1;
			if(cursor > 3)cursor = 1;
			
			Key_Num = 0;
			menu_changed = 1;
		}	
		if(menu_changed == 1)
		{
			if(cursor == 1)
			{
				OLED_ShowString(1,1,"->");
				OLED_ShowString(2,1,"  ");
				OLED_ShowString(3,1,"  ");
				OLED_ShowString(1,3,"OFF");
				OLED_ShowString(2,3,"dianji");
		        OLED_ShowString(3,3,"deng");
				GPIO_SetBits(GPIOA,GPIO_Pin_10);
				TIM_SetCompare3(TIM3,0);
			}	

			if(cursor == 2)
			{
				OLED_ShowString(1,1,"  ");
				OLED_ShowString(2,1,"->");
				OLED_ShowString(3,1,"  ");
		        OLED_ShowString(2,3,"dianji");
		        OLED_ShowString(3,3,"deng");
				GPIO_SetBits(GPIOA,GPIO_Pin_10);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				TIM_SetCompare3(TIM3,100);
			}	
			else if(cursor == 3)
			{
				OLED_ShowString(2,1,"  ");
				OLED_ShowString(3,1,"->");
		        OLED_ShowString(2,3,"dianji");
		        OLED_ShowString(3,3,"deng");
				GPIO_ResetBits(GPIOA,GPIO_Pin_10);
				TIM_SetCompare3(TIM3,0);
			}	
			menu_changed = 0;	
		}	
	}	
}




