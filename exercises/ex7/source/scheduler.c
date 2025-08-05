

#include "scheduler.h"
#include "task_config.h"
#include "SysTick.h"

Task_t *Task_ptr;         // Task pointer

uint32_t Tick = 0;			// System tick
uint8_t TaskIndex = 0;			// Task index
uint32_t ElapsedInterval = 0;		// Time since last ran

void OS_Init(void)
{
   Task_ptr = Task_ConfigGet();    // Get a pointer to the task config
}

void OS_Run(void)
{
	// Number of tasks
	const uint8_t NumberOfTasks = Task_GetNumberOf();

	Tick = SysTickGet();

	for (int TaskIndex = 0; TaskIndex < NumberOfTasks; ++TaskIndex)
	{
	   ElapsedInterval = Tick - Task_ptr[TaskIndex].LastTick;

	   if (ElapsedInterval >= Task_ptr[TaskIndex].Interval)
	   {      (*Task_ptr[TaskIndex].Function)();         // Execute Task      // Only update the LastTick if the task is not continuous
	      if (Task_ptr[TaskIndex].Interval != 0)
	      {
	         Task_ptr[TaskIndex].LastTick = Tick;
	      }
	   }
	}
}
