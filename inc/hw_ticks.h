#ifndef __HW_TICKS_H
#define __HW_TICKS_H

#include<stdint.h>
#include "stm32f10x.h"
#include "platform_config.h"

typedef uint32_t system_tick_t;

void System1MsTick(void);


system_tick_t GetSystem1MsTick(void);

void SysTick_Disable(void);

#endif
