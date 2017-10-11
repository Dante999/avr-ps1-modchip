/*
 * debug.c
 *
 *  Created on: 01.10.2017
 *      Author: dante999
 */

#include "main.h"


/*******************************************************************************
 * @brief	initialize the debug I/O pin
 *
 * simply sets the debug-pin as an output with an initial LOW-level
 * 
 * @param	none
 * 
 * @return	none
 *
*******************************************************************************/
void debug_init() {
	REG_DDR  |=  (1<<PIN_DEBUG);
	REG_PORT &= ~(1<<PIN_DEBUG);
}


/*******************************************************************************
 * @brief	sets the debug pin to HIGH
 * 
 * @param	none
 *
 * @return	none
 *  
*******************************************************************************/
void debug_setPinHigh() {
	REG_PORT |= (1<<PIN_DEBUG);
}


/*******************************************************************************
 * @brief	sets the debug pin to LOW
 * 
 * @param	none
 * 
 * @return	none
 *
*******************************************************************************/
void debug_setPinLow() {
	REG_PORT &= ~(1<<PIN_DEBUG);
}


/*******************************************************************************
 * @brief	toggles the debug pin
 * 
 * if the pin is currently HIGH, the function will change the debug-pin to a
 * LOW-Level. if the pin is currently LOW, the function will change the
 * debug-pin to a HIGH-level
 * 
 * @param	none
 * 
 * @return	none
 *
*******************************************************************************/
void debug_togglePin() {
	REG_PORT ^= (1<<PIN_DEBUG);
}
