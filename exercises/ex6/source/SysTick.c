

#include "SysTick.h"

static volatile uint32_t systick_counter = 0;

void SysTickInit(uint32_t frequency)
{
	// SystemCoreClock is the number of ticks per second configured by startup
	uint32_t reload_value = (SystemCoreClock / frequency) - 1UL; /* reload/interrupt every 1 ms */

	// SysTick counter is only 24 bits. Make sure value is valid otherwise we will halt here
	while (!(reload_value > 0) && (reload_value < SysTick_LOAD_RELOAD_Msk) )
		;

	// Disable the timer just in case
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

	// Reset the current value
	SysTick->VAL = 0UL;

	// Load the reload value
	SysTick->LOAD = reload_value;

	// Set interrupt priority for SysTick
	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);

	// Enable the timer and interrupt
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/*
	This function is called by the CPU automatically to service the SysTick interrupt

	You DO NOT call it directly
 */
void SysTick_Handler(void)
{
	systick_counter++;
}

uint32_t SysTickGet(void)
{
	return systick_counter;
}
