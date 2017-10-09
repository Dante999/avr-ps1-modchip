/*
 * debug.c
 *
 *  Created on: 01.10.2017
 *      Author: dante999
 */

#include <avr/io.h>
#include "main.h"


/*
 * initialize the debug I/O pin
 * 
 * @param	none
 * 
 * @return	none
 *
*/
void debug_init() {
	REG_DDR |= (1<<PIN_DEBUG);
}


/*
 * sets the debug pin to HIGH
 * 
 * @param	none
 *
 * @return	none
 *  
*/
void debug_setPinHigh() {
	REG_PORT |= (1<<PIN_DEBUG);
}


/* 
 * sets the debug pin to LOW
 * 
 * @param	none
 * 
 * @return	none
*/
void debug_setPinLow() {
	REG_PORT &= ~(1<<PIN_DEBUG);
}


/*
 * toggles the debug pin
 * 
 * if the pin is currently HIGH, it changes to LOW and vice versa
 * 
 * @param	none
 * 
 * @return	none
*/
void debug_togglePin() {
	REG_PORT ^= (1<<PIN_DEBUG);
}
