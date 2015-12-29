/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef __SSD1306_H
#define __SSD1306_H

/*

#include "lcd.h"


#define SSD1306_LCD_PIXEL_WIDTH  ((uint16_t)128)
#define SSD1306_LCD_PIXEL_HIGH   ((uint16_t)64)



// Commands
#define OLED_OFF				0xAE // Power off
#define OLED_ON					0xAF // Power on
#define OLED_MEMMODE			0x20 // Memory addressing mode
#define OLED_NONINVERT			0xA6 // Noninvert
#define OLED_INVERT				0xA7 // Invert
#define OLED_SEG_NML			0xA0 // Seg remap left to right
#define OLED_SEG_REMAP			0xA1 // Seg remap right to left
#define OLED_SETCONTRAST		0x81 // Set contrast
#define OLED_SETMUX				0xA8 // MUX
#define OLED_SCANDIR_NML		0xC0 // Scan direction top to bottom
#define OLED_SCANDIR_REMAP		0xC8 // Scan direction bottom to top
#define OLED_DISPLAY_OFFSET		0xD3
#define OLED_COMCFG				0xDA
#define OLED_DISPLAY_SHOWRAM	0xA4 // Show RAM contents
#define OLED_DISPLAY_HIDERAM	0xA5 // Blank screen, but still on
#define OLED_CHARGEPUMP			0x8D
#define OLED_CLOCK_FREQ			0xD5
#define OLED_DISPLAY_START		0x40
#define OLED_PRECHARGE_PERIOD	0xD9
#define OLED_VCOM_LEVEL			0xDB

// Data
#define OLED_MEM_HORIZ		0x00
#define OLED_MEM_VERT		0x01
#define OLED_MEM_PAGE		0x02
#define OLED_CHARGEPUMP_EN	0x14
#define OLED_CHARGEPUMP_DIS	0x10





void ssd1306_Init(void);
uint16_t ssd1306_ReadID(void);


void ssd1306_DisplayOn(void);
void ssd1306_DisplayOff(void);

void ssd1306_SetCursor(uint16_t Xpos,uint16_t Ypos);
void ssd1306_WritePixel(uint16_t Xpos,uint16_t Ypos,uint16_t RGBCode);

void ssd1306_WriteReg(uint8_t LCDReg,uint8_t LCDRegValue);
uint8_t ssd1306_ReadReg(uint8_t LCDReg);

void ssd1306_SetDisplayWindow(uint16_t Xpos,uint16_t Ypos,uint16_t Width, uint16_t Height);
void ssd1306_DrawHLine(uint16_t RGBCode,uint16_t Xpos,uint16_t Ypos,uint16_t Length);
void ssd1306_DrawVLine(uint16_t RGBCode,uint16_t Xpos,uint16_t Ypos,uint16_t Length);

uint16_t ssd1306_GetLcdPixelWidth(void);
uint16_t ssd1306_GetLcdPixelHeight(void);
void ssd1306_DrawBitmap(uint16_t Xpos,uint16_t Ypos,uint16_t *pbmp);
*/
/* LCD driver structure */
//extern LCD_DrvTypeDef ssd1306_drv;
#include "oled.h"

#define BLACK 0
#define WHITE 1
#define INVERSE 2


#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64


#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON   0xA5
#define SSD1306_NORMALDISPLAY  0xA6
#define SSD1306_INVERTDISPLAY  0xA7
#define SSD1306_DISPLAYOFF     0xAE
#define SSD1306_DISPLAYON      0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE  0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP   0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling defines
#define SSD1306_ACTIVATE_SCROLL  0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


extern OLED_DrvTypeDef ssd1306_drv;
extern uint8_t ssd1306_Buffer[SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8];
void ssd1306_Init(void);

void ssd1306_Command(uint8_t);

void ssd1306_Data(uint8_t);

void ssd1306_ClearDisplay(void);

void ssd1306_InvertDisplay(bool);

void ssd1306_Display(void);

void ssd1306_StartScrollRight(uint8_t,uint8_t);
void ssd1306_StartScrollLeft(uint8_t,uint8_t);
void ssd1306_StopScroll(void);
void ssd1306_StartScrollDiagRight(uint8_t,uint8_t);
void ssd1306_StartScrollDiagLeft(uint8_t,uint8_t);
void ssd1306_Dim(bool);

void ssd1306_DrawPixel(int16_t ,int16_t , uint16_t);

uint16_t ssd1306_GetLCDWidth(void);
uint16_t ssd1306_GetLCDHeight(void);


#endif /* __SSD1306_H */
