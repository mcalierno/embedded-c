

#ifndef LED_H_
#define LED_H_

#include "MKL46Z4.h"
#include <stdbool.h>

void LEDInit(void);
void LEDToggle(void);
void LEDRed(bool on);
void LEDGreen(bool on);

#endif /* LED_H_ */
