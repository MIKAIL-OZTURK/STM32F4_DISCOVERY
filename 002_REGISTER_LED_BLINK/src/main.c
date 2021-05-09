#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

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

void GPIO_Config(void)
{
	RCC->AHB1ENR |= 1 << 3;			// GPIOD Clock Enable

	GPIOD->MODER |= 1 << 24;		// GPIOD 12. pin output
	GPIOD->MODER &= ~(1 << 25);
	GPIOD->MODER |= 1 << 26;		// GPIOD 13. pin output
	GPIOD->MODER &= ~(1 << 27);
	GPIOD->MODER |= 1 << 28;		// GPIOD 14. pin output
	GPIOD->MODER &= ~(1 << 29);
	GPIOD->MODER |= 1 << 30;		// GPIOD 15. pin output
	GPIOD->MODER &= ~(1 << 31);

	GPIOD->OSPEEDR |= 0XFF000000;
}

int main(void)
{

	RCC_Config();
	SystemCoreClockUpdate();

	GPIO_Config();

  while (1)
  {
	  	 GPIOD->ODR |= 1 << 12;			// 12.pin set
	  	 GPIOD->ODR |= 1 << 13;			// 13.pin set
	  	 GPIOD->ODR |= 1 << 14;			// 14.pin set
	  	 GPIOD->ODR |= 1 << 15;			// 15.pin set

	  	 for(int i=0; i<1680000; i++);

	  	 GPIOD->ODR &= ~(1 << 12);		// 12.pin reset
	  	 GPIOD->ODR &= ~(1 << 13);		// 13.pin reset
	  	 GPIOD->ODR &= ~(1 << 14);		// 14.pin reset
	  	 GPIOD->ODR &= ~(1 << 15);		// 15.pin reset

	  	 for(int i=0; i<1680000; i++);





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
