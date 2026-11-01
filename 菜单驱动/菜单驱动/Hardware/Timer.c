#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "PWM.h"


volatile uint16_t Key_Num = 0;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 999;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
}	


void TIM2_IRQHandler(void)
{
	static uint8_t count = 0;//计数
	static uint8_t Key_state = 1;//1松开，0按下
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)
		{	
			if(Key_state == 1)
			{
				count++;
				if(count >=19)
				{
					Key_state = 0;
					count = 0;
					Key_Num = 1;
				}
			}	
		}
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1)
		{
			if(Key_state == 0)
			{
				Key_state = 1;
				count = 0;
			}
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			
	}	
}	

