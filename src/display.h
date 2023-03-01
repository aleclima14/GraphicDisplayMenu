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
void fnvDrawBrightnessMenu(void);
void fnvToggleBacklight(void);

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

typedef struct
{
  EnMainMenuItems enMenuItem;
  const unsigned char *pucMenuIcons;
  char *pucMenuName;
  void (*pvFunction)();
}StMainMenuList;

static const StMainMenuList stMainMenuTable[] =
{
  /*MENU INDEX              16x16 ICON            MENU NAME                 FUNCTION              */
  {MENU_LOCALIZATION,       localization_icon,    "Localization",           NULL                  },
  {MENU_BLUETOOTH,          bluetooth_icon,       "Bluetooth",              NULL                  },
  {MENU_BATTERY,            battery_icon,         "Battery",                NULL                  },
  {MENU_CLOCK,              clock_icon,           "Clock",                  NULL                  },
  {MENU_ALERTS,             exclamation_icon,     "Alerts",                 NULL                  },
  {MENU_GAUGE,              gauge_icon,           "Gauge",                  NULL                  },
  // {MENU_SOUND,              soundon_icon,         "Sound",                  &fnvBuzzerToggleStatus},
  // {MENU_CONFIGURATION,      config_icon,          "Configuration",          &fnvDrawBrightnessMenu},
  {MENU_CONFIGURATION,      config_icon,          "Configuration",          &fnvDrawConfigMenuList},
};
#define MAIN_MENU_TABLE_SIZE (int)(sizeof(stMainMenuTable)/sizeof(StMainMenuList))


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

typedef struct
{
  EnSubMenuConfigurationItems enMenuItem;
  char *pucMenuName;
  void (*pvFunction)();
}StSubMenuConfigList;

static const StSubMenuConfigList stSubMenuConfigTable[] = 
{
  /*MENU INDEX                            MENU NAME             FUNCTION                    */
  {SUBMENU_CONFIG_BRIGHTNESS,             "Brightness",         &fnvDrawBrightnessMenu      },
  {SUBMENU_CONFIG_BACKLIGHT,              "Backlight",          NULL                        },
  {SUBMENU_CONFIG_SOUND,                  "Sound",              &fnvBuzzerToggleStatus      },
  {SUBMENU_CONFIG_RETURN,                 "Back",               &fnvDrawMainMenuList        },
};
#define CONFIG_MENU_TABLE_SIZE (int)(sizeof(stSubMenuConfigTable)/sizeof(StSubMenuConfigList))

#endif /* __diplay_h__ */
