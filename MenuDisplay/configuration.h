/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
 */

#ifndef __configuration_h__
#define __configuration_h__

/* INCLUDES */
#include "Arduino.h"

/* DEFINES */
/* Enable peripherals */
#define ENABLE_BUZZER               //Enable play buzzer
#define ENABLE_TOGGLE_BACKLIGHT     //Enable turn on/off backlight

/* Peripherals */
#define BUZZER_PIN         6
#define BUTTON1_PIN        7  
#define BUTTON2_PIN        5
#define BUTTON3_PIN        4

/* Display ST7920 128x64 pixels */
#define SCK_PIN            13
#define MOSI_PIN           11
#define CS_PIN             10
#define ENABLE_BACKLIGHT   9
#define RESET_PIN          8 

/* EEPROM ADDRESS */
#define BACKLIGHT_ADDRESS  0
#define BUZZER_ADDRESS     1

#endif /* __configuration_h__ */
