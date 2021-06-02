#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_TimeBaseInitTypeDef TIM_InitStruct;

int count = 0;

void TIMER_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1 ;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_InitStruct.TIM_Period = 3999;
	TIM_InitStruct.TIM_Prescaler = 41999;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM2 ,ENABLE);
}

int main(void)
{
	TIMER_Config();
  while (1)
  {
	  count = TIM_GetCounter(TIM2);
  }
}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
