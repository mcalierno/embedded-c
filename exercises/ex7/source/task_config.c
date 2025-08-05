

#include "task_config.h"

// Include tasks located in other files
#include "task.h"
#include "main_tasks.h"

Task_t Tasks[] =
{ // Interval        LastTick   Function
   {INTERVAL_0MS,		0,      Task},
   {INTERVAL_10MS,		0,		TaskLED},
   {INTERVAL_500MS,		0,		TaskLCD},
   {INTERVAL_1000MS,	0,		TaskConsole},
   {INTERVAL_10MS,		0,		TaskCounter},
   {INTERVAL_10MS,		0,		TaskButtons},
};


Task_t *Task_ConfigGet(void)
{
   return Tasks;
}

uint8_t Task_GetNumberOf(void)
{
   return sizeof(Tasks) / sizeof(*Tasks);
}
