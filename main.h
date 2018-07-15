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


/*
 * Pinout on Playstation
 *
 * GATE - IC732.Pin-5  (WFCK)
 * DATA - IC732.Pin-42 (CEO)
 * SUBQ - IC304.Pin-24 (SUBQ)
 * SQCK - IC304.Pin-26 (SQCK)
 *
 */


#define REG_DDR     DDRB
#define REG_PIN     PINB
#define REG_PORT    PORTB

#define PIN_DEBUG   PB0
#define PIN_SUBQ    PB1
#define PIN_SQCK    PB2
#define PIN_GATE    PB3
#define PIN_DATA    PB4


#endif /* MAIN_H_ */
