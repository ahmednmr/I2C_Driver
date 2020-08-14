/*
 * i2c.c
 *
 *  Created on: Mar 25, 2019
 *      Author: Nmr
 */
#include<avr/io.h>
#include<avr/delay.h>
#include"i2c.h"


void TWI_Init(void)
{

//	TWCR = 0;
//	TWBR= TWBR_val;

TWSR=0;
TWBR=0x47;             //50khz
TWCR=0x04;


}


void TWI_Start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 	//Send START condition
	while (!(TWCR & (1<<TWINT)) );   		//Wait for TWINT flag set. This indicates that the

	}



void TWI_Sendbyte(uint8_t c_byte)
{
	TWDR = c_byte;
	TWCR = (1<<TWINT) |(1<<TWEN);	   //Load SLA_W into TWDR Register. Clear TWINT bit
	                                   //in TWCR to start transmission of data

	while (!(TWCR & (1<<TWINT)));   		//Wait for TWINT flag set. This indicates that the

	}

uint8_t TWI_ReceiveData_ACK(void)
{

	TWCR = (1<<TWEA)|(1<<TWINT)|(1<<TWEN);

	while (!(TWCR & (1<<TWINT)));		//Wait for TWINT flag set. This indicates that the

	return TWDR;

}


uint8_t TWI_ReceiveData_NACK(void)
{

	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));   		//Wait for TWINT flag set. This indicates that the

	return TWDR;


}

void TWI_Stop(void)
{
	TWCR =  (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	  //Transmit STOP condition
}



