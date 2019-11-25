/*******************************************************************************
 *
 * avr-ps1-modchip
 * Copyright (C) 2019 Matthias Escher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include "main.h"

#include <util/delay.h>

#include "debug.h"
#include "inject.h"


/**
 * the delay in milliseconds between the playstation is powered up and the first
 * initial injection starts
 **/
#define DELAY_AFTER_BOOTUP_MS 4300

/*******************************************************************************
 * @brief   initialize board peripherals
 *
 * @param   none
 *
 * @return  none
 *
 *******************************************************************************/
void init()
{

	REG_DDR  = 0x00; // all pins as inputs
	REG_PORT = 0x00; // no pullup -> high impedance

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
int main()
{

	init();

	_delay_ms(DELAY_AFTER_BOOTUP_MS);
	inject_sequence();

	while (1) {
		// at the moment nothing to do...
	}
}
