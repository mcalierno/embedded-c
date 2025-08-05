

#include "Button.h"

void ButtonInit(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    /* Make pins GPIO AND enable pull up resistors */
    PORTC->PCR[BUTTON0] = PORT_PCR_MUX(1u) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;
    PORTC->PCR[BUTTON1] = PORT_PCR_MUX(1u) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;

    PTC->PDDR &= ~(1u << BUTTON0);
    PTC->PDDR &= ~(1u << BUTTON1);
}

bool ButtonRead(uint32_t which)
{
	bool result = false;

	switch(which)
	{
		case 0:
			result = ((PTC->PDIR & (1u << BUTTON0)) == 0);
			break;

		case 1:
			result = ((PTC->PDIR & (1u << BUTTON1)) == 0);
			break;

		default:
			result = false;
			break;
	}

	return result;
}

bool ButtonRead0Debounced(void)
{
	static bool current_state = false;
	static uint32_t press_counter = 0;

	// If the button was pressed, increment the counter unless that would take us beyond maximum
	if (ButtonRead(0))
	{
		if (press_counter < BUTTON_DEBOUNCE)
		{
			press_counter++;
		}
		else
		{
			// We were at maximum, we can reliably stay in the pressed state
			current_state = true;
		}
	}
	else	// Decrement the counter unless it's already 0
	{
		if (press_counter > 0)
		{
			press_counter--;
		}
		else
		{
			current_state = false;
		}
	}

	return current_state;
}

bool ButtonRead1Debounced(void)
{
	static bool current_state = false;
	static uint32_t press_counter = 0;

	// If the button was pressed, increment the counter unless that would take us beyond maximum
	if (ButtonRead(1))
	{
		if (press_counter < BUTTON_DEBOUNCE)
		{
			press_counter++;
		}
		else
		{
			// We were at maximum, we can reliably stay in the pressed state
			current_state = true;
		}
	}
	else	// Decrement the counter unless it's already 0
	{
		if (press_counter > 0)
		{
			press_counter--;
		}
		else
		{
			current_state = false;
		}
	}

	return current_state;
}
