/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 18/fev/2023
*/

/* INCLUDES */
#include "eeprom_app.h"

/* DEFINES */
//empty

/**
 * @brief Write value in EEPROM Address only if the value is different from the previous one. This prevents unnecessary recording
 * 
 * @param eeprom_address 
 * @param eeprom_value 
 * @return true if it is written right
 * @return false 
 */
bool EEWrite(int eeprom_address, int eeprom_value)
{
   bool flagIsWrittenRight = false;

   int iEepromAfterWriteValue = EERead(eeprom_address);
   if(eeprom_value != iEepromAfterWriteValue)
   {
      EEPROM.write(eeprom_address, eeprom_value);
   }
   int iEepromBeforeWriteValue = EERead(eeprom_address);

   eeprom_value == iEepromBeforeWriteValue ? flagIsWrittenRight = true : flagIsWrittenRight = false;

   return flagIsWrittenRight;
}

int EERead(int eeprom_address)
{
   int iEepromReadValue = EEPROM.read(eeprom_address);

   return iEepromReadValue;
}