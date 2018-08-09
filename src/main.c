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

    _delay_ms(DELAY_AFTER_BOOTUP_MS);
    inject_sequence();

    while(1) {
        // at the moment nothing to do...
    }

}

