
#include "display.h"
#include "configuration.h"
#include <U8g2lib.h>
#include "peripherals.h"
#include "display_screen.h"

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);

/* PRIVATE FUNCTIONS */
void fnvIncDecSelectedItemMenu(void);
void fnvIncDecBrightness(void);
void (*pfvChangeScreen)();

/* GLOBAL VARIABLES */
int iPreviusItem;
int iNextItem;
int iSelectedItem = 0;
int brightnessValue;

/**
 * @brief Init u8g2 lib and backlight display
 * 
 */
void fnvDisplayInit(void)
{
  u8g2.begin();
  pinMode(ENABLE_BACKLIGHT, OUTPUT);
  int backlightEEPROMValue = EEPROM.read(BACKLIGHT_ADDRESS);
  analogWrite(ENABLE_BACKLIGHT, backlightEEPROMValue);
  pfvChangeScreen = fnvDrawMenuList;
}

/**
 * @brief Set value of brightness
 * 
 * @param valuePWM
 */
void fnvBacklightSetValue(int valuePWM)
{
  if (valuePWM > 250) valuePWM = 250;
  if (valuePWM < 0) valuePWM = 0;
  
  EEPROM.write(BACKLIGHT_ADDRESS, valuePWM);

  int backlightEEPROMValue = EEPROM.read(BACKLIGHT_ADDRESS);
  analogWrite(ENABLE_BACKLIGHT, backlightEEPROMValue);
}

/**
 * @brief If the button Up or Down was pressed, change the selected menu item
 * 
 */
void fnvIncDecSelectedItemMenu(void)
{
  int buttonValue = fniButtonPressed();

  switch (buttonValue)
  {
    case BUTTON_UP:
    {
      iSelectedItem++;
      if (iSelectedItem >= MENU_TABLE_SIZE)
      {
        iSelectedItem = 0;
      }
    }
    break;

    case BUTTON_DOWN:
    {
      iSelectedItem--;
      if (iSelectedItem < 0)
      {
        iSelectedItem = MENU_TABLE_SIZE - 1;
      }
    }
    break;

    case BUTTON_SELECT:
    {
      switch (stMenuTable[iSelectedItem].enMenuItem)
      {
        case MENU_SOUND:
        {
          // To call a function:
          stMenuTable[iSelectedItem].pvFunction();
        }
        break;

        case MENU_CONFIGURATION:
        {
          // To change screen:
          pfvChangeScreen = stMenuTable[iSelectedItem].pvFunction;
        }
        break;

        default:
        break;
      }
    }
    break;

    default:
    break;
  }

  if (iPreviusItem < 0)
  {
    iPreviusItem = MENU_TABLE_SIZE - 1;
  }

  if (iNextItem >= MENU_TABLE_SIZE)
  {
    iNextItem = 0;
  }
}

/**
 * @brief Draw menu 
 * 
 */
void fnvDrawMenuList(void)
{
  iPreviusItem = iSelectedItem - 1;
  iNextItem = iSelectedItem + 1;

  u8g2.firstPage();
  do
  {
    fnvIncDecSelectedItemMenu();
    u8g2.drawXBMP(0, 0, 128, 64, backgroundMenuList);

    u8g2.drawXBMP(5, 2, 16, 16, stMenuTable[iPreviusItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(24, 14, stMenuTable[iPreviusItem].pucMenuName);

    u8g2.drawXBMP(5, 24, 16, 16, stMenuTable[iSelectedItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11b_mr);
    u8g2.drawStr(24, 36, stMenuTable[iSelectedItem].pucMenuName);

    u8g2.drawXBMP(5, 45, 16, 16, stMenuTable[iNextItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(24, 58, stMenuTable[iNextItem].pucMenuName);

    u8g2.drawBox(124, 64 / MENU_TABLE_SIZE * iSelectedItem, 3, 64 / MENU_TABLE_SIZE);
  } while (u8g2.nextPage());
}

/**
 * @brief Draw Brightness menu
 * 
 */
void fnvDrawBrightnessMenu(void)
{
  int brightnessBarValue = (brightnessValue * 100) / 250;
  u8g2.firstPage();
  do
  {
    fnvIncDecBrightness();
    u8g2.drawXBMP(0, 0, 128, 64, backgroundBrightnessMenu);
    
    u8g2.drawXBMP(5, 3, 16, 16, brightness_icon); 
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(24, 15, "Brightness Menu");

    u8g2.drawXBMP(50, 42, 16, 16, return_icon);
    u8g2.drawStr(65, 55, "Ok"); 

    u8g2.drawBox(14, 27, brightnessBarValue, 5);
    
  } while (u8g2.nextPage());
}

/**
 * @brief Check buttons and set brightness
 * 
 */
void fnvIncDecBrightness(void)
{
  int buttonValue = fniButtonPressed();
  brightnessValue = EEPROM.read(BACKLIGHT_ADDRESS);

  switch(buttonValue)
  {
    case BUTTON_UP:
    {
      brightnessValue+=25;
      if(brightnessValue > 250) brightnessValue = 250;
      fnvBacklightSetValue(brightnessValue);
    }
    break;

    case BUTTON_DOWN:
    {
      brightnessValue-=25;
      if(brightnessValue < 0) brightnessValue = 0;
      fnvBacklightSetValue(brightnessValue);
    }
    break;

    case BUTTON_SELECT:
    {
      pfvChangeScreen = fnvDrawMenuList;
    }
    break;
  }
}
