
#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include "MKL46Z4.h"

#define NUM_BUTTONS		2

// Macros to specify bits of PORTC used for button0 and button1
// Remote access lab uses relays instead of buttons on board
#ifdef REMOTE_BUTTONS
	#define BUTTON0			8
	#define BUTTON1			9
#else
	#define BUTTON0			3
	#define BUTTON1			12
#endif

// An arbitrary count for the number of times the ButtonRead() function must be called before a value is deemed stable
#define BUTTON_DEBOUNCE	5

void ButtonInit(void);
bool ButtonRead(uint32_t which);
bool ButtonRead0Debounced(void);
bool ButtonRead1Debounced(void);

#endif /* BUTTON_H_ */
