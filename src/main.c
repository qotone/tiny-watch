/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#include <stdio.h>
#include <stdbool.h>
#include "ssd1306.h"
#include "draw.h"
#include "hw_config.h"
#include "display.h"
#include "rtc_hal.h"
#include "buttons.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int16_t time_hour,time_mins,time_secs;
volatile uint16_t TimingLED = 1000;
bool timeUpdate = false;
extern void watchUI_normal(void);
void Timing_Decrement(void)
{
  /* do something like this */
  /*
  if(TimingBUTTON != 0x00)
  {
    TimingBUTTON--;
  }
  */
  TimingLED--;
  if(TimingLED == 0x00)
  {
    TimingLED = 1000;
    //    GPIO_ResetBits(GPIOC, GPIO_Pin_2);
    //        GPIOC->ODR ^= 1 << 2;
	//    timeUpdate = true;
  }
}

/* Private function prototypes -----------------------------------------------*/

static bool ledToggle(void)
{
  GPIOC->ODR ^= 1<<2;
  return true;
}
//GPIO_InitTypeDef gpio_init;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{

  time_t tmpTime = 1451221698;
  struct tm *ntime;
  Set_System();

  SysTick_Configuration();


    GPIO_InitTypeDef gpio_init;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  gpio_init.GPIO_Pin = GPIO_Pin_2;
  gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&gpio_init);
  GPIO_SetBits(GPIOC, GPIO_Pin_2);

  buttons_init();
  button_setFunc(BUTTON1,ledToggle);
  //  if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  //  {
    //    time_t tmpTime = 1451221698;
    /* Backup data register value is not correct or not yet programmed when the first time the program is executed */
    
    /* RTC Configuration */
      HAL_RTC_Configuration();
    // begin Time adjust
    //    HAL_RTC_Set_UnixTime(tmpTime);
    //    ntime = localtime(&tmpTime);
    /* write backup register */
    //BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    //  }
    //  else
    //  {
    /* Check if the Power On Reset flag is set */
    //    if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    //    {
      //
    //    }
    /* Check if the Pin Reset flag is set */
    //    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    //    {
      //
    //    }
    //    RTC_WaitForSynchro();

    //    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    //    RTC_WaitForLastTask();
    //  }
  /* Clear reset flags */
    //  RCC_ClearFlag();



  ssd1306_drv.Init();

 ssd1306_drv.ClearDisplay();
 // drawYBitmap(0,0,menu_alarm,32,32);
 // ssd1306_drv.Display();
 // char *s="This is Hello";
 // draw_string(s,false,0,0);
 // draw_end();
 display_set(watchUI_normal);
 display_load();
 // display_update();
 // SysTick_Disable();
 while(1)
 {
   if(timeUpdate)
   {
  tmpTime= HAL_RTC_Get_UnixTime();
  ntime=localtime(&tmpTime);
  time_hour = ntime->tm_hour;
  time_secs = ntime->tm_sec;
  time_mins = ntime->tm_min;
  timeUpdate = false;
  //  display_update();
  }
  display_update();
  buttons_update();
 }


}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
