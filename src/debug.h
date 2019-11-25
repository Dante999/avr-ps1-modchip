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

#include <avr/io.h>

#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUG_LOW 0
#define DEBUG_HIGH 1
#define DEBUG_TOGGLE 2

void debug_init();
void debug_set_pin(uint8_t mode);

#endif /* DEBUG_H_ */
