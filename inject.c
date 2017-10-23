#include "inject.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "main.h"
#include "debug.h"

#define REGION_LENGTH					44
#define TIMER_OCR_OFFSET				-5

#define BIT_LENGTH_MS					4
#define DELAY_AFTER_INJECTION_MS		90




#ifdef  REGION_EUROPE
	//SCEE 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01011101 00
	static char SCEXData[REGION_LENGTH] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

#elif defined REGION_AMERICA
	//SCEA: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01111101 00
	static char SCEXData[REGION_LENGTH] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};


#elif defined REGION_JAPAN
	//SCEI: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01101101 00
	static char SCEXData[REGION_LENGTH] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

#else
	#error "Please define a Region!"
#endif







// milliseconds counter variable
volatile uint8_t m_counter_ms = 0;



// using a F_CPU from 9.6MHz
void inject_startTimer() {

	sei();


	TCCR0A |= (1<<WGM01);							// CTC-Mode

//	TCCR0B |= (1<<CS02) | (1<<CS00) ;			// prescaler 1024 ->   9,375 KHz (106,667us)
//	TCCR0B |= (1<<CS02) | (1<<CS00) ;			// prescaler 256  ->  37,500 KHz ( 26,667us)
	TCCR0B |= (1<<CS01) | (1<<CS00) ;			// prescaler  64  -> 150,000 KHz (  6,667us)

	TIMSK0 |= (1<<OCIE0A);							// enable compare A interrupt

	OCR0A = 149+TIMER_OCR_OFFSET;					// set compare register

	m_counter_ms = 0;									// set millisecond-counter back to zero

}

void inject_stopTimer() {
	TIMSK0 &= ~(1<<OCIE0A);
}


ISR(TIM0_COMPA_vect)
{
	m_counter_ms++;
}


void inject_write_high_bit() 
{
	REG_DDR &= ~(1<<PIN_GATE);

	if( REG_PIN & (1<<PIN_GATE) ) {
		REG_DDR  &=  ~(1<<PIN_DATA);				// set data-Pin as Input
		REG_PORT &= ~(1<<PIN_DATA);				// set to high impedance
	}
	else {
		REG_DDR  |=  (1<<PIN_DATA);				// set data-Pin as Output
		REG_PORT &= ~(1<<PIN_DATA);				// set the data-Pin LOW
	}

}


void inject_write_low_bit() 
{
	REG_DDR  |=  (1<<PIN_DATA);					// set data-Pin as Output
	REG_PORT &= ~(1<<PIN_DATA);					// set the data-Pin LOW
}




void inject_region_code() 
{
	uint8_t	i		= 0;


	inject_write_low_bit();

	_delay_ms(DELAY_AFTER_INJECTION_MS);

	inject_startTimer();


	for( i=0; i < REGION_LENGTH; i++) {

		m_counter_ms = 0;

		while(m_counter_ms < BIT_LENGTH_MS) {

			if( SCEXData[i] == 1) {
				inject_write_high_bit();
				debug_set_pin(DEBUG_HIGH);
			}
			else {
				inject_write_low_bit();
				debug_set_pin(DEBUG_LOW);
			}

		}

	}
	

	REG_DDR  &= ~(1<<PIN_DATA);					// data-pin high impedanze
	REG_PORT &= ~(1<<PIN_DATA);					// deactivate pullups
	
	REG_DDR  &= ~(1<<PIN_GATE);
	REG_PORT &= ~(1<<PIN_GATE);

	inject_stopTimer();

}
