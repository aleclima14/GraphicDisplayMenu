/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
 */

#include "display.h"
#include "configuration.h"
#include "peripherals.h"

extern void (*changeScreen)();

void setup()
{
  fnvDisplayInit();
  fnvBuzzerInit();
  fnvButtonsInit();
}

void loop()
{
//  fnvDrawMenuList();
  //  fnvDrawBrightnessMenu();
  (*changeScreen)();
}
