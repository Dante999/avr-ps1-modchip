/*
 * main.h
 *
 *  Created on: 07.09.2017
 *      Author: dante999
 */

#ifndef MAIN_H_
#define MAIN_H_

#define AVR_ATtiny13

#include <avr/io.h>
//#include <avr/iotn13.h>

#define REG_DDR		DDRB
#define REG_PIN		PINB
#define REG_PORT	PORTB

#define PIN_DEBUG	PB0
#define PIN_SUBQ	PB1
#define PIN_SQCK	PB2
#define PIN_GATE	PB3
#define PIN_DATA	PB4


#endif /* MAIN_H_ */
