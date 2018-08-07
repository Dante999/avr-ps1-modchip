#include "inject.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "main.h"
#include "debug.h"

#define REGION_LENGTH               44
#define TIMER_OCR_OFFSET            -5

#define BIT_LENGTH_MS               4
#define DELAY_AFTER_INJECTION_MS    90



/**
 * f_ocnx = (F_CPU) / (2*N*(1+OCRNx)
 */


#define REGION_EUROPE
//#define REGION_AMERICA
//#define REGION_JAPAN

/**
 * default value: 70
 * works fine on my SCPH-7502
**/
#define REPEAT_INJECTION        70


#ifdef  REGION_EUROPE
    //SCEE 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01011101 00
    /*
    static char SCEXData[REGION_LENGTH] = {1, 0,0,1,1,0,1,0,1, 0,0,     // S
                                           1, 0,0,1,1,1,1,0,1, 0,0,     // C
                                           1, 0,1,0,1,1,1,0,1, 0,0,     // E
                                           1, 0,1,0,1,1,1,0,1, 0,0};    // E
*/

   static char SCEXData[44] = {1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0};

#elif defined REGION_AMERICA
    //SCEA: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01111101 00
    static char SCEXData[REGION_LENGTH] = {1, 0,0,1,1,0,1,0,1, 0,0,     // S
                                           1, 0,0,1,1,1,1,0,1, 0,0,     // C
                                           1, 0,1,0,1,1,1,0,1, 0,0,     // E
                                           1, 0,1,1,1,1,1,0,1, 0,0};    // A


#elif defined REGION_JAPAN
   //SCEI: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01101101 00
   static char SCEXData[REGION_LENGTH] = {1, 0,0,1,1,0,1,0,1, 0,0,      // S
                                          1, 0,0,1,1,1,1,0,1, 0,0,      // C
                                          1, 0,1,0,1,1,1,0,1, 0,0,      // E
                                          1, 0,1,1,0,1,1,0,1, 0,0};     // I

#else
   #error "Please define a Region!"
#endif



// milliseconds counter variable
volatile uint8_t m_counter_ms = 0;


/******************************************************************************
 * @brief   starts the timer which counts the milliseconds
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void inject_startTimer() {

    sei();                                  // enable all interrupts

    TCCR0A |= (1<<WGM01);                   // CTC-Mode
    //TCCR0B |= (1<<CS00);                    // no prescaler
    //TCCR0B |= (1<<CS01);                    // prescaler 8
    TCCR0B |= (1<<CS01) | (1<<CS00);        // prescaler 64
    //TCCR0B |= (1<<CS02) | (1<<CS00) ;       // prescaler 256

    TIMSK  |= (1<<OCIE0A);                  // enable compare A interrupt
    OCR0A = 124;                             // interrupt every 1ms

    m_counter_ms = 0;                       // set millisecond-counter back to zero

}


/******************************************************************************
 * @brief   stops the timer which counts the milliseconds
 *
 * @param   none
 *
 * @return  none
 *
******************************************************************************/
void inject_stopTimer() {
    TIMSK  &= ~(1<<OCIE0A);
}


/******************************************************************************
* @brief    interrupt which is called every millisecond
*
* @param    vector (set via macro)
*
* @return   none
*
******************************************************************************/
ISR(TIM0_COMPA_vect) {
    m_counter_ms++;
}


/******************************************************************************
* @brief    write a HIGH-Bit on the databus
*
* @param    none
*
* @return   none
*
******************************************************************************/
void inject_write_high_bit() {

    REG_DDR &= ~(1<<PIN_GATE);

    if( REG_PIN & (1<<PIN_GATE) ) {
        REG_DDR  &=  ~(1<<PIN_DATA);        // set data-Pin as Input
        REG_PORT &=  ~(1<<PIN_DATA);        // set to high impedance
    }
    else {
        REG_DDR  |=  (1<<PIN_DATA);         // set data-Pin as Output
        REG_PORT &= ~(1<<PIN_DATA);         // set the data-Pin LOW
    }


}


/******************************************************************************
* @brief    write a LOW-Bit on the databus
*
* @param    none
*
* @return   none
*
******************************************************************************/
void inject_write_low_bit() {
    REG_DDR  |=  (1<<PIN_DATA);             // set data-Pin as Output
    REG_PORT &= ~(1<<PIN_DATA);             // set the data-Pin LOW
}


/******************************************************************************
* @brief    inject the region-code on the databus
*
* @param    none
*
* @return   none
*
******************************************************************************/
void inject_region_code() {

    uint8_t i = 0;

    inject_startTimer();

    for( i=0; i < REGION_LENGTH; i++) {

        m_counter_ms = 0;

        while(m_counter_ms < BIT_LENGTH_MS) {

            if( SCEXData[i] == 1) {
                debug_set_pin(DEBUG_HIGH);
                inject_write_high_bit();
            }
            else {
                debug_set_pin(DEBUG_LOW);
                inject_write_low_bit();
            }

        }

    }

    inject_stopTimer();                     // stop the timer

}


void inject_sequence() {

    REG_DDR  &= ~(1<<PIN_DATA);             // set data-pin as Input
    REG_PORT &= ~(1<<PIN_DATA);             // set data-pin to high impedance

    uint8_t i = 0;

    for(i=0; i < REPEAT_INJECTION; i++) {
        inject_region_code();
        inject_write_low_bit();
        _delay_ms(DELAY_AFTER_INJECTION_MS);
    }

    inject_release();


}


void inject_release() {
    REG_DDR  &= ~(1<<PIN_DATA);             // set data-pin as input
    REG_PORT &= ~(1<<PIN_DATA);             // set data-pin to high-impedance

    REG_DDR  &= ~(1<<PIN_GATE);             // set gate-pin as input
    REG_PORT &= ~(1<<PIN_GATE);             // set gate_pin to high-impedance
}
