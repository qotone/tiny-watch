#ifndef __RTC_HAL_H
#define __RTC_HAL_H

#include <stdint.h>
#include <time.h>

void HAL_RTC_Configuration(void);

time_t HAL_RTC_Get_UnixTime(void);

void HAL_RTC_Set_UnixTime(time_t value);

void HAL_RTC_Set_UnixAlarm(time_t value);





#endif
