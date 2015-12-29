#include "hw_ticks.h"

static volatile system_tick_t system_millis = 0;

void System1MsTick(void)
{
  system_millis++;
}


system_tick_t GetSystem1MsTick(void)
{
  return system_millis;
}

void SysTick_Disable(void)
{
  SysTick->CTRL = SysTick->CTRL & ~SysTick_CTRL_ENABLE_Msk;
}
