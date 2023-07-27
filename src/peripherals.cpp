/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

/* INCLUDES */
#include "peripherals.h"

/* GLOBAL VARIABLES */
//empty

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
  if (EERead(BUZZER_ADDRESS) > 0)
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
   pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
   pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
   pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
}

/**
 * @brief Check if any button was pressed
 * 
 * @return The button pressed 
 */
Keypressed ButtonPressed()
{
   Keypressed returnButton = BUTTON_NULL;
   static int buttonUP = 0;
   static int buttonDW = 0;
   static int buttonSL = 0;
   static bool flagButtonSL = false;
   static unsigned long ulDebounceUP = 0;
   static unsigned long ulDebounceDW = 0;
   static unsigned long ulDebounceSL = 0;

   buttonUP = digitalRead(BUTTON_UP_PIN);
   if(!buttonUP)
   {
      if((millis() - ulDebounceUP) > DEBOUCE_BUTTON)
      {
         ulDebounceUP = millis();
         returnButton = BUTTON_UP;
         fnvBuzzerPlay(2000, 50);
      }
   }

   buttonDW = digitalRead(BUTTON_DOWN_PIN);
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
   buttonSL = digitalRead(BUTTON_SELECT_PIN);
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
