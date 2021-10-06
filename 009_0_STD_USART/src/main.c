#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char str[50];

GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		// USART2 için clock hattýný aktif ettik.

	USART_InitStruct.USART_BaudRate = 9600;		// BaudRate ->  Veri gönderme hýzýdýr. Aldýðýmýýz ve gönderdiðimiz veri hýzlarý eþit olmalýdýr.
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Donaným akýþ kontrolünü belirtir.Akýþ Kontrolü,
	//	yavaþ ve hýzlý cihazlarýn veri kaybetme riski olmadan USART üzerinden birbirleriyle iletiþim kurmasý için bir yöntemdir.Akýþ kontrolü, vericiye iletimi
	//	durdurmasý (duraklatma) veya baþlatmasý (devam ettirmesi) gerektiðini bildirmek için ekstra sinyal saðlar. Donaným akýþ kontrolü ise kablolardaki mantýk
	//	seviyesinin, vericinin veri göndermeye devam edip etmeyeceðini veya duracaðýný belirlediði ekstra kablolar kullanýr.
	USART_InitStruct.USART_Mode = USART_Mode_Tx; 	// USART modülünü hangi modda kullanacaðýmýzý seçiyoruz.Tx - Mesaj Gönderme (PC->MCU) ~ Rx - Mesaj Alma (MCU->PC)
	USART_InitStruct.USART_Parity = USART_Parity_No; // Veri bitlerinde herhangi bir hata olup olmadýðýný alýcý cihaza bildirir.
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// Haberleþmenin sonlanmasý için gereken 'Stop Biti'nin deðeri kaç bit olsun? 1 Bit olarak ayarladýk.
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // Veri keliLme uzunluðunu belirtiriz.

	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);		// USART bir çevresel birimi olduðundan aktif ediyoruz.
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

int main(void)
{
	GPIO_Config();
	USART_Config();
  while (1)
  {
	  sprintf(str, "Hello World\n");
	  USART_Puts(USART2, str);			// "Hello World" --> MCU
	  delay(1680000);
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
