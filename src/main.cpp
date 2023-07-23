/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#include "display.h"
#include "configuration.h"
#include "peripherals.h"

extern void (*pfvChangeScreen)();

void setup()
{
   fnvDisplayInit();
   fnvBuzzerInit();
   fnvButtonsInit();
   Serial.begin(9600);
}

void loop()
{
   (*pfvChangeScreen)();
}
