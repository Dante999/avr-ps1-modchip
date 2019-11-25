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

#include "debug.h"

#include "main.h"

/*******************************************************************************
 * @brief   initialize the debug I/O pin
 *
 * simply sets the debug-pin as an output with an initial LOW-level
 *
 * @param   none
 *
 * @return  none
 *
 ******************************************************************************/
void debug_init()
{
	REG_DDR |= (1 << PIN_DEBUG);
	REG_PORT &= ~(1 << PIN_DEBUG);
}

/*******************************************************************************
 * @brief   controls the debug pin
 *
 * @param   mode    DEBUG_LOW     sets the pin to a low-level
 *                  DEBUG_HIGH    sets the pin to a high-level
 *                  DEBUG_TOGGLE  toggles the pin
 *
 * @return  none
 *
 ******************************************************************************/
void debug_set_pin(uint8_t mode)
{

	switch (mode) {

	case DEBUG_LOW:
		REG_PORT &= ~(1 << PIN_DEBUG);
		break;

	case DEBUG_HIGH:
		REG_PORT |= (1 << PIN_DEBUG);
		break;

	case DEBUG_TOGGLE:
		REG_PORT ^= (1 << PIN_DEBUG);
		break;
	}
}
