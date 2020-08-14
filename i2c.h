/*
 * i2c.h
 *
 *  Created on: Mar 25, 2019
 *      Author: Nmr
 */

#ifndef I2C_H_
#define I2C_H_


#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void TWI_Init(void);
void TWI_Start(void);
void TWI_Sendbyte(uint8_t c_byte);
uint8_t TWI_ReceiveData_ACK(void);
uint8_t TWI_ReceiveData_NACK(void);
void TWI_Stop(void);


#endif /* I2C_H_ */
