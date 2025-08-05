#include "GPIO.h"
#include <stdlib.h>

void GPIOInitialise(const IOPORT * io, GPIO_MODE mode)
{
	PORT_Type * port = NULL;
	uint32_t sim_mask = 0;

	if (io->port == PTA)	{port = PORTA;	sim_mask = SIM_SCGC5_PORTA_MASK;}
	if (io->port == PTB)	{port = PORTB;	sim_mask = SIM_SCGC5_PORTB_MASK;}
	if (io->port == PTC)	{port = PORTC;	sim_mask = SIM_SCGC5_PORTC_MASK;}
	if (io->port == PTD)	{port = PORTD;	sim_mask = SIM_SCGC5_PORTD_MASK;}
	if (io->port == PTE)	{port = PORTE;	sim_mask = SIM_SCGC5_PORTE_MASK;}

	if (port != NULL)
	{
		SIM->SCGC5 |= sim_mask;
		port->PCR[io->pin] = PORT_PCR_MUX(1u);

		if (mode == GPIO_OUTPUT)
			io->port->PDDR |= 1u << io->pin;
		else
		{
			io->port->PDDR &= ~(1u << io->pin);

			// It's an input, but what about pull resistors?
			switch(mode)
			{
				case GPIO_INPUT:
					port->PCR[io->pin] &= ~PORT_PCR_PE_MASK;
					break;

				case GPIO_INPUT_PULLUP:
					port->PCR[io->pin] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
					break;

				case GPIO_INPUT_PULLDOWN:
					port->PCR[io->pin] |= PORT_PCR_PE_MASK;
					port->PCR[io->pin] &= ~PORT_PCR_PS_MASK;
					break;

				default:
					break;
			}
		}
	}
}

void GPIOToggle(const IOPORT * io)
{
	io->port->PTOR = 1u << io->pin;
}

void GPIOSet(const IOPORT * io)
{
	io->port->PSOR = 1u << io->pin;
}

void GPIOReset(const IOPORT * io)
{
	io->port->PCOR = 1u << io->pin;
}

bool GPIOGet(const IOPORT * io)
{
	return (io->port->PDIR & (1u << io->pin)) != 0;
}
