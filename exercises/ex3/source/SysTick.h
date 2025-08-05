

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include "MKL46Z4.h"

void SysTickInit(uint32_t frequency);
uint32_t SysTickGet(void);

#endif /* SYSTICK_H_ */
