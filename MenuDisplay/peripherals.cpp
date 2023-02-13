

/* INCLUDES */
#include "peripherals.h"

/* GLOBAL VARIABLES */
unsigned long ulDebounceUP = 0;
unsigned long ulDebounceDW = 0;
unsigned long ulDebounceSL = 0;

int buttonUP = 0;
int buttonDW = 0;
int buttonSL = 0;
bool flagButtonUP = false;
bool flagButtonSL = false;

int valuePWMTest = EEPROM.read(BACKLIGHT_ADDRESS);
/* LOCAL FUNCTIONS */
//empty

/* FUNCTIONS */

/**
 * @brief This function turn Buzzer Pin Output
 * 
 */
void fnvBuzzerInit()
{
  pinMode(BUZZER_PIN, OUTPUT);
}

/**
 * @brief Play the buzzer with the frequency and duration set
 * 
 * @param frequency 
 * @param duration 
 */
void fnvBuzzerPlay(int frequency, int duration)
{
  #ifdef ENABLE_BUZZER
  float periode = 1000.0 / frequency;

  for (int i = 0; i < duration / (periode); i++)
  {
    digitalWrite(BUZZER_PIN,HIGH);
    delayMicroseconds(periode * 500);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(periode * 500);
  }
  #endif
}

/**
 * @brief Set the button pins as input with pullup
 * 
 */
void fnvButtonsInit()
{
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
}

/**
 * @brief Check if any button was pressed
 * 
 * @return The button pressed 
 */
int fniButtonPressed()
{
  int returnButton = 0;

  buttonUP = digitalRead(BUTTON1_PIN);
  if(!buttonUP)
  {
    if((millis() - ulDebounceUP) > DEBOUCE_BUTTON)
    {
      ulDebounceUP = millis();
      returnButton = BUTTON_UP;
      fnvBuzzerPlay(2000, 50);
      valuePWMTest+=25;
      if(valuePWMTest > 250) valuePWMTest = 250;
      fnvBacklightEnable(valuePWMTest);
    }
  }

  buttonDW = digitalRead(BUTTON2_PIN);
  if(!buttonDW)
  {
    if((millis() - ulDebounceDW) > DEBOUCE_BUTTON)
    {
      ulDebounceDW = millis();
      returnButton = BUTTON_DOWN;
      fnvBuzzerPlay(2000, 50);
      valuePWMTest-=25;
      if(valuePWMTest < 0) valuePWMTest = 0;
      fnvBacklightEnable(valuePWMTest);
    }
  }

  flagButtonSL = buttonSL;
  buttonSL = digitalRead(BUTTON3_PIN);
  if((!buttonSL) && (flagButtonSL))
  {
    if((millis() - ulDebounceSL) > DEBOUNCE_SELECT_BUTTON)
    {
      ulDebounceSL = millis();
      returnButton = BUTTON_SELECT;
      fnvBuzzerPlay(2000, 50);
    }
  }

  return returnButton;
}
