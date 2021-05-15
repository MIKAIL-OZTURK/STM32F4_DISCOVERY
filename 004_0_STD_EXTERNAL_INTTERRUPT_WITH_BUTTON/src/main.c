#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;		// LED'ler ve Buton ayarlar� i�in nesne olu�turduk.
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config()		// GPIO portlar� i�in konfig�rasyonlar ayarlar� -->
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		// D portu i�in AHB1 hatt�n� aktif ettik
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// A portu i�in AHB1 hatt�n� aktif ettik

	// BUTON AYARLARI -->
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// LED AYARLARI -->
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void EXTI_Config()		// EXTERNAL INTERRUPT i�in konfig�rasyon ayarlar� -->
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 	// External Interrupt i�in APB2 hatt�n� aktif ettik.

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Line hatt�n� aktif ettik.
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Kesme i�lemi yapaca��m�zdan Interrupt modunu se�iyoruz.
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;				// Butonu harici kesme olarak kullanaca��m�zdan Line0 yapt�k.
	//											  		   ��nk� 0.pindekiler (Buton = A Portu 0.Pin) Line0'a ba�l�d�r.
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// Kesme i�lemini y�kselen kenarda yapmak istiyoruz.

	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hatt�n� aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;		//	External interrupt kanal�n� se�iyoruz.EXTI + Line0 = EXTI0
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// Birden fazla interrupt i�lemi i�in kullan�l�r.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// Birden fazla interrupt i�lemi i�in kullan�l�r.

	NVIC_Init(&NVIC_InitStruct);
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()		// Kesme i�lemi ger�ekle�ti�i zaman yap�lacak i�lemler -->
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	// �nterupt'a girip girmedi�in kontrol ediyoruz. E�er girdiyse -->
	{
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  	 delay(3360000);
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  	 delay(3360000);
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	  	 EXTI_ClearITPendingBit(EXTI_Line0);	// Interrupt'� s�rekli kullanabilmemiz i�in bayara�� temizledik.
	}
}
int main(void)
{
	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
