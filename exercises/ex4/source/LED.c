
#include "LED.h"

void LEDInit(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
    PORTD->PCR[LED_GREEN] = PORT_PCR_MUX(1u);
    PORTE->PCR[LED_RED] = PORT_PCR_MUX(1u);

    PTD->PDDR |= 1u << LED_GREEN;
    PTE->PDDR |= 1u << LED_RED;

    PTD->PTOR = 1u << LED_GREEN;
}

void LEDToggle(void)
{
	PTD->PTOR = 1u << LED_GREEN;
	PTE->PTOR = 1u << LED_RED;
}
