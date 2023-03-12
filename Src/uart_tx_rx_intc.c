/*
 * uart_tx_rx_intc.c
 *
 *  Created on: Mar 7, 2023
 *      Author: Admin
 */

#include<stdio.h>
#include<string.h>
#include "stm32f4.h"
#include "stm32_uart.h"
#include "stm32_gpio.h"

char rx_buf[7] ;

int a =0, b= 0;

USART_Handle_t usart2_handle;

void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_TXRX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
}

void USART2_GPIOInit(void)
{
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode =7;

	//USART2 TX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios);

	//USART2 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios);
}

int main(void)
{
	USART2_GPIOInit();
	USART2_Init();
	USART_IRQInterruptConfig(IRQ_NO_USART2,ENABLE);
	USART_PeripheralControl(USART2,ENABLE);

	 while(1)
	 {
		 while ( USART_ReceiveDataIT(&usart2_handle,(uint8_t *)rx_buf,6) != USART_READY );
		 USART_SendDataIT(&usart2_handle,(uint8_t*)rx_buf,6);
	 }
}

void USART2_IRQHandler(void)
{
	USART_IRQHandling(&usart2_handle);
}


void USART_ApplicationEventCallback( USART_Handle_t *pUSARTHandle,uint8_t ApEv)
{
   if(ApEv == USART_EVENT_RX_CMPLT)
   {
	   a =1;

   }else if (ApEv == USART_EVENT_TX_CMPLT)
   {
	   b =1;
   }
}
