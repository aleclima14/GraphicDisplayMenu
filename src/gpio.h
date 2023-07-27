/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 27/jul/2023
*/

#ifndef __gpio_h__
#define __gpio_h__

/* INCLUDES */
#include "Arduino.h"

typedef enum
{
   GPIO_PIN_0 = 0,   /* UART RX                    */
   GPIO_PIN_1 = 1,   /* UART TX                    */  
   GPIO_PIN_2 = 2,   /* DIGITAL PIN                */
   GPIO_PIN_3 = 3,   /* DIGITAL/PWM  PIN           */
   GPIO_PIN_4 = 4,   /* DIGITAL PIN                */
   GPIO_PIN_5 = 5,   /* DIGITAL/PWM PIN            */
   GPIO_PIN_6 = 6,   /* DIGITAL/PWM PIN            */
   GPIO_PIN_7 = 7,   /* DIGITAL PIN                */
   GPIO_PIN_8 = 8,   /* DIGITAL PIN                */
   GPIO_PIN_9 = 9,   /* DIGITAL/PWM PIN            */
   GPIO_PIN_10 = 10, /* DIGITAL/PWM/SPI CS PIN     */
   GPIO_PIN_11 = 11, /* DIGITAL/PWM/SPI MOSI PIN   */
   GPIO_PIN_12 = 12, /* DIGITAL/SPI MISO PIN       */
   GPIO_PIN_13 = 13, /* DIGITAL/PWM/SPI SCK PIN    */
}GPIO_DIGITAL_PIN;

typedef enum
{
   GPIO_PIN_A0 = 0,  /* ANALOG PIN                  */
   GPIO_PIN_A1 = 1,  /* ANALOG PIN                  */
   GPIO_PIN_A2 = 2,  /* ANALOG PIN                  */
   GPIO_PIN_A3 = 3,  /* ANALOG PIN                  */
   GPIO_PIN_A4 = 4,  /* ANALOG/I2C SDA PIN          */
   GPIO_PIN_A5 = 5,  /* ANALOG/I2C SCK PIN          */
   GPIO_PIN_A6 = 6,  /* ANALOG PIN                  */
   GPIO_PIN_A7 = 7,  /* ANALOG PIN                  */
}GPIO_ANALOG_PIN;

#endif /* __gpio_h__ */