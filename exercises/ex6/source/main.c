/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "GPIO.h"
#include "LED.h"
#include "Button.h"
#include "SysTick.h"
#include "LCD.h"

#define SECONDS_PER_MINUTE		60
#define MINUTES_PER_HOUR		60
#define HOURS_PER_DAY			24
#define SECONDS_PER_HOUR		(SECONDS_PER_MINUTE * MINUTES_PER_HOUR)

typedef enum {STOPPED, RUNNING, LAP} STOPWATCH_STATE;

STOPWATCH_STATE state = STOPPED;

void Delay(uint32_t length)
{
	for (volatile double d = length; d > 0; d--)
		;
}

void TimeDisplay(int count)
{
	int seconds = count % SECONDS_PER_MINUTE;
	int minutes = (count / SECONDS_PER_MINUTE) % MINUTES_PER_HOUR;
	int hours = (count / SECONDS_PER_HOUR) % HOURS_PER_DAY;

    printf("%2d:%02d:%02d\n", hours, minutes, seconds);

    // Display minutes and seconds on the LCD too
    LCDWrite("%2d%02d", minutes, seconds);

    // If the seconds count is even, show the colon. Even means bit 0 of seconds == 0
    LCDColon((seconds & 1) == 0);
}

void LCDInit(void)
{
	// This function does *our* initialisation of the LCD
	// Note that we are using the Delay() function because SysTick may not be running yet
	LCDInitialise();

	// Segment test
	LCDAllSegments(1);
	Delay(100000);
	LCDAllSegments(0);
}

/*
 * @brief   Application entry point.
 */
int main(void)
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    printf("Hello World\n");

    LEDInit();
    ButtonInit();
    SysTickInit(1000);
    LCDInit();

    volatile static int i = (23 * SECONDS_PER_HOUR) + (59 * SECONDS_PER_MINUTE) + 55;
    int stopwatch_counter = 0;
    int lap_counter = 0;
    bool button0_pressed = false;
    bool button1_pressed = false;

    while(1)
    {
    	// Divide by 1000 because SysTickGet() returns in milliseconds
        if (i != (SysTickGet() / 1000))
        {
        	// Only do this once the seconds have changed
        	i = (SysTickGet() / 1000);

        	if ((state == RUNNING) || (state == LAP))
        	{
        		stopwatch_counter++;
        	}

        	if (state == LAP)
        		TimeDisplay(lap_counter);
        	else
        		TimeDisplay(stopwatch_counter);
        }

        if (ButtonRead0Debounced())
        {
        	if (!button0_pressed)
        	{
        		switch(state)
        		{
					case STOPPED:
						state = RUNNING;
						break;

					case RUNNING:
						state = STOPPED;
						break;

					case LAP:
						state = STOPPED;
						break;

					default:
						break;
        		}
        	}

        	button0_pressed = true;
        }
        else
        {
        	button0_pressed = false;
        }

        if (ButtonRead1Debounced())
        {
        	if (!button1_pressed)
        	{
        		switch(state)
        		{
					case STOPPED:
						// Reset the time
						stopwatch_counter = 0;
						break;

					case RUNNING:
						// Remember the current lap time
						lap_counter = stopwatch_counter;
						state = LAP;
						break;

					case LAP:
						state = RUNNING;
						break;

					default:
						break;
        		}
        	}

        	button1_pressed = true;
        }
        else
        {
        	button1_pressed = false;
        }

		switch(state)
		{
			case STOPPED:
				LEDRed(true);
				LEDGreen(false);
				break;

			case RUNNING:
				LEDRed(false);
				LEDGreen(true);
				break;

			case LAP:
				LEDGreen(true);
				LEDRed(true);
				break;

			default:
				break;
		}

    }

    return 0;
}
