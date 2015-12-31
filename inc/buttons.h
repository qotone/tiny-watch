#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <stdbool.h>
#include "hw_config.h"

typedef bool (*button_f)(void);


void buttons_init(void);
void buttons_update(void);
void buttons_setFuncs(button_f,button_f);
button_f button_setFunc(Button_TypeDef,button_f);
#endif
