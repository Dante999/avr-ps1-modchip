/*
 * injection.c
 *
 *  Created on: 07.09.2017
 *      Author: dante999
 */



#include "inject.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"
#include "debug.h"

#define REGION_LENGTH			44

#define BIT_LENGTH_MS			4

#define DELAY_AFTER_INJECTION	90

#define TIMER_OCR_OFFSET		-7



//SCEE: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01011101 00
static char SCEEData[44] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

//SCEA: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01111101 00
static char SCEAData[44] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

//SCEI: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01101101 00
static char SCEIData[44] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

// milliseconds counter variable
volatile uint8_t ms_counter = 0;





void inject_startTimer() {

	sei();

	TCCR0A |= (1<<WGM01);									// CTC-Mode

//	TCCR0B |= (1<<CS02) | (1<<CS00) ;					// prescaler 1024 ->  4,6875 KHz (213,133us)
//	TCCR0B |= (1<<CS02) | (1<<CS00) ;					// prescaler 256  -> 18,7500 KHz ( 53,333us)
	TCCR0B |= (1<<CS01) | (1<<CS00) ;					// prescaler  64  -> 75,0000 KHz ( 13,333us)

	TIMSK0 |= (1<<OCIE0A);									// enable compare A interrupt

	OCR0A = 75+TIMER_OCR_OFFSET;							// set compare register

	ms_counter = 0;											// set millisecond-counter back to zero

}

void inject_stopTimer() {
	TCCR0B = 0x00;
	cli();
}


ISR(TIM0_COMPA_vect)
{
	ms_counter++;
}

void inject_write_high_bit() {

	debug_setPinHigh();

	REG_DDR &= ~(1<<PIN_GATE);

	if( REG_PIN & (1<<PIN_GATE) ) {
		REG_DDR  &=  ~(1<<PIN_DATA);						// set data-Pin as Output
		REG_PORT &= ~(1<<PIN_DATA);						// set the data-Pin LOW
	}
	else {
		REG_DDR  |=  (1<<PIN_DATA);						// set data-Pin as Output
		REG_PORT &= ~(1<<PIN_DATA);						// set the data-Pin LOW
	}


}


void inject_write_low_bit() {

	debug_setPinLow();
	REG_DDR  |=  (1<<PIN_DATA);						// set data-Pin as Output
	REG_PORT &= ~(1<<PIN_DATA);						// set the data-Pin LOW
}

void inject_region(uint8_t region) {

	uint8_t	i		= 0;
	char	*data 	= 0;

	switch(region) {

	case REGION_EUROPE:
		data = SCEEData;
		break;

	case REGION_AMERICA:
		data = SCEAData;
		break;

	case REGION_JAPAN:
		data = SCEIData;
		break;

	default:
		data = SCEEData;
		break;

	}

	inject_startTimer();



//	REG_DDR  |=  (1<<PIN_GATE);
//	REG_PORT &= ~(1<<PIN_GATE);

	for( i=0; i < REGION_LENGTH; i++) {

		ms_counter = 0;

		while(ms_counter < 4) {


			if( data[i] == 0) {
				inject_write_low_bit();
	//			debug_setPinLow();

			}
			else {
				inject_write_high_bit();
	//			debug_setPinHigh();

			}

		}

	}

	_delay_ms(DELAY_AFTER_INJECTION);


	REG_DDR  &= ~(1<<PIN_DATA);								// data-pin high impedanze
	REG_PORT &= ~(1<<PIN_DATA);								// deactivate pullups

	inject_stopTimer();

}
