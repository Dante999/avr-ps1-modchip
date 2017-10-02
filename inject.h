/*
 * injection.h
 *
 *  Created on: 07.09.2017
 *      Author: dante999
 */

#ifndef INJECT_H_
#define INJECT_H_

#include <avr/io.h>


#define REGION_EUROPE		0
#define REGION_AMERICA		1
#define REGION_JAPAN		2




//void inject_SCEX(char region);

void inject_region(uint8_t region);

//void inject_SCEE();


#endif /* INJECT_H_ */
