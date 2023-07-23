/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#ifndef __diplay_h__
#define __diplay_h__

/* INCLUDES */
#include "Arduino.h"
#include <U8g2lib.h>
#include "configuration.h"
#include "peripherals.h"
#include "eeprom_app.h"
#include "display_screen.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

/* GLOBAL FUNCTIONS */
void fnvDisplayInit(void);
void fnvBacklightSetValue(int valuePWM);
void fnvDrawMainMenuList(void);
void fnvDrawConfigMenuList(void);
void fnvToggleBacklight(void);
void fnvIncDecBrightness(void);
void fnvNothingHere();

/* ENUM */
typedef enum
{
  MENU_LOCALIZATION,
  MENU_BLUETOOTH,
  MENU_BATTERY,
  MENU_CLOCK,
  MENU_ALERTS,
  MENU_GAUGE,
  MENU_SOUND,
  MENU_CONFIGURATION,
}EnMainMenuItems;

typedef enum
{
  SUBMENU_CONFIG_BRIGHTNESS,
  SUBMENU_CONFIG_BACKLIGHT,
  SUBMENU_CONFIG_SOUND,
  SUBMENU_CONFIG_TEST1,
  SUBMENU_CONFIG_TEST2,
  SUBMENU_CONFIG_TEST3,
  SUBMENU_CONFIG_TEST4,
  SUBMENU_CONFIG_TEST5,
  SUBMENU_CONFIG_TEST6,
  SUBMENU_CONFIG_TEST7,
  SUBMENU_CONFIG_TEST8,
  SUBMENU_CONFIG_RETURN
}EnSubMenuConfigurationItems;

typedef enum
{
  BRIGHTNESS_1,
  BRIGHTNESS_2,
  BRIGHTNESS_3,
  BRIGHTNESS_4,
  BRIGHTNESS_5,
}EnBrightnessLevel;

/* STRUCT */
typedef struct
{
  EnMainMenuItems enMenuItem;
  const unsigned char *pucMenuIcons;
  const char *pucMenuName;
  void (*pvFunction)();
}StMainMenuList;

typedef struct
{
  EnSubMenuConfigurationItems enMenuItem;
  const char *pucMenuName;
  void (*pvFunction)();
}StSubMenuConfigList;

typedef struct
{
  EnBrightnessLevel level;
  const char *levelName;
  const int integerValue;
}StBrightnessLevel;

/* TABLE */
static const StMainMenuList stMainMenuTable[] =
{
  /*MENU INDEX              16x16 ICON            MENU NAME                 FUNCTION              */
  {MENU_LOCALIZATION,       localization_icon,    "Localization",           NULL                  },
  {MENU_BLUETOOTH,          bluetooth_icon,       "Bluetooth",              NULL                  },
  {MENU_BATTERY,            battery_icon,         "Battery",                NULL                  },
  {MENU_CLOCK,              clock_icon,           "Clock",                  NULL                  },
  {MENU_ALERTS,             exclamation_icon,     "Alerts",                 NULL                  },
  {MENU_GAUGE,              gauge_icon,           "Gauge",                  NULL                  },
  {MENU_CONFIGURATION,      config_icon,          "Configuration",          &fnvDrawConfigMenuList},
};
#define MAIN_MENU_TABLE_SIZE (int)(sizeof(stMainMenuTable)/sizeof(StMainMenuList))

static const StSubMenuConfigList stSubMenuConfigTable[] = 
{
  /*MENU INDEX                            MENU NAME             FUNCTION                    */
   {SUBMENU_CONFIG_BRIGHTNESS,            "Brightness",         &fnvIncDecBrightness        },
   {SUBMENU_CONFIG_BACKLIGHT,             "Backlight",          &fnvNothingHere             },
   {SUBMENU_CONFIG_SOUND,                 "Sound",              &fnvBuzzerToggleStatus      },
   {SUBMENU_CONFIG_TEST1,                 "Test 1",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST2,                 "Test 2",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST3,                 "Test 3",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST4,                 "Test 4",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST5,                 "Test 5",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST6,                 "Test 6",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST7,                 "Test 7",             &fnvNothingHere             },
   {SUBMENU_CONFIG_TEST8,                 "Test 8",             &fnvNothingHere             },
   {SUBMENU_CONFIG_RETURN,                "Back",               &fnvDrawMainMenuList        },
};
#define CONFIG_MENU_TABLE_SIZE (int)(sizeof(stSubMenuConfigTable)/sizeof(StSubMenuConfigList))

static const StBrightnessLevel stBrightnessList[] =
{
  {BRIGHTNESS_1,      "O",        0   },
  {BRIGHTNESS_2,      "25",       25  },
  {BRIGHTNESS_3,      "5O",       50  },
  {BRIGHTNESS_4,      "75",       75  },
  {BRIGHTNESS_5,      "1OO",      100 },
};
#define BRIGHTNESS_LEVELS_SIZE (int)(sizeof(stBrightnessList)/sizeof(StBrightnessLevel))

#endif /* __diplay_h__ */
