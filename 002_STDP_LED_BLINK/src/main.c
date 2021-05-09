#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;			// LED ayarlar�n� yapmak i�in GPIO_InitTypeDef veri t�r�nden
											// bir nesne olu�turduk.
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// ��lemci ile D portunun haberle�mesi i�in
															// AHB1 bus'�n� aktif ettik.

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);			// Yapt���m�z ayarlar� D portuna y�kledik.
}

int main(void)
{
	GPIO_Config();

  while (1)
  {
	  GPIO_SetBits(GPIOD, GPIO_Pin_12);			// D portunun 12.pini lojik 1'e set edildi.
	  GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  GPIO_SetBits(GPIOD, GPIO_Pin_15);

	  for(int i=0; i<1680000; i++);

	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);		// D portunun 12.pini lojik 0'a �ekildi.
	  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	  GPIO_ResetBits(GPIOD, GPIO_Pin_15);

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
