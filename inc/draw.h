#ifndef __DRAW_H
#define __DRAW_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct{
  uint8_t x;
  uint8_t y;
  const uint8_t* bitmap;
  uint8_t width;
  uint8_t height;
    bool invert;
  uint8_t offsetY;
}image_s;

#define newImage(x,y,bitmap,width,height,invert,offsetY)\
  (image_s){x,y,bitmap,width,height,invert,offsetY}


void draw_bitmap_set(image_s* _image);
void draw_string(char*, bool, uint8_t, uint8_t);
void draw_bitmap_do(void);
void draw_clearArea(uint8_t, uint8_t,uint8_t);
void draw_end(void);
#endif
