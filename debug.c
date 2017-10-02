/*
 * debug.c
 *
 *  Created on: 01.10.2017
 *      Author: dante999
 */

#include <avr/io.h>
#include "main.h"



void debug_init() {
	REG_DDR |= (1<<PIN_DEBUG);
}

void debug_setPinHigh() {
	REG_PORT |= (1<<PIN_DEBUG);
}

void debug_setPinLow() {
	REG_PORT &= ~(1<<PIN_DEBUG);
}

void debug_togglePin() {
	REG_PORT ^= (1<<PIN_DEBUG);
}
