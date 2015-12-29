#include "display.h"
#include "hw_ticks.h"
#include "draw.h"

#define FRAME_RATE     60
#define FRAME_RATE_LOW    25


static draw_f drawFunc;
static display_f func;


void display_set(display_f uiFunc)
{
  func = uiFunc;
}

void display_load(void)
{
  if(func != NULL)
    func();
}


draw_f display_setDrawFunc(draw_f func)
{
  draw_f old = drawFunc;
  drawFunc = func;
  return old;
}

void display_update(void)
{
  static system_tick_t lastDraw = 0;
  static uint8_t fpsMs = 0;
  static system_tick_t now = 10;
  now=GetSystem1MsTick();
  if((now - lastDraw) < fpsMs)
  {
        return;
  }

  lastDraw=now;
  display_t busy = DISPLAY_DONE;

  if(drawFunc != NULL)
    busy = drawFunc();

  draw_end();

  if(busy == DISPLAY_DONE)
    fpsMs = FRAME_RATE_LOW;
  else
    fpsMs = FRAME_RATE;
}
