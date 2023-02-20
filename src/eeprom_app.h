/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 18/fev/2023
*/

#ifndef __eeprom_app_h__
#define __eeprom_app_h__

/* INCLUDES */
#include "Arduino.h"
#include <EEPROM.h>

/* GLOBAL FUNCTIONS */
bool EEWrite(int eeprom_address, int eeprom_value);
int EERead(int eeprom_address);

#endif /* __eeprom_app_h__ */