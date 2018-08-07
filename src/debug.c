#include "main.h"
#include "debug.h"



/*******************************************************************************
 * @brief   initialize the debug I/O pin
 *
 * simply sets the debug-pin as an output with an initial LOW-level
 * 
 * @param   none
 * 
 * @return  none
 *
*******************************************************************************/
void debug_init() {
    REG_DDR  |=  (1<<PIN_DEBUG);
    REG_PORT &= ~(1<<PIN_DEBUG);
}


/*******************************************************************************
 * @brief   controls the debug pin
 * 
 * @param   mode    LOW     sets the pin to a low-level
 *                  HIGH    sets the pin to a high-level
 *                  TOGGLE  toggles the pin
 *
 * @return  none
 *  
*******************************************************************************/
void debug_set_pin(uint8_t mode) {

    switch(mode) {

        case DEBUG_LOW:
            REG_PORT &= ~(1<<PIN_DEBUG);
            break;
 
        case DEBUG_HIGH:
            REG_PORT |= (1<<PIN_DEBUG);
            break;
 
        case DEBUG_TOGGLE:
            REG_PORT ^= (1<<PIN_DEBUG);
            break;
 
    }

}
