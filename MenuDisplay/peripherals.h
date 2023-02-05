/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
 */
 
#ifndef __peripherals.h__
#define __peripherals.h__

#include "Arduino.h"
#include "configuration.h"
#include "display.h"

#define DEBOUCE_BUTTON  200
#define DEBOUNCE_SELECT_BUTTON  100

enum Keypressed
{
   BUTTON_UP      = 1,
   BUTTON_DOWN    = 2,
   BUTTON_SELECT  = 3,
};

void fnvBuzzerInit();
void fnvBuzzerPlay(int frequency, int duration);

void fnvButtonsInit();
int fniButtonPressed();

#endif /* __peripherals.h__ */
