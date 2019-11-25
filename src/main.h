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

#ifndef MAIN_H_
#define MAIN_H_

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

#define REG_DDR DDRB
#define REG_PIN PINB
#define REG_PORT PORTB

// pin for debugging (led)
#define PIN_DEBUG PB1

/** IC732 Pins -> CPU **/
#define PIN_GATE PB0
#define PIN_DATA PB2

/** IC304 Pins -> Lens Controller **/
#define PIN_SUBQ PB3
#define PIN_SQCK PB4

#endif /* MAIN_H_ */
