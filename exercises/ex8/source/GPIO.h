#ifndef _GPIO_H_
#define _GPIO_H_

#include "MKL46Z4.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	GPIO_Type * port;
	uint32_t pin;
} IOPORT;

typedef enum {GPIO_OUTPUT, GPIO_INPUT, GPIO_INPUT_PULLUP, GPIO_INPUT_PULLDOWN} GPIO_MODE;

void GPIOInitialise(const IOPORT * io, GPIO_MODE mode);
void GPIOToggle(const IOPORT * io);
void GPIOSet(const IOPORT * io);
void GPIOReset(const IOPORT * io);
bool GPIOGet(const IOPORT * io);

#endif
