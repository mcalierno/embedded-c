

#include "Button.h"
#include "GPIO.h"

const IOPORT button0 = {PTC, BUTTON0};
const IOPORT button1 = {PTC, BUTTON1};

void ButtonInit(void)
{
	GPIOInitialise(&button0, GPIO_INPUT_PULLUP);
	GPIOInitialise(&button1, GPIO_INPUT_PULLUP);
}

bool ButtonRead(uint32_t which)
{
	bool result = false;

	switch(which)
	{
		case 0:
			result = !GPIOGet(&button0);
			break;

		case 1:
			result = !GPIOGet(&button1);
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
