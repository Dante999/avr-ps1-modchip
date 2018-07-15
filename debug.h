#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUG_LOW       0
#define DEBUG_HIGH      1
#define DEBUG_TOGGLE    2


void debug_init();
void debug_set_pin(uint8_t mode);


#endif /* DEBUG_H_ */
