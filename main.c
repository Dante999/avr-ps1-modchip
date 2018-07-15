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

/**
 * the delay in milliseconds between the playstation is powered up and the first
 * initial injection starts
**/
#define DELAY_AFTER_BOOTUP_MS   4300

/**
 * default value: 70
 * works fine on my SCPH-7502
**/
#define REPEAT_INJECTION        70



/*******************************************************************************
 * @brief   initialize board peripherals
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void init() {

    REG_DDR  = 0x00;                        // all pins as inputs
    REG_PORT = 0x00;                        // no pullup -> high impedance

    debug_init();
}


/*******************************************************************************
 * @brief   call this function at the beginning to inject right after bootup
 *
 * @param   none
 *
 * @return  none
*******************************************************************************/
void injectAfterBootup() {

    _delay_ms(DELAY_AFTER_BOOTUP_MS);       // give the playstation time before you inject

    REG_DDR  &= ~(1<<PIN_DATA);
    REG_PORT &= ~(1<<PIN_DATA);

    inject_region_code();


    uint8_t i = 0;

    for(i=0; i < REPEAT_INJECTION; i++) {
        inject_region_code();
    }

}


/*******************************************************************************
 * @brief   the main function
 *
 * 
 * @param   none
 * 
 * @return  none
 *
*******************************************************************************/
int main() {

    init();
    injectAfterBootup();

    while(1) {
        // nothing to do at the moment
    }

}

