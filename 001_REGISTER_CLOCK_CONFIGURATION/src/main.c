#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;
uint32_t SystemClock;

void RCC_Config(void)
{
	// 8 000 000 -> 168 000 000

 	RCC->CR &= ~(1 << 0);			// HSI OFF
	RCC->CR |= 1 << 16;				// HSE 0N
	while(!(RCC->CR & (1 << 17)));	// Wait HSE active
	RCC->CR |= 1 << 19;
	RCC-> PLLCFGR = 0X00000000;		// PLLCFGR Reset			// PLL P 2
	RCC-> PLLCFGR |= (1 << 22);		// PLL Source HSE
	RCC-> PLLCFGR |= (4 << 0);		// PLL M 4
	RCC-> PLLCFGR |= (168 << 6);	// PLL N 168

	RCC->CR |= (1 << 24);
	while(!(RCC->CR & (1 << 25)));

	RCC->CFGR &= ~(1 << 0);
	RCC->CFGR |= (1 << 1);			// System clock is PLL

	while(!(RCC->CFGR & (1 << 1)));	// Select system clock is PLL clock
}

int main(void)
{

	RCC_Config();

	SystemCoreClockUpdate();

	SystemClock = SystemCoreClock;

  while (1)
  {

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
