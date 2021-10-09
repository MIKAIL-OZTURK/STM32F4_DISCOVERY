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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		// USART2 i�in clock hatt�n� aktif ettik.

	USART_InitStruct.USART_BaudRate = 9600;		// BaudRate ->  Verimizin saniyede ne kadarl�k byte��n� ta��yaca��n� belirlememize yarar.
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Donan�m ak�� kontrol�n� belirtir.Ak�� Kontrol�,
	//	yava� ve h�zl� cihazlar�n veri kaybetme riski olmadan USART �zerinden birbirleriyle ileti�im kurmas� i�in bir y�ntemdir.Ak�� kontrol�, vericiye iletimi
	//	durdurmas� (duraklatma) veya ba�latmas� (devam ettirmesi) gerekti�ini bildirmek i�in ekstra sinyal sa�lar. Donan�m ak�� kontrol� ise kablolardaki mant�k
	//	seviyesinin, vericinin veri g�ndermeye devam edip etmeyece�ini veya duraca��n� belirledi�i ekstra kablolar kullan�r.
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 	// USART mod�l�n� hangi modda kullanaca��m�z� se�iyoruz.Tx - Mesaj G�nderme (PC->MCU) ~ Rx - Mesaj Alma (MCU->PC)
	USART_InitStruct.USART_Parity = USART_Parity_No; // Veri bitlerinde herhangi bir hata olup olmad���n� al�c� cihaza bildirir.
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	// Haberle�menin sonlanmas� i�in gereken 'Stop Biti'nin de�eri ka� bit olsun? 1 Bit olarak ayarlad�k.
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // Veri keliLme uzunlu�unu belirtiriz.

	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);		// USART bir �evresel birimi oldu�undan aktif ediyoruz.

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);		// Etkinle�tirilecek veya devre d��� b�rak�lacak USART kesme kaynaklar�n� belirtir.
														// USART_IT_RXNE -> MCU'ya bir mesaj ald���nda Interrupt'a girer.
}

void NVIC_Config()
{
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;		// Etkinle�tirilecek veya devre d��� b�rak�lacak IRQ kanal�n� belirtir
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// NVIC_IRQChannel'da tan�mlanan IRQ kanal�n�n etkinle�tirilip etkinle�tirilmeyece�ini belirtir.
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;	// NVIC_IRQChannel'da belirtilen IRQ kanal� i�in �n al�m �nceli�ini belirtir
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;			// NVIC_IRQChannel'da belirtilen IRQ kanal� i�in alt �ncelik d�zeyini belirtir.

	NVIC_Init(&NVIC_InitStruct);
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

void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE))		// USART2'nin RXNE(Mesaj gelme) bayara��n� kontrol ettik, e�er mesaj geldiyse -->
	{
		char rx_buffer = USART_ReceiveData(USART2);		// USART2'den gelen mesaj� char bir de�i�kene atad�k.

		if(rx_buffer != '\n' && i < 50)		// rx_buffer de�i�keni bo� de�ilse -->
		{
			rx_buff[i] = rx_buffer;		// rx_buffer'daki mesaj� rx_buff dizisine atad�k.
			i++;
		}
		else
		{
			rx_buff[i] = rx_buffer;			// Veri ak��� bitti�inde diziyi sonland�r.
			i = 0;
			USART_Puts(USART2, rx_buff); 	// USART Mesaj G�nderme Fonksiyonu (Sat�r 59-68)

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
