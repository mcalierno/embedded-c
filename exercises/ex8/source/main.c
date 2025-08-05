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

#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"
#include "GPIO.h"
#include "LED.h"
#include "Button.h"

#define STACK_SIZE	(configMINIMAL_STACK_SIZE * 2)
typedef enum {STOPPED, RUNNING, LAP} STOPWATCH_STATE;

STOPWATCH_STATE state = STOPPED;

volatile uint32_t counter = 0;
volatile uint32_t lap = 0;

void TaskDisplay(void * params)
{
	uint32_t last = 0xFFFFFFFF;

    while(1)
    {
    	uint32_t count = counter / 100;
    	if (last != count)
    	{
    		last = count;
    		printf("%2d:%02d:%02d\r\n", last / 3600, (last % 3600) / 60, last % 60);
    	}
    	vTaskDelay(100);
    }
}

void TaskCounter(void * params)
{
	while(1)
	{
		if (state != STOPPED)
			counter++;

		if ((state == LAP) && ((counter - lap) > 500))
			state = RUNNING;

		vTaskDelay(10);
	}
}

void TaskButtons(void * params)
{
    bool button0_pressed = false;
    bool button1_pressed = false;

    ButtonInit();

	while(1)
	{
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
						counter = 0;
						break;

					case RUNNING:
						// Remember the current lap time
						lap = counter;
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

        vTaskDelay(10);
	}
}

void TaskLCD(void * params)
{
	LCDInitialise();

	LCDAllSegments(1);
	vTaskDelay(1000);
	LCDAllSegments(0);

	while(1)
	{
		uint32_t val = counter;
		if (state == LAP)
			val = lap;

		if (val < (1 * 60 * 100))
		{
			LCDWrite("%2d%02d", (val / 100) % 60, (val % 100));
			LCDColon(0);
			LCDDP2((val % 100) < 50);
			vTaskDelay(10);
		}
		else
		{
			val /= 100;
			LCDWrite("%2d%02d", (val / 60) % 60, (val % 60));
			LCDColon((counter % 100) < 50);
			LCDDP2(0);
			vTaskDelay(250);
		}
	}
}

void TaskLED(void * params)
{
	LEDInit();

	while(1)
	{
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
			LEDRed(true);
			if ((counter % 100) < 50)
				LEDGreen(false);
			else
				LEDGreen(true);
			break;

		default:
			LEDRed(false);
			LEDGreen(false);
			break;
		}

		vTaskDelay(10);
	}
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

    xTaskCreate(TaskDisplay, "Display", STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(TaskCounter, "Counter", STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(TaskLCD, "LCD", STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(TaskButtons, "Buttons", STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(TaskLED, "LED", STACK_SIZE, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();

    while(1)
    	;

    return 0;
}
