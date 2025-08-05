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
#include "LED.h"
#include "Button.h"
#include "SysTick.h"

#define SECONDS_PER_MINUTE		60
#define MINUTES_PER_HOUR		60
#define HOURS_PER_DAY			24
#define SECONDS_PER_HOUR		(SECONDS_PER_MINUTE * MINUTES_PER_HOUR)

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

    volatile static int i = (23 * SECONDS_PER_HOUR) + (59 * SECONDS_PER_MINUTE) + 55;
    int button_count = 0;
    bool button0_pressed = false;
    bool button1_pressed = false;

    while(1)
    {
    	// Divide by 1000 because SysTickGet() returns in milliseconds
        if (i != (SysTickGet() / 1000))
        {
        	// Only do this once the seconds have changed
        	i = (SysTickGet() / 1000);
            TimeDisplay(i);

            // Only do the LEDs once per second too
            LEDToggle();
        }

        if (ButtonRead0Debounced())
        {
        	if (!button0_pressed)
        	{
        		button_count++;
                printf("%d\n", button_count);
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
        		button_count--;
                printf("%d\n", button_count);
        	}

        	button1_pressed = true;
        }
        else
        {
        	button1_pressed = false;
        }

//        Delay(100000);
    }
    return 0 ;
}
