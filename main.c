/*
 * main.c
 *
 *  Created on: 06.09.2017
 *      Author: dante999
 */

#include "main.h"
#include <util/delay.h>
#include "inject.h"
#include "debug.h"



/*
 * Pinout on Playstation
 *
 * GATE	-	IC732.Pin-5		(WFCK)
 * DATA	-	IC732.Pin-42	(CEO)
 * SUBQ	-	IC304.Pin-24	(SUBQ)
 * SQCK	-	IC304.Pin-26	(SQCK)
 *
 *
 *
 */


// the delay in milliseconds between the playstation is powered up and the first
// initial injection starts
#define DELAY_AFTER_BOOTUP_MS	4300

// default value: 70
// works fine on my SCPH-7502
#define REPEAT_INJECTION		70










void init() {

	REG_DDR  = 0x00;			// all pins as inputs
	REG_PORT = 0x00;			// no pullup -> high impedance

	debug_init();

}



void injectAfterBootup() {


	_delay_ms(DELAY_AFTER_BOOTUP_MS);											// give the playstation time before you inject


	REG_DDR  &= ~(1<<PIN_DATA);
	REG_PORT &= ~(1<<PIN_DATA);


	inject_region_code();


	uint8_t i = 0;

	for(i=0; i < REPEAT_INJECTION; i++) {
		inject_region_code();
	}




}


int main() {

	init();

	injectAfterBootup();

	


	while(1) {





	}

}





