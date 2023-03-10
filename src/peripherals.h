/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/
 
#ifndef __peripherals_h__
#define __peripherals_h__

/* INCLUDES */
#include "Arduino.h"
#include "configuration.h"
#include "eeprom_app.h"

/* DEFINES */
#define DEBOUCE_BUTTON  300
#define DEBOUNCE_SELECT_BUTTON  100

/* ENUMS */
enum Keypressed
{
   BUTTON_UP      = 1,
   BUTTON_DOWN    = 2,
   BUTTON_SELECT  = 3,
};

/* GLOBAL FUNCTIONS */
void fnvBuzzerInit();
void fnvBuzzerPlay(int frequency, int duration);
void fnvBuzzerEnableDisable (int stateBz);
void fnvBuzzerToggleStatus();
void fnvButtonsInit();
int fniButtonPressed();

#endif /* __peripherals_h__ */
