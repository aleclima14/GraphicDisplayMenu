/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#ifndef __diplay_h__
#define __diplay_h__

/* INCLUDES */
#include "Arduino.h"
#include "configuration.h"
#include <U8g2lib.h>
#include "eeprom_app.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

/* GLOBAL FUNCTIONS */
void fnvDisplayInit(void);
void fnvBacklightSetValue(int valuePWM);
void fnvDrawMenuList(void);
void fnvDrawBrightnessMenu(void);
void fnvToggleBacklight(void);

#endif /* __diplay_h__ */
