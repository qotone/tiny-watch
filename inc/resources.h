/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include<stdint.h>

typedef uint8_t  byte;

#define DATE_FORMAT ("%s %02hhu %s 20%02hhu")
#define TIME_FORMAT_SMALL ("%02hhu:%02hhu%c")

#define CHAR_AM	'A'
#define CHAR_PM	'P'
#define CHAR_24	' '

#define CHAR_YES	'Y'
#define CHAR_NO		'N'

#define STR_DOWCHARS	"MTWTFSS"

// Days
// 3 characters only
#define STR_MON			"Mon"
#define STR_TUE			"Tue"
#define STR_WED			"Wed"
#define STR_THU			"Thu"
#define STR_FRI			"Fri"
#define STR_SAT			"Sat"
#define STR_SUN			"Sun"

// Months
// 3 characters only
#define STR_JAN			"Jan"
#define STR_FEB			"Feb"
#define STR_MAR			"Mar"
#define STR_APR			"Apr"
#define STR_MAY			"May"
#define STR_JUN			"Jun"
#define STR_JUL			"Jul"
#define STR_AUG			"Aug"
#define STR_SEP			"Sep"
#define STR_OCT			"Oct"
#define STR_NOV			"Nov"
#define STR_DEC			"Dec"



// Max string length for menu stuff is 23 characters

#define STR_MAINMENU	"< MAIN MENU >"
#define STR_ALARMS		"Alarms"
#define STR_FLASHLIGHT	"Flashlight"
#define STR_STOPWATCH	"Stopwatch"
#define STR_GAMES		"Games"
#define STR_SETTINGS	"Settings"
#define STR_DIAGNOSTICS	"Diagnostics"
//#define STR_BTRCCAR		"BT RC Car"
//#define STR_TUNEMAKER	"Tune maker"
//#define STR_CALCULATORS	"Calculators"

#define STR_ALARMSMENU	"< ALARMS >"

#define STR_TIMEDATEMENU	"< TIME & DATE >"
#define STR_SAVE		"Save"

#define STR_DIAGNOSTICSMENU	"< DIAGNOSTICS >"
#define STR_TEMPERATURE		"Temperature %hhd.%hhuC"
#define STR_BATTERY			"Battery    %umV"
#define STR_SHOWFPS			"Show FPS%9c"

#define STR_DISPLAYMENU	"< DISPLAY >"
#define STR_BRIGHTNESS	"Brightness"
#define STR_INVERT		"Invert"
#define STR_ROTATE		"Rotate"
#define STR_ANIMATIONS	"Animations"

#define STR_GAMESMENU	"< GAMES >"

#define STR_SOUNDMENU	"< SOUND >"
#define STR_UI			"UI"
#define STR_HOURBEEPS	"Hour beeps"

#define STR_SLEEPMENU	"< SLEEP >"
#define STR_TIMEOUT		"Timeout"
//#define STR_CLOCKMODE	"Clock mode"

#define STR_SETTINGSMENU	"< SETTINGS >"
#define STR_TIMEDATE	"Time & date"
#define STR_SLEEP		"Sleep"
#define STR_SOUND		"Sound"
#define STR_DISPLAY		"Display"
#define STR_LEDS		"LEDs"
//#define STR_RCSETTINGS	"RC Settings"

#define STR_BACK		"Back"
#define STR_EXIT		"Exit"




// game names

#define STR_WIN			"WIN!"
#define STR_GAMEOVER	"GAMEOVER!"
#define STR_SCORE		"Score:"
#define STR_HIGHSCORE	"Highscore:"
#define STR_NEWHIGHSCORE	"!NEW HIGHSCORE!"



extern const char dowChars[];

extern const char days[7][4];
extern const char months[12][4];

extern const byte livesImg[];
extern const byte stopwatch[];

extern const byte dowImg[7][8];

extern const byte menu_default[];
extern const byte menu_alarm[];
extern const byte menu_stopwatch[];
extern const byte menu_torch[];
//extern const byte menu_tunemaker[];
extern const byte menu_settings[];
extern const byte menu_diagnostic[];
extern const byte menu_exit[];
extern const byte menu_timedate[];
extern const byte menu_sleep[];
extern const byte menu_sound[];
extern const byte menu_games[];
//extern const byte menu_calc[];
extern const byte menu_brightness[][128];
extern const byte menu_invert[];
extern const byte menu_anim[][128];
extern const byte menu_volume[][128];
extern const byte menu_rotate[];
extern const byte menu_display[];
extern const byte menu_sleeptimeout[];

extern const byte selectbar_bottom[];
extern const byte selectbar_top[];

extern const byte usbIcon[];
extern const byte chargeIcon[];

extern const byte battIconEmpty[];
extern const byte battIconLow[];
extern const byte battIconHigh[];
extern const byte battIconFull[];

// Alarm icon
//extern const byte smallFontAlarm[];

#define SMALLFONT_WIDTH 5
#define SMALLFONT_HEIGHT 8
extern const byte smallFont[][5];

#define CHAR_DEGREES	127
#define CHAR_TICK		128

#define MIDFONT_WIDTH 19
#define MIDFONT_HEIGHT 24
extern const byte midFont[][57];

#define SEGFONT_WIDTH 19
#define SEGFONT_HEIGHT 24
extern const byte segFont[][57];

#define FONT_SMALL2_WIDTH 11
#define FONT_SMALL2_HEIGHT 16
extern const byte small2Font[][22];

#define FONT_COLON_WIDTH 6
#define FONT_COLON_HEIGHT 24
extern const byte colon[];

#endif /* RESOURCES_H_ */
