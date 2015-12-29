#include "draw.h"
#include "resources.h"
#include "ssd1306.h"

#define FRAME_WIDTH SSD1306_LCDWIDTH
#define FRAME_HEIGHT SSD1306_LCDHEIGHT

static image_s* image;

inline static uint8_t readByte(const uint8_t* loc, bool invert)
{
  uint8_t byte= *loc;
  if(invert)
    byte = ~byte;
  return byte;
}

inline static void setBuffByte(uint8_t* buff, uint8_t x, uint8_t y, uint8_t val)
{
  uint16_t pos = x + (y/8) * FRAME_WIDTH;
  buff[pos] |= val;
}

void draw_bitmap_set(image_s* _image)
{
  image = _image;
}

void draw_string(char* string,bool invert, uint8_t x, uint8_t y)
{
  image_s* oldPtr = image;
  image_s img = newImage(0,y,NULL,SMALLFONT_WIDTH,SMALLFONT_HEIGHT,invert,0);
  draw_bitmap_set(&img);

  uint8_t charCount = 0;
  while(*string)
  {
    char c = *string - 0x20;
    uint8_t x_char = x + (charCount * 7);
    img.x = x_char;
    img.bitmap = smallFont[(uint8_t)c];
    draw_bitmap_do();
    if(invert)
    {
      if(x_char > 0)
	setBuffByte(ssd1306_drv.Buffer,x_char -1,y,0xFF);
      if(x_char < FRAME_WIDTH -5)
	setBuffByte(ssd1306_drv.Buffer,x_char+5,y,0xFF);
    }
    string++;
    charCount++;
  }
  image = oldPtr;
}


void draw_bitmap_do(void)
{
  uint8_t x = image->x;
  uint8_t tmp_y = image->y;
  const uint8_t *bitmap = image->bitmap;
  uint8_t w = image->width;
  uint8_t h = image->height;

  //  tmp_y += animation_offsetY(); // to do : Apply animation offset

  uint8_t offsetY =  image->offsetY;
  bool invert = image->invert;
  uint8_t y = tmp_y - offsetY;

  uint8_t byteHeight = h / 8; // 字节高度：位图的字节为单位的高度
  uint8_t pixelOffset = y % 8; // 在Y轴方向上像素字节对齐的偏差值
  uint8_t pixelEdge = tmp_y + h;// 位图在Y轴方向上的像素边界
  
  for(uint8_t i=0;i<byteHeight;i++)// i 为位图的字节高度遍历
  {
    uint8_t pixelY = (i*8) + y;//一个字节高度的像素低值（LSB）Y坐标值
    uint8_t pixelY_Next = (i+1)*8 + y;//下一个字节高度的像素低值Y坐标值

    if(offsetY && (pixelY_Next < tmp_y || pixelY_Next > FRAME_HEIGHT || pixelY > pixelEdge))
 continue;

    uint8_t offsetMask = 0xFF;
    if(offsetY) // 还没有研究这个offsetY变量，有时间再说
    {
      if(pixelY < tmp_y)
	offsetMask = (0xFF << (tmp_y - pixelY));
      else if(pixelY_Next > pixelEdge)
	offsetMask = (0xFF >> (pixelY_Next - pixelEdge));
    }

    uint16_t pixelY_bytesMin_in_buffer = ((pixelY / 8) * FRAME_WIDTH); //pixelY 在oled buffer 中的最小（其实就是X轴方向上偏移量为零）位置

    const uint8_t *b = bitmap + (i * w); // 位图中的字节高度最小位置（实际就是X轴方向上的偏移量为零）遍历
    if(!pixelOffset && (pixelY < FRAME_HEIGHT)) //Y轴方向上像素高度对齐时
    {
      for(uint8_t j = 0; j < w; j++) // X轴方向上的偏移量遍历
      {
	uint8_t xInBuffer = j + x;
	if(xInBuffer >= FRAME_WIDTH) continue;

	uint8_t byteInBitmap = readByte(b + j, invert) & offsetMask;
	*(ssd1306_drv.Buffer+xInBuffer + pixelY_bytesMin_in_buffer) |= byteInBitmap;
      }
    }
    else
    {

      uint16_t pixelY_next_bytesMin_in_buffer = ((pixelY_Next / 8) * FRAME_WIDTH);
      for (uint8_t j = 0; j < w; j++)
      {
	uint8_t xInBuffer = j + x;
	if(xInBuffer >= FRAME_WIDTH) continue;
	uint8_t byteInBitmap = readByte(b + j, invert) & offsetMask;
	if(pixelY < FRAME_HEIGHT)
	  *(ssd1306_drv.Buffer+xInBuffer + pixelY_bytesMin_in_buffer) |= byteInBitmap << pixelOffset; // 上一组字节的高位
	if(pixelY_Next < FRAME_HEIGHT)
	  *(ssd1306_drv.Buffer+xInBuffer + pixelY_next_bytesMin_in_buffer) |= byteInBitmap >> (8- pixelOffset); // 下一组字节的低位
      }
    }
  }
}

void draw_clearArea(uint8_t x, uint8_t y, uint8_t w)
{
  uint16_t pos = x +(y / 8) * FRAME_WIDTH;
  memset((ssd1306_drv.Buffer+pos), 0x00,w);
}

void draw_end()
{
  // oled_flush();
  //  ssd1306_drv.ClearDisplay();
  ssd1306_drv.Display();
}
