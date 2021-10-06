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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		// USART2 i�in clock hatt�n� aktif ettik.

	USART_InitStruct.USART_BaudRate = 9600;		// BaudRate ->  Veri g�nderme h�z�d�r. Ald���m��z ve g�nderdi�imiz veri h�zlar� e�it olmal�d�r.
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Donan�m ak�� kontrol�n� belirtir.Ak�� Kontrol�,
	//	yava� ve h�zl� cihazlar�n veri kaybetme riski olmadan USART �zerinden birbirleriyle ileti�im kurmas� i�in bir y�ntemdir.Ak�� kontrol�, vericiye iletimi
	//	durdurmas� (duraklatma) veya ba�latmas� (devam ettirmesi) gerekti�ini bildirmek i�in ekstra sinyal sa�lar. Donan�m ak�� kontrol� ise kablolardaki mant�k
	//	seviyesinin, vericinin veri g�ndermeye devam edip etmeyece�ini veya duraca��n� belirledi�i ekstra kablolar kullan�r.
	USART_InitStruct.USART_Mode = USART_Mode_Tx; 	// USART mod�l�n� hangi modda kullanaca��m�z� se�iyoruz.Tx - Mesaj G�nderme (PC->MCU) ~ Rx - Mesaj Alma (MCU->PC)
	USART_InitStruct.USART_Parity = USART_Parity_No; // Veri bitlerinde herhangi bir hata olup olmad���n� al�c� cihaza bildirir.
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// Haberle�menin sonlanmas� i�in gereken 'Stop Biti'nin de�eri ka� bit olsun? 1 Bit olarak ayarlad�k.
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // Veri keliLme uzunlu�unu belirtiriz.

	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);		// USART bir �evresel birimi oldu�undan aktif ediyoruz.
}

void USART_Puts(USART_TypeDef* USARTx, volatile char *s)		// USART Mesaj G�nderme Fonksiyonu
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
