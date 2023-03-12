/*
 * i2c_rx.c
 *
 *  Created on: Mar 12, 2023
 *      Author: Admin
 */


#include<stdio.h>
#include<string.h>
#include "stm32f4.h"
#include "stm32_i2c.h"
#include "stm32_gpio.h"

#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68

I2C_Handle_t I2C1Handle;

uint8_t rcv_buf[32];
uint8_t Data_receive_1;

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

void I2C1_GPIOInits(void)
{
  GPIO_Handle_t I2CPins;

  I2CPins.pGPIOx = GPIOB;
  I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
  I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
  I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
  I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
  I2CPins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  //scl
  I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
  GPIO_Init(&I2CPins);
  //sda
  I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
  GPIO_Init(&I2CPins);
}
void I2C1_Inits(void)
{
  I2C1Handle.pI2Cx = I2C1;
  I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
  I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
  I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
  I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
  I2C_Init(&I2C1Handle);
}


int main(void)
{
	  I2C1_GPIOInits();
	  I2C1_Inits();
	  I2C_PeripheralControl(I2C1,ENABLE);
	  while(1)
	   {
		  //Receive 1 bit
		  	 uint8_t data = 0x01;
		     I2C_MasterSendData(&I2C1Handle,&data,1,SLAVE_ADDR,I2C_ENABLE_SR);
		     I2C_MasterReceiveData(&I2C1Handle,&Data_receive_1,1,SLAVE_ADDR,I2C_ENABLE_SR);

		     for(uint32_t i = 0 ; i < 500000/2 ; i ++); // delay

		  //Receive bit > 1
		     data = 0x02;
			 I2C_MasterSendData(&I2C1Handle,&data,1,SLAVE_ADDR,I2C_ENABLE_SR);
			 I2C_MasterReceiveData(&I2C1Handle,rcv_buf,14,SLAVE_ADDR,I2C_ENABLE_SR);
			 while(1);
	   }

}

