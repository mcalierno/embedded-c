

#ifndef TASK_CONFIG_H_
#define TASK_CONFIG_H_

#include <stdint.h>
#include "scheduler.h"

Task_t *Task_ConfigGet(void);
uint8_t Task_GetNumberOf(void);

#endif /* TASK_CONFIG_H_ */
