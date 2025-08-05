
#ifndef LED_H_
#define LED_H_

#include "MKL46Z4.h"

#define LED_RED		29
#define LED_GREEN	5

void LEDInit(void);
void LEDToggle(void);

#endif /* LED_H_ */
