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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 		// External Interrupt i�in APB2 hatt�n� aktif ettik.

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Line hatt�n� aktif ettik.
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Kesme i�lemi yapaca��m�zdan Interrupt modunu se�iyoruz.
	EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line2;// Butonu harici kesme olarak kullanaca��m�zdan Line1 ve
	//	Line2'ye ba�lad�k. ��nk� 1.pindekiler Line1'e, 2.pindekiler Line2'ye ba�l�d�r.
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// Kesme i�lemini y�kselen kenarda yapmak istiyoruz.

	EXTI_Init(&EXTI_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		// Birden fazla kesme i�lemi oldu�unda �ncelik i�in
														// kullan�lan fonksiyondur.
	// 1.BUTON ���N INTERRUPT AYARLARI -->
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hatt�n� aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;		//	External interrupt kanal�n� se�iyoruz.EXTI + Line1 = EXTI1
	// Hangi buton �ncelik olmas�n� istiyorsak ona d���k de�er yazmal�y�z -->
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// �ncelik buton oldu�undan d���k de�er veriyoruz.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannelPreemptionPriority de�eri e�it oldu�u
	// takdirde bu de�er esas al�n�r.NVIC_IRQChannelPreemptionPriority de�erleri farkl� oldu�undan �u anl�k �enmi yok

	NVIC_Init(&NVIC_InitStruct);

	// 2.BUTON ���N INTERRUPT AYARLARI -->
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hatt�n� aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;		//	External interrupt kanal�n� se�iyoruz.EXTI + Line2 = EXTI2
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	// �ncelik butonu olmad���ndan di�er butonun
	//	NVIC_IRQChannelPreemptionPriority de�erinde y�ksek bir de�er veriyoruz.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannelPreemptionPriority de�eri e�it oldu�u
	// takdirde bu de�er esas al�n�r.NVIC_IRQChannelPreemptionPriority de�erleri farkl� oldu�undan �u anl�k �enmi yok

	NVIC_Init(&NVIC_InitStruct);
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI1_IRQHandler()		// 1.Buton i�in kesme i�lemi ger�ekle�ti�i zaman yap�lacak i�lemler -->
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	// �nterupt'a girip girmedi�in kontrol ediyoruz. E�er girdiyse -->
	{
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_All);

	  	 GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  	 delay(3360000);

	  	 EXTI_ClearITPendingBit(EXTI_Line1);	// Interrupt'� s�rekli kullanabilmemiz i�in bayra�� temizledik.
	}
}

void EXTI2_IRQHandler()		// 2.Buton i�in kesme i�lemi ger�ekle�ti�i zaman yap�lacak i�lemler -->
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)	// �nterupt'a girip girmedi�in kontrol ediyoruz. E�er girdiyse -->
	{
		 GPIO_ResetBits(GPIOD, GPIO_Pin_All);

	  	 GPIO_SetBits(GPIOD, GPIO_Pin_15);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_14);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_13);
	  	 delay(3360000);
	  	 GPIO_SetBits(GPIOD, GPIO_Pin_12);
	  	 delay(3360000);

	  	 EXTI_ClearITPendingBit(EXTI_Line2);	// Interrupt'� s�rekli kullanabilmemiz i�in bayra�� temizledik.
	}
}
int main(void)
{
	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	  	 GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
