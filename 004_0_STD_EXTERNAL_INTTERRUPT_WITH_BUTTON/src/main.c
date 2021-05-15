#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;		// LED'ler ve Buton ayarlarý için nesne oluþturduk.
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config()		// GPIO portlarý için konfigürasyonlar ayarlarý -->
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		// D portu için AHB1 hattýný aktif ettik
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		// A portu için AHB1 hattýný aktif ettik

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

void EXTI_Config()		// EXTERNAL INTERRUPT için konfigürasyon ayarlarý -->
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 	// External Interrupt için APB2 hattýný aktif ettik.

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Line hattýný aktif ettik.
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Kesme iþlemi yapacaðýmýzdan Interrupt modunu seçiyoruz.
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;				// Butonu harici kesme olarak kullanacaðýmýzdan Line0 yaptýk.
	//											  		   Çünkü 0.pindekiler (Buton = A Portu 0.Pin) Line0'a baðlýdýr.
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// Kesme iþlemini yükselen kenarda yapmak istiyoruz.

	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hattýný aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;		//	External interrupt kanalýný seçiyoruz.EXTI + Line0 = EXTI0
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// Birden fazla interrupt iþlemi için kullanýlýr.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// Birden fazla interrupt iþlemi için kullanýlýr.

	NVIC_Init(&NVIC_InitStruct);
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI0_IRQHandler()		// Kesme iþlemi gerçekleþtiði zaman yapýlacak iþlemler -->
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	// Ýnterupt'a girip girmediðin kontrol ediyoruz. Eðer girdiyse -->
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

	  	 EXTI_ClearITPendingBit(EXTI_Line0);	// Interrupt'ý sürekli kullanabilmemiz için bayaraðý temizledik.
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
