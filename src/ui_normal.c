#include "display.h"
#include "draw.h"
#include "resources.h"
#include <time.h>

#define TIME_POS_X 1
#define TIME_POS_Y 20
#define TICKER_GAP 4


extern int16_t time_hour;
extern int16_t time_mins;
extern int16_t time_secs;

//extern struct tm *ntime;

static void drawTickerNum(image_s* img,uint8_t val,uint8_t maxValue)
{
  uint8_t arraySize = (img->width * img->height) / 8;
  uint8_t yPos = img->offsetY;

  const uint8_t* bitmap = img->bitmap;

  img->bitmap = &bitmap[val * arraySize];
  // if
  img->offsetY = 0;
  draw_bitmap_do();


  img->offsetY = yPos;
  img->bitmap = bitmap;
}

static display_t ticker(void)
{
  static uint8_t yPos = 0;
  static uint8_t yPos_secs = 0;
  image_s img = newImage(104,28,(const uint8_t*)&small2Font,FONT_SMALL2_WIDTH, FONT_SMALL2_HEIGHT,false,yPos_secs);
  draw_bitmap_set(&img);

  drawTickerNum(&img,time_secs/10,5);
  img.x = 116;
  drawTickerNum(&img,time_secs%10,9);

  img.y =TIME_POS_Y;
  img.width = MIDFONT_WIDTH;
  img.height = MIDFONT_HEIGHT;
  img.bitmap = (const uint8_t*)&midFont;
  img.offsetY = yPos;
  img.x = 60;
  drawTickerNum(&img,(time_mins) / 10,5);
  img.x = 83;
  drawTickerNum(&img,(time_mins) % 10,9);

  img.x = 1;
  drawTickerNum(&img,(time_hour) / 10,5);
  img.x = 24;
  drawTickerNum(&img,(time_hour) % 10,9);

  //  if()
  img.x = TIME_POS_X + 46+2;
  img.bitmap =colon;
  img.width = FONT_COLON_WIDTH;
  img.height = FONT_COLON_HEIGHT;
  img.offsetY = 0;
  draw_bitmap_do();

  return DISPLAY_DONE;
}


void watchUI_normal(void)
{
  display_setDrawFunc(ticker);
}
