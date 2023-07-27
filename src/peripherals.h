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
typedef enum 
{
   BUTTON_NULL = 0,
   BUTTON_UP,
   BUTTON_DOWN,
   BUTTON_SELECT,
}Keypressed;

/* GLOBAL FUNCTIONS */
void fnvBuzzerInit();
void fnvBuzzerPlay(int frequency, int duration);
void fnvBuzzerEnableDisable (int stateBz);
void fnvBuzzerToggleStatus();
void fnvButtonsInit();
Keypressed ButtonPressed();

#endif /* __peripherals_h__ */
