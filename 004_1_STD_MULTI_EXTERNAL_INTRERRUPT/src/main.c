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

void EXTI_Config()		// EXTERNAL INTERRUPT için konfigürasyon ayarlarý -->
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); 		// External Interrupt için APB2 hattýný aktif ettik.

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;				// Line hattýný aktif ettik.
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Kesme iþlemi yapacaðýmýzdan Interrupt modunu seçiyoruz.
	EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line2;// Butonu harici kesme olarak kullanacaðýmýzdan Line1 ve
	//	Line2'ye baðladýk. Çünkü 1.pindekiler Line1'e, 2.pindekiler Line2'ye baðlýdýr.
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	// Kesme iþlemini yükselen kenarda yapmak istiyoruz.

	EXTI_Init(&EXTI_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		// Birden fazla kesme iþlemi olduðunda öncelik için
														// kullanýlan fonksiyondur.
	// 1.BUTON ÝÇÝN INTERRUPT AYARLARI -->
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hattýný aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;		//	External interrupt kanalýný seçiyoruz.EXTI + Line1 = EXTI1
	// Hangi buton öncelik olmasýný istiyorsak ona düþük deðer yazmalýyýz -->
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// Öncelik buton olduðundan düþük deðer veriyoruz.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannelPreemptionPriority deðeri eþit olduðu
	// takdirde bu deðer esas alýnýr.NVIC_IRQChannelPreemptionPriority deðerleri farklý olduðundan þu anlýk öenmi yok

	NVIC_Init(&NVIC_InitStruct);

	// 2.BUTON ÝÇÝN INTERRUPT AYARLARI -->
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		//	NVIC hattýný aktif ediyoruz.
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;		//	External interrupt kanalýný seçiyoruz.EXTI + Line2 = EXTI2
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	// Öncelik butonu olmadýðýndan diðer butonun
	//	NVIC_IRQChannelPreemptionPriority deðerinde yüksek bir deðer veriyoruz.
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannelPreemptionPriority deðeri eþit olduðu
	// takdirde bu deðer esas alýnýr.NVIC_IRQChannelPreemptionPriority deðerleri farklý olduðundan þu anlýk öenmi yok

	NVIC_Init(&NVIC_InitStruct);
}

void delay(uint32_t time)
{
	while(time--);
}

void EXTI1_IRQHandler()		// 1.Buton için kesme iþlemi gerçekleþtiði zaman yapýlacak iþlemler -->
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	// Ýnterupt'a girip girmediðin kontrol ediyoruz. Eðer girdiyse -->
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

	  	 EXTI_ClearITPendingBit(EXTI_Line1);	// Interrupt'ý sürekli kullanabilmemiz için bayraðý temizledik.
	}
}

void EXTI2_IRQHandler()		// 2.Buton için kesme iþlemi gerçekleþtiði zaman yapýlacak iþlemler -->
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)	// Ýnterupt'a girip girmediðin kontrol ediyoruz. Eðer girdiyse -->
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

	  	 EXTI_ClearITPendingBit(EXTI_Line2);	// Interrupt'ý sürekli kullanabilmemiz için bayraðý temizledik.
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
