#include "ssd1306.h"
#include "hw_config.h"
#include <stdbool.h>
#include <string.h> 
/*
LCD_DrvTypeDef ssd1306_drv =
  {
    ssd1306_Init,
    0,
    ssd1306_DisplayOn,
    ssd1306_DisplayOff,
    ssd1306_SetCursor,
    ssd1306_WritePixel,
    0,
    0,
    0,
    0,
    ssd1306_GetLcdPixelWidth,
    ssd1306_GetLcdPixelHight,
    ssd1306_DrawBitmap,
  };
*/

OLED_DrvTypeDef ssd1306_drv ={

  ssd1306_Init,
  ssd1306_Command,
  ssd1306_Data,
  ssd1306_Display,
  ssd1306_ClearDisplay,
  ssd1306_InvertDisplay,
  ssd1306_DrawPixel,
  ssd1306_Dim,
  ssd1306_StartScrollRight,
  ssd1306_StartScrollLeft,
  ssd1306_StopScroll,
  0,
  0,
  ssd1306_GetLCDWidth,
  ssd1306_GetLCDHeight,
  ssd1306_Buffer,
};

uint8_t ssd1306_Buffer[SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT /8] ={
 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
 0b00000000, 0b00110000 };

#define MODE_CMD    OLED_DC_LOW()
#define MODE_DATA    OLED_DC_HIGH()
#define CHIPSELECT(mode) mode;\
  for(bool cs =oled_select();cs; cs = oled_deselect())

static inline bool oled_select(void)
{
  OLED_CS_LOW();
  return true;
}

static inline bool oled_deselect(void)
{
  OLED_CS_HIGH();
  return false;
}

static void resetPosition(void)
{
  CHIPSELECT(MODE_CMD)
  {
    OLED_SPI_Write(0x22);
    OLED_SPI_Write(0x00);
    OLED_SPI_Write(0x07);

    OLED_SPI_Write(0x21);
    OLED_SPI_Write(0x00);
    OLED_SPI_Write(0x7F);
  }
}

static void sendCmd2(uint8_t cmd,uint8_t val)
{
  CHIPSELECT(MODE_CMD)
  {
    OLED_SPI_Write(cmd);
    OLED_SPI_Write(val);
  }
}

static void sendCmd(uint8_t cmd)
{
  CHIPSELECT(MODE_CMD)
  {
    OLED_SPI_Write(cmd);
  }
}

/*
static void oled_power(oled_pwr_t on)
{
  sendCmd(on == OLED_PWR_ON ? OLED_ON : OLED_OFF);
}

static void oled_setBrightness(uint8_t brightness)
{
  sendCmd2(OLED_SETCONTRAST, brightness);
}

static void oled_setInvert(bool invert)
{
  sendCmd(invert ? OLED_INVERT : OLED_NONINVERT);
}

static void oled_set180(bool rotate)
{
  if(rotate)
    sendCmd2(OLED_SEG_REMAP, OLED_SCANDIR_REMAP);
  else
    sendCmd2(OLED_SEG_NML,OLED_SCANDIR_NML);
}

void ssd1306_WriteReg(uint8_t Reg,uint8_t RegValue)
{
  sendCmd2(Reg,RegValue);
}
*/


void ssd1306_Init(void)
{
  
  OLED_IO_Init();

  ssd1306_Command(SSD1306_DISPLAYOFF);
  ssd1306_Command(SSD1306_SETDISPLAYCLOCKDIV);
  ssd1306_Command(0x80);
  
  ssd1306_Command(SSD1306_SETMULTIPLEX);
  ssd1306_Command(0x3F);
  ssd1306_Command(SSD1306_SETDISPLAYOFFSET);
  ssd1306_Command(0x0);

  ssd1306_Command(SSD1306_SETSTARTLINE | 0x0); // line #0
  ssd1306_Command(SSD1306_CHARGEPUMP);
  ssd1306_Command(0x14);
  ssd1306_Command(SSD1306_MEMORYMODE);
  ssd1306_Command(0x00); // 0x0 act like ks0108
  ssd1306_Command(SSD1306_SEGREMAP | 0x1);
  ssd1306_Command(SSD1306_COMSCANDEC);
  ssd1306_Command(SSD1306_SETCOMPINS); // 0xDA
  ssd1306_Command(0x12);
  ssd1306_Command(SSD1306_SETCONTRAST);
  ssd1306_Command(0xCF);
  ssd1306_Command(SSD1306_SETPRECHARGE);
  ssd1306_Command(0xF1);

  ssd1306_Command(SSD1306_SETVCOMDETECT);
  ssd1306_Command(0x40);
  ssd1306_Command(SSD1306_DISPLAYALLON_RESUME);
  ssd1306_Command(SSD1306_NORMALDISPLAY);

  ssd1306_Command(SSD1306_DISPLAYON);
  
}

void ssd1306_InvertDisplay(bool i)
{
  if(i)
  {
    ssd1306_Command(SSD1306_INVERTDISPLAY);
  }
  else
  {
    ssd1306_Command(SSD1306_NORMALDISPLAY);
  }
}


void ssd1306_Command(uint8_t c)
{
  //  LCD_IO_Write(c);
  CHIPSELECT(MODE_CMD)
  {
    OLED_SPI_Write(c);
  }

}

void ssd1306_StartScrollRight(uint8_t start, uint8_t stop)
{
  ssd1306_Command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_Command(0x00);
  ssd1306_Command(start);
  ssd1306_Command(0x00);
  ssd1306_Command(stop);
  ssd1306_Command(0x00);
  ssd1306_Command(0xff);
  ssd1306_Command(SSD1306_ACTIVATE_SCROLL);
}


void ssd1306_StartScrollLeft(uint8_t start, uint8_t stop)
{
  ssd1306_Command(SSD1306_LEFT_HORIZONTAL_SCROLL);
  ssd1306_Command(0x00);
  ssd1306_Command(start);
  ssd1306_Command(0x00);
  ssd1306_Command(stop);
  ssd1306_Command(0x00);
  ssd1306_Command(0xff);
  ssd1306_Command(SSD1306_ACTIVATE_SCROLL);
}

void ssd1306_StartScrollDiagRight(uint8_t start, uint8_t stop)
{
  ssd1306_Command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  ssd1306_Command(0x00);
  ssd1306_Command(SSD1306_LCDHEIGHT);
  ssd1306_Command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_Command(0x00);
  ssd1306_Command(start);
  ssd1306_Command(0x00);
  ssd1306_Command(stop);
  ssd1306_Command(0x01);
  ssd1306_Command(SSD1306_ACTIVATE_SCROLL);
}

void ssd1306_StartScrollDiagLeft(uint8_t start, uint8_t stop)
{
  ssd1306_Command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  ssd1306_Command(0x00);
  ssd1306_Command(SSD1306_LCDHEIGHT);
  ssd1306_Command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  ssd1306_Command(0x00);
  ssd1306_Command(start);
  ssd1306_Command(0x00);
  ssd1306_Command(stop);
  ssd1306_Command(0x01);
  ssd1306_Command(SSD1306_ACTIVATE_SCROLL);
}


void ssd1306_StopScroll(void)
{
  ssd1306_Command(SSD1306_DEACTIVATE_SCROLL);
}

void ssd1306_Dim(bool dim)
{
  uint8_t contrast;
  if(dim)
  {
    contrast = 0;
  }
  else
  {
    contrast = 0xCF;
  }
  ssd1306_Command(SSD1306_SETCONTRAST);
  ssd1306_Command(contrast);
}

void ssd1306_Data(uint8_t c)
{
  CHIPSELECT(MODE_DATA)
  {
    OLED_SPI_Write(c);
  }
}

void ssd1306_Display(void)
{
  ssd1306_Command(SSD1306_COLUMNADDR);
  ssd1306_Command(0);
  ssd1306_Command(SSD1306_LCDWIDTH-1);

  ssd1306_Command(SSD1306_PAGEADDR);
  ssd1306_Command(0);
  ssd1306_Command(7);
  CHIPSELECT(MODE_DATA)
  {
   
    for(uint16_t i = 0; i< (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++)
    {
      uint8_t next = ssd1306_Buffer[i];
      ssd1306_Buffer[i] = 0x00;
      ssd1306_Data(next);
      //OLED_SPI_Write(0xff);//ssd1306_Buffer[i]);
    }
  }
}

void ssd1306_ClearDisplay(void)
{
  memset(ssd1306_Buffer, 0, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT /8));
}

void ssd1306_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
  if( (x< 0) || (x >= SSD1306_LCDWIDTH) || (y<0) ||(y >= SSD1306_LCDHEIGHT))
    return ;

  switch(color)
  {
  case WHITE:
    ssd1306_Buffer[x + (y/8)*SSD1306_LCDWIDTH] |= (1 << (y&7));
    break;
  case BLACK:
    ssd1306_Buffer[x + (y/8)*SSD1306_LCDWIDTH] &= ~(1<< (y&7));
    break;
  case INVERSE:
    ssd1306_Buffer[x + (y/8)*SSD1306_LCDWIDTH] ^= (1<< (y&7));
    break;
  }
}

void ssd1306_DrawXBitmap(uint16_t xPos,uint16_t yPos,uint8_t *buff,uint8_t w,uint8_t h)
{

      int16_t i,j,byteWidth = (w +7) /8;
      for(j = 0;j<h;j++)
      {
	for(i= 0; i< w;i++)
	{
	  if(buff[j*byteWidth +i/8] & (1<<(i%8)))
	  {
	    ssd1306_DrawPixel(xPos+i,yPos+j,1);
	  }
	}
      }
}

// 这是我写的，字节排列为：Y轴，上为LSB，下为MSB
void ssd1306_DrawYBitmap(uint16_t xPos,uint16_t yPos,uint8_t *buff,uint8_t w,uint8_t h)
{

  int16_t i,j;
  //int16_t byteWidth = (w +7) /8;
      for(j = 0;j<h;j++)
      {
	for(i= 0; i< w;i++)
	{
	  if(buff[i +j/8 * w] & (1<<(j%8)))
	  {
	    ssd1306_DrawPixel(xPos+i,yPos+j,1);
	  }
	}
      }
}


uint16_t ssd1306_GetLCDWidth(void)
{
  return SSD1306_LCDWIDTH;
}

uint16_t ssd1306_GetLCDHeight(void)
{
  return SSD1306_LCDHEIGHT;
}
