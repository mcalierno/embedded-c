

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

typedef struct
{
   uint16_t Interval;
   uint32_t LastTick;
   void (*Function)(void);
} Task_t;

#define SYS_TICK_INTERVAL	  1000UL

// Define the number of system ticks required for each interval
#define INTERVAL_0MS		 0UL
#define INTERVAL_10MS        (10000UL / SYS_TICK_INTERVAL)
#define INTERVAL_50MS        (50000UL / SYS_TICK_INTERVAL)
#define INTERVAL_100MS       (100000UL / SYS_TICK_INTERVAL)
#define INTERVAL_500MS       (500000UL / SYS_TICK_INTERVAL)
#define INTERVAL_1000MS      (1000000UL / SYS_TICK_INTERVAL)

void OS_Init(void);
void OS_Run(void);

#endif /* SCHEDULER_H_ */
