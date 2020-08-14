/*
 * main.c
 *
 *  Created on: Mar 24, 2019
 *      Author: Nmr
 */
#include<avr/io.h>
#include<avr/delay.h>
#include"i2c.h"
#include"UART.h"

#define write_time   0
#define read_time   1



int main()
{


	uint8_t month_day=0,month=0,year=0,seconds,mins,hours,week_day;
	TWI_Init();
	init_UART();
	UART_SEND_string("start");

	_delay_ms(1000);
	while(1)
	{


#if write_time
		// write time and date

		//				TWI_Start();
		//				TWI_Sendbyte(0b11010000);        // send salve add with operation write
		//				TWI_Sendbyte(0x07);             //control register add
		//				TWI_Sendbyte(0x00);             // write 0 to control Register
		//				TWI_Stop();
		//
		//				_delay_ms(100);
		TWI_Start();
		TWI_Sendbyte(0b11010000);        // send salve add with operation write
		TWI_Sendbyte(0x00);              // goto address 0 in Real time clock
		TWI_Sendbyte(0x00);              //send seconds
		TWI_Sendbyte(0x32);              //send  minutes
		TWI_Sendbyte(0x01);              //send   hours
		TWI_Sendbyte(0x01);              //send  day in the week
		TWI_Sendbyte(0x15);              //send  day in the month
		TWI_Sendbyte(0x08);              //send  month
		TWI_Sendbyte(0x20);              //send  year
		TWI_Stop();


		_delay_ms(1000);


#endif


#if read_time
		// read time and date
		// send dummy writing
		TWI_Start();
		TWI_Sendbyte(0b11010000);
		TWI_Sendbyte(0x00);
		TWI_Stop();


		// send read
		_delay_ms(100);
		TWI_Start();
		TWI_Sendbyte(0b11010001);
		seconds=TWI_ReceiveData_ACK();         //read sec
		mins=TWI_ReceiveData_ACK();         //read mins
		hours=TWI_ReceiveData_ACK();         //read hours
		week_day=TWI_ReceiveData_ACK();         //read week-day
		month_day=TWI_ReceiveData_ACK();         //read month-day
		month=TWI_ReceiveData_ACK();         //read month
		year=TWI_ReceiveData_NACK();         //read year

		TWI_Stop();
		UART_SEND_string("\r\n\r\n  seconds   :");
		 UART_SEND_number_BCD(seconds);
		UART_SEND_string("\r\n  mins      :");
		 UART_SEND_number_BCD(mins);
		UART_SEND_string("\r\n  hours     :");
		 UART_SEND_number_BCD(hours);

		UART_SEND_string("\r\n  week_day  :");
		 UART_SEND_number_BCD(week_day);

		UART_SEND_string("\r\n  month_day :");
		 UART_SEND_number_BCD(month_day);
		UART_SEND_string("\r\n  month     :");
		 UART_SEND_number_BCD(month);
		UART_SEND_string("\r\n  year      :");
		 UART_SEND_number_BCD(year);





		_delay_ms(4000);
#endif


	}

	return 0;

}




