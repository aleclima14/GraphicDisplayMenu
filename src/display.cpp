/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#include "display.h"

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);

/* PRIVATE FUNCTIONS */
void fnvIncDecSelectedItemMenu(void);
void fnvIncDecSelectedSubMenuItem(void);
void fnvWriteBacklightValue(int value);
void (*pfvChangeScreen)();

/* GLOBAL VARIABLES */
int iPreviusItem;
int iNextItem;
int iSelectedItem = 0;
int brightnessValue = EERead(BACKLIGHT_ADDRESS);
int iSelectedSubMenuItem = 0;
// Adjusts the initial value to be between 0 and 4
int brightnessSelect = brightnessValue / 55;

int primeiroMenu = 0;
int segundoMenu = 1;
int terceiroMenu = 2;
int quartoMenu = 3;

/**
 * @brief Init u8g2 lib and backlight display
 * 
 */
void fnvDisplayInit(void)
{
  u8g2.begin();
  pinMode(ENABLE_BACKLIGHT, OUTPUT);
  analogWrite(ENABLE_BACKLIGHT, EERead(BACKLIGHT_ADDRESS));
  pfvChangeScreen = fnvDrawMainMenuList;
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

  analogWrite(ENABLE_BACKLIGHT, valuePWM);
}

/**
 * @brief Write bightness into BACKLIGHT_ADDRESS
 * 
 * @param brightnessWriteValue 
 */
void fnvWriteBacklightValue(int brightnessWriteValue)
{
  if(brightnessValue != EERead(BACKLIGHT_ADDRESS))
  {
    EEWrite(BACKLIGHT_ADDRESS, brightnessWriteValue);
    fnvBuzzerPlay(1000, 50);
    fnvBuzzerPlay(4000, 50);
    fnvBuzzerPlay(1000, 50);
  }
}

/**
 * @brief Draw Main Menu 
 * 
 */
void fnvDrawMainMenuList(void)
{
  iPreviusItem = iSelectedItem - 1;
  iNextItem = iSelectedItem + 1;
  iSelectedSubMenuItem = 0;
  
  u8g2.firstPage();
  do
  {
    u8g2.setDrawColor(1);
    fnvIncDecSelectedItemMenu();
    u8g2.drawXBMP(0, 0, 128, 64, backgroundMenuList);

    u8g2.drawXBMP(5, 2, 16, 16, stMainMenuTable[iPreviusItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(24, 14, stMainMenuTable[iPreviusItem].pucMenuName);

    u8g2.drawXBMP(5, 24, 16, 16, stMainMenuTable[iSelectedItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11b_mr);
    u8g2.drawStr(24, 36, stMainMenuTable[iSelectedItem].pucMenuName);

    u8g2.drawXBMP(5, 45, 16, 16, stMainMenuTable[iNextItem].pucMenuIcons);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(24, 58, stMainMenuTable[iNextItem].pucMenuName);

    u8g2.drawBox(124, 64 / MAIN_MENU_TABLE_SIZE * iSelectedItem, 3, 64 / MAIN_MENU_TABLE_SIZE);
  } while (u8g2.nextPage());
}

/**
 * @brief If the button Up or Down was pressed, change the selected menu item
 * 
 */
void fnvIncDecSelectedItemMenu(void)
{
  switch (fniButtonPressed())
  {
    case BUTTON_UP:
    {
      iSelectedItem--;
      if (iSelectedItem < 0 )
      {
        iSelectedItem = MAIN_MENU_TABLE_SIZE - 1;
      }
    }
    break;

    case BUTTON_DOWN:
    {
      iSelectedItem++;
      if (iSelectedItem >= MAIN_MENU_TABLE_SIZE)
      {
        iSelectedItem = 0;
      }
    }
    break;

    case BUTTON_SELECT:
    {
      switch (stMainMenuTable[iSelectedItem].enMenuItem)
      {
        case MENU_SOUND:
        {
          // To call a function:
          stMainMenuTable[iSelectedItem].pvFunction();
        }
        break;

        case MENU_CONFIGURATION:
        {
          // To change screen:
          pfvChangeScreen = stMainMenuTable[iSelectedItem].pvFunction;
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
    iPreviusItem = MAIN_MENU_TABLE_SIZE - 1;
  }

  if (iNextItem >= MAIN_MENU_TABLE_SIZE)
  {
    iNextItem = 0;
  }
}

/**
 * @brief 
 * 
 */
void fnvDrawConfigMenuList(void)
{
  u8g2.firstPage();
  do
  {
    fnvIncDecSelectedSubMenuItem();
    u8g2.setDrawColor(1);
    u8g2.drawLine(125, 1, 125, 63);
    u8g2.drawBox(124, 64 / CONFIG_MENU_TABLE_SIZE * iSelectedSubMenuItem, 3, 64 / CONFIG_MENU_TABLE_SIZE);
    u8g2.drawXBMP(2, 1+iSelectedSubMenuItem*15, 116, 16, submenuSelectBar);

    u8g2.setFontMode(1);
    u8g2.setDrawColor(2);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(6, 13, stSubMenuConfigTable[primeiroMenu].pucMenuName);
    u8g2.drawStr(85, 13, "<   >");

    if(stBrightnessList[brightnessSelect].integerValue > 99)
    {
      u8g2.drawStr(91, 13, stBrightnessList[brightnessSelect].levelName);
    }
    else if(stBrightnessList[brightnessSelect].integerValue < 10)
    {
      u8g2.drawStr(97, 13, stBrightnessList[brightnessSelect].levelName);
    }
    else
    {
      u8g2.drawStr(94, 13, stBrightnessList[brightnessSelect].levelName);
    }

    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(6, 28, stSubMenuConfigTable[segundoMenu].pucMenuName);
    // u8g2.drawStr(85, 28, "<   >");

    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(6, 43, stSubMenuConfigTable[terceiroMenu].pucMenuName);
    u8g2.drawStr(85, 43, "<   >");
    EERead(BUZZER_ADDRESS) > 0 ? u8g2.drawStr(94, 43, "On"): u8g2.drawStr(91, 43, "Off");


    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(6, 58, stSubMenuConfigTable[quartoMenu].pucMenuName);

  }while (u8g2.nextPage());
}

/**
 * @brief Config submenu navigation logic
 * 
 */
void fnvIncDecSelectedSubMenuItem(void)
{
  switch (fniButtonPressed())
  {
    case BUTTON_UP:
    {
      if (iSelectedSubMenuItem == 0) iSelectedSubMenuItem = 0;
      else iSelectedSubMenuItem--;
      fnvWriteBacklightValue(brightnessValue);
    }
    break;

    case BUTTON_DOWN:
    {
      if (iSelectedSubMenuItem >= CONFIG_MENU_TABLE_SIZE-1) iSelectedSubMenuItem = CONFIG_MENU_TABLE_SIZE-1;
      else iSelectedSubMenuItem++;
      fnvWriteBacklightValue(brightnessValue);
      // if(iSelectedSubMenuItem >= quartoMenu && iSelectedSubMenuItem < CONFIG_MENU_TABLE_SIZE)
      // {
      //   primeiroMenu = segundoMenu;
      //   segundoMenu = terceiroMenu;
      //   terceiroMenu = quartoMenu;
      //   quartoMenu = iSelectedSubMenuItem;
      // }
    }
    break;

    case BUTTON_SELECT:
    {
      switch (stSubMenuConfigTable[iSelectedSubMenuItem].enMenuItem)
      {
        case SUBMENU_CONFIG_RETURN:
        {
          pfvChangeScreen = stSubMenuConfigTable[iSelectedSubMenuItem].pvFunction;
        }
        break;

        default:
        {
          stSubMenuConfigTable[iSelectedSubMenuItem].pvFunction();
        }
        break;
      }
    }
    break;

    default:
    break;
  }

  
}

/**
 * @brief Check buttons and set brightness
 * 
 */
void fnvIncDecBrightness(void)
{
  brightnessSelect--;
  if(brightnessSelect < BRIGHTNESS_1) brightnessSelect = BRIGHTNESS_5;
  brightnessValue = stBrightnessList[brightnessSelect].integerValue * 250/100;
  fnvBacklightSetValue(brightnessValue);
}

void fnvNothingHere()
{
  //Nothing here
}
