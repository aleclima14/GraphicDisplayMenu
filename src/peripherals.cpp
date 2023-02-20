/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

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
  int buzzerEnable = EERead(BUZZER_ADDRESS);

  if (buzzerEnable > 0)
  {
    float periode = 1000.0 / frequency;

    for (int i = 0; i < duration / (periode); i++)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      delayMicroseconds(periode * 500);
      digitalWrite(BUZZER_PIN, LOW);
      delayMicroseconds(periode * 500);
    }
  }
}

/**
 * @brief Enable/disable buzzer
 * 
 * @param stateBz 
 */
void fnvBuzzerEnableDisable (int stateBz)
{
  EEWrite(BUZZER_ADDRESS, stateBz);
}

void fnvBuzzerToggleStatus()
{
  static int buzzerState;
  buzzerState = EERead(BUZZER_ADDRESS);
  buzzerState = !buzzerState;
  fnvBuzzerEnableDisable(buzzerState);
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

  buttonUP = digitalRead(BUTTON2_PIN);
  if(!buttonUP)
  {
    if((millis() - ulDebounceUP) > DEBOUCE_BUTTON)
    {
      ulDebounceUP = millis();
      returnButton = BUTTON_UP;
      fnvBuzzerPlay(2000, 50);
    }
  }

  buttonDW = digitalRead(BUTTON1_PIN);
  if(!buttonDW)
  {
    if((millis() - ulDebounceDW) > DEBOUCE_BUTTON)
    {
      ulDebounceDW = millis();
      returnButton = BUTTON_DOWN;
      fnvBuzzerPlay(2000, 50);
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
