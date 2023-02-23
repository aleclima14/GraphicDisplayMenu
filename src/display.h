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
void fnvDrawMenuList(void);
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
}EnMenuListItems;

typedef struct
{
  EnMenuListItems enMenuItem;
  const unsigned char *pucMenuIcons;
  char *pucMenuName;
  void (*pvFunction)();
}StMenuListAction;

static const StMenuListAction stMenuTable[] =
{
  /*MENU INDEX              16x16 ICON            MENU NAME                 FUNCTION              */
  {MENU_LOCALIZATION,       localization_icon,    "Localization",           NULL                  },
  {MENU_BLUETOOTH,          bluetooth_icon,       "Bluetooth",              NULL                  },
  {MENU_BATTERY,            battery_icon,         "Battery",                NULL                  },
  {MENU_CLOCK,              clock_icon,           "Clock",                  NULL                  },
  {MENU_ALERTS,             exclamation_icon,     "Alerts",                 NULL                  },
  {MENU_GAUGE,              gauge_icon,           "Gauge",                  NULL                  },
  {MENU_SOUND,              soundon_icon,         "Sound",                  &fnvBuzzerToggleStatus},
  {MENU_CONFIGURATION,      config_icon,          "Configuration",          &fnvDrawBrightnessMenu},
};
#define MENU_TABLE_SIZE (int)(sizeof(stMenuTable)/sizeof(StMenuListAction))

#endif /* __diplay_h__ */
