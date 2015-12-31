#include "buttons.h"
#include "hw_ticks.h"
//#include "hw_config.h"
//#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


#define BTN_IS_PRESSED    4


typedef struct {
  system_tick_t  pressedTime;
  bool processed;
  uint8_t counter;
  bool funcDone;
  button_f onPress;
  const uint8_t *tune;
} button_t;


static button_t buttons[BUTTONn];

//static void processButtons(void);
static void processButton(button_t*,bool);
static uint8_t bitCount(uint8_t val);

void buttons_init(void)
{
  BUTTON_Init(BUTTON1,BUTTON_MODE_GPIO);
  BUTTON_Init(BUTTON2,BUTTON_MODE_GPIO);
}


void buttons_update(void)
{
  static system_tick_t lastUpdate;
  system_tick_t now = GetSystem1MsTick();
  if( (now - lastUpdate) >= 10)
  {
    lastUpdate = now;
    bool isPressed[BUTTONn];
    isPressed[BUTTON1] = BUTTON_GetState(BUTTON1);
    isPressed[BUTTON2] = BUTTON_GetState(BUTTON2);

    for(uint8_t i = 0;i<BUTTONn;i++)
    {
     processButton(&buttons[i],!isPressed[i]); 
    }
  }

}

static uint8_t bitCount(uint8_t val)
{
  uint8_t counter = 0;
  do{
    //    if(val & 0x01)
      counter += val & 1;
  }
  while(val >>= 1);
  return counter;
}

  static void processButton(button_t* button, bool isPressed)
  {
    button->counter <<= 1;
    if(isPressed)
    {
      button->counter |= 1;
      if(bitCount(button->counter) >= BTN_IS_PRESSED)
      {
	if(!button->processed)
	{
	  button->pressedTime = GetSystem1MsTick();
	  button->processed = true;
	}
	if(!button->funcDone && button->onPress != NULL && button->onPress())
	{
	  button->funcDone =true;
	  //tune_play(button->tune, VOL_UI,PRIO_UI);// to do
	}
      }
    }
    else
    {
      if(bitCount(button->counter) <= BTN_IS_PRESSED)
      {
	button->processed = false;
	button->funcDone = false;
      }
    }
  }


button_f button_setFunc(Button_TypeDef btn,button_f btn_func)
{
  button_f oldFunc = buttons[btn].onPress;
  buttons[btn].onPress =btn_func;
  return oldFunc;
}

void buttons_setFuncs(button_f btn1,button_f btn2)
{
  buttons[BUTTON1].onPress = btn1;
  buttons[BUTTON2].onPress = btn2;
}
