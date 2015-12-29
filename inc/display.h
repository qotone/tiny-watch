#ifndef __DISPLAY_H
#define __DISPLAY_H
#include<stdint.h>

typedef enum
  {
    DISPLAY_DONE,
    DISPLAY_BUSY,
  } display_t;

typedef display_t (*draw_f)(void);
typedef void (*display_f)(void);


void display_set(display_f uiFunc);

void display_load(void);

draw_f display_setDrawFunc(draw_f func);

void display_update(void);



#endif
