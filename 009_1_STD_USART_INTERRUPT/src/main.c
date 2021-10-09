#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char rx_buff[50];
int i=0;

GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);		// PA2 Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);		// PA3 Rx

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		// USART2 için clock hattýný aktif ettik.

	USART_InitStruct.USART_BaudRate = 9600;		// BaudRate ->  Verimizin saniyede ne kadarlýk byte’ýný taþýyacaðýný belirlememize yarar.
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Donaným akýþ kontrolünü belirtir.Akýþ Kontrolü,
	//	yavaþ ve hýzlý cihazlarýn veri kaybetme riski olmadan USART üzerinden birbirleriyle iletiþim kurmasý için bir yöntemdir.Akýþ kontrolü, vericiye iletimi
	//	durdurmasý (duraklatma) veya baþlatmasý (devam ettirmesi) gerektiðini bildirmek için ekstra sinyal saðlar. Donaným akýþ kontrolü ise kablolardaki mantýk
	//	seviyesinin, vericinin veri göndermeye devam edip etmeyeceðini veya duracaðýný belirlediði ekstra kablolar kullanýr.
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 	// USART modülünü hangi modda kullanacaðýmýzý seçiyoruz.Tx - Mesaj Gönderme (PC->MCU) ~ Rx - Mesaj Alma (MCU->PC)
	USART_InitStruct.USART_Parity = USART_Parity_No; // Veri bitlerinde herhangi bir hata olup olmadýðýný alýcý cihaza bildirir.
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// Haberleþmenin sonlanmasý için gereken 'Stop Biti'nin deðeri kaç bit olsun? 1 Bit olarak ayarladýk.
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // Veri keliLme uzunluðunu belirtiriz.

	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);		// USART bir çevresel birimi olduðundan aktif ediyoruz.

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		// Etkinleþtirilecek veya devre dýþý býrakýlacak USART kesme kaynaklarýný belirtir.
														// USART_IT_RXNE -> MCU'ya bir mesaj aldýðýnda Interrupt'a girer.
}

void NVIC_Config()
{
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;		// Etkinleþtirilecek veya devre dýþý býrakýlacak IRQ kanalýný belirtir
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// NVIC_IRQChannel'da tanýmlanan IRQ kanalýnýn etkinleþtirilip etkinleþtirilmeyeceðini belirtir.
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// NVIC_IRQChannel'da belirtilen IRQ kanalý için ön alým önceliðini belirtir
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannel'da belirtilen IRQ kanalý için alt öncelik düzeyini belirtir.

	NVIC_Init(&NVIC_InitStruct);
}

void USART_Puts(USART_TypeDef* USARTx, volatile char *s)		// USART Mesaj Gönderme Fonksiyonu
{
	while(*s)
	{
		while(!(USARTx->SR & 0x00000040));

		USART_SendData(USARTx, *s);
		*s++;
	}
}

void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE))		// USART2'nin RXNE(Mesaj gelme) bayaraðýný kontrol ettik, eðer mesaj geldiyse -->
	{
		char rx_buffer = USART_ReceiveData(USART2);		// USART2'den gelen mesajý char bir deðiþkene atadýk.

		if(rx_buffer != '\n' && i < 50)		// rx_buffer deðiþkeni boþ deðilse -->
		{
			rx_buff[i] = rx_buffer;		// rx_buffer'daki mesajý rx_buff dizisine atadýk.
			i++;
		}
		else
		{
			rx_buff[i] = rx_buffer;			// Veri akýþý bittiðinde diziyi sonlandýr.
			i = 0;
			USART_Puts(USART2, rx_buff); 	// USART Mesaj Gönderme Fonksiyonu (Satýr 59-68)

			for(int a = 0; a<50; a++)
				rx_buff[a] = '\0';
		}
	}
}

int main(void)
{
	GPIO_Config();
	USART_Config();
	NVIC_Config();
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
