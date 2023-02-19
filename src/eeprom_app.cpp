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
 * @brief Write value in EEPROM Address
 * 
 * @param eeprom_address 
 * @param eeprom_value 
 * @return true 
 * @return false 
 */
bool EEWrite(int eeprom_address, int eeprom_value)
{
   bool bRightWrite = false;

   int iEepromAfterWriteValue = EERead(eeprom_address);
   EEPROM.write(eeprom_address, eeprom_value);
   int iEepromBeforeWriteValue = EERead(eeprom_address);

   iEepromAfterWriteValue == iEepromBeforeWriteValue ? bRightWrite = true : bRightWrite = false;

   return bRightWrite;
}

int EERead(int eeprom_address)
{
   int iEepromReadValue = EEPROM.read(eeprom_address);

   return iEepromReadValue;
}