#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;			// LED ayarlarýný yapmak için GPIO_InitTypeDef veri türünden
											// bir nesne oluþturduk.
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	// Ýþlemci ile D portunun haberleþmesi için
															// AHB1 bus'ýný aktif ettik.

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);			// Yaptýðýmýz ayarlarý D portuna yükledik.
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

	  GPIO_ResetBits(GPIOD, GPIO_Pin_12);		// D portunun 12.pini lojik 0'a çekildi.
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
