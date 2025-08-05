

#include "LED.h"
#include "GPIO.h"

const IOPORT LED_green = {PTD, 5};
const IOPORT LED_red = {PTE, 29};

void LEDInit(void)
{
	GPIOInitialise(&LED_green, GPIO_OUTPUT);
	GPIOInitialise(&LED_red, GPIO_OUTPUT);

	GPIOToggle(&LED_green);
}

void LEDToggle(void)
{
	GPIOToggle(&LED_green);
	GPIOToggle(&LED_red);
}
