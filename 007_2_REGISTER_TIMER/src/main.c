#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t count;

void RCC_Config()
{
	RCC->CR |= 0x00010000;			// HSEON enable
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;			// CSS Enable
	RCC->PLLCFGR |= 0x00400000;		// PLL e HSE se�tik
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL p = 2
	RCC->CFGR |= 0x00000000;		// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;		// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;		// APB1 Prescaler = 4
	RCC->CIR |= 0x00800000;			// CSS Flag clear
}

void TIM_Config()
{
	RCC->APB1ENR |= 1 << 0;

	TIM2->CR1 |= 0 << 4;		// Counter mode is upcounter
	TIM2->CR1 |= 0 << 5; 		// Center aligned mode edge-aligned mode
	TIM2->CR1 |= 0 << 8;		// Set the clock division to 1
	TIM2->SMCR |= 0 << 0;		// �nternal clock source
	TIM2->EGR |= 1 << 0;		// Timer update generation
	TIM2->PSC = 41999;
	TIM2->ARR = 4000;
	TIM2->CR1 |= 1 << 0;		// Timer2 counter enable
}

int main(void)
{
	RCC_Config();
	TIM_Config();
  while (1)
  {
	count = TIM2->CNT;
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
