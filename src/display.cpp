/**
* Alecsander Lima
* aleclima14@gmail.com
* Campinas, SP - 03/fev/2023
*/

#include "display.h"

#ifdef DISPLAY_ST7920_128X64 
   U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);
#endif

#ifdef DISPLAY_SSD1306_128X64
   U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#endif

/* PRIVATE FUNCTIONS */
void fnvIncDecSelectedItemMenu(void);
void fnvIncDecSelectedSubMenuItem(void);
void fnvWriteBacklightValue(int value);
void fnvSetBrightness(void);
void fnvDrawString(const uint8_t *font, uint8_t x, uint8_t y, const char *string);

void (*pfvChangeScreen)();

/* GLOBAL VARIABLES */
int iPreviusItem;
int iNextItem;
int iSelectedItem = 0;
int brightnessValue = EERead(BACKLIGHT_ADDRESS);
int iSelectedSubMenuItem = 0;
// Adjusts the initial value to be between 0 and 4
int brightnessSelect = brightnessValue / 55;

int subMenu0 = 0;
int subMenu1 = 1;
int subMenu2 = 2;
int subMenu3 = 3;
int selectBarPosition = 1;

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
 * @brief Set font and draw string
 * 
 * @param font family
 * @param x position
 * @param y  position
 * @param string 
 */
void fnvDrawString(const uint8_t *font, uint8_t x, uint8_t y, const char *string)
{
   u8g2.setFont(font);
   u8g2.drawStr(x, y, string);
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
      fnvDrawString(u8g2_font_t0_11_mr, 24, 14,stMainMenuTable[iPreviusItem].pucMenuName);

      u8g2.drawXBMP(5, 24, 16, 16, stMainMenuTable[iSelectedItem].pucMenuIcons);
      fnvDrawString(u8g2_font_t0_11b_mr, 24, 36,stMainMenuTable[iSelectedItem].pucMenuName);

      u8g2.drawXBMP(5, 45, 16, 16, stMainMenuTable[iNextItem].pucMenuIcons);
      fnvDrawString(u8g2_font_t0_11_mr, 24, 58,stMainMenuTable[iNextItem].pucMenuName);

      u8g2.drawBox(124, 64 / MAIN_MENU_TABLE_SIZE * iSelectedItem, 3, 64 / MAIN_MENU_TABLE_SIZE);
   } while (u8g2.nextPage());
}

/**
 * @brief If the button Up or Down was pressed, change the selected menu item
 * 
 */
void fnvIncDecSelectedItemMenu(void)
{
   switch (ButtonPressed())
   {
      case BUTTON_UP:
      {
         iSelectedItem--;
         if (iSelectedItem < 0 )  iSelectedItem = MAIN_MENU_TABLE_SIZE - 1;
      }
      break;

      case BUTTON_DOWN:
      {
         iSelectedItem++;
         if (iSelectedItem >= MAIN_MENU_TABLE_SIZE) iSelectedItem = 0;
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

   if (iPreviusItem < 0) iPreviusItem = MAIN_MENU_TABLE_SIZE - 1;
   if (iNextItem >= MAIN_MENU_TABLE_SIZE) iNextItem = 0;
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
      u8g2.drawXBMP(2, selectBarPosition, 116, 16, submenuSelectBar);
      u8g2.setFontMode(1);
      u8g2.setDrawColor(2);

      /* Draw line 0 */
      fnvDrawString(u8g2_font_t0_11_mr, 6, 13, stSubMenuConfigTable[subMenu0].pucMenuName);
      // u8g2.drawStr(85, 13, "<   >");
      // fnvSetBrightness();

      /* Draw line 1 */
      fnvDrawString(u8g2_font_t0_11_mr, 6, 28, stSubMenuConfigTable[subMenu1].pucMenuName);
      
      /* Draw line 2 */
      fnvDrawString(u8g2_font_t0_11_mr, 6, 43, stSubMenuConfigTable[subMenu2].pucMenuName);
      // u8g2.drawStr(85, 43, "<   >");
      // EERead(BUZZER_ADDRESS) > 0 ? u8g2.drawStr(94, 43, "On"): u8g2.drawStr(91, 43, "Off");
      
      /* Draw line 3 */
      fnvDrawString(u8g2_font_t0_11_mr, 6, 58, stSubMenuConfigTable[subMenu3].pucMenuName);
      

   }while (u8g2.nextPage());
}

/**
 * @brief Config submenu navigation logic
 * 
 */
void fnvIncDecSelectedSubMenuItem(void)
{
   switch (ButtonPressed())
   {
      case BUTTON_UP:
      {
         if (iSelectedSubMenuItem == 0) iSelectedSubMenuItem = 0;
         else iSelectedSubMenuItem--;
         fnvWriteBacklightValue(brightnessValue);
         selectBarPosition = selectBarPosition - 15;
         if(selectBarPosition < 0) selectBarPosition = 1;
         if((iSelectedSubMenuItem+3 < subMenu3) && (subMenu0 > 0) && (selectBarPosition == 1))
         {
            subMenu0--;
            subMenu1--;
            subMenu2--;
            subMenu3--;
         }         
      }
      break;

      case BUTTON_DOWN:
      {
         if (iSelectedSubMenuItem >= CONFIG_MENU_TABLE_SIZE-1) iSelectedSubMenuItem = CONFIG_MENU_TABLE_SIZE-1;
         else iSelectedSubMenuItem++;
         fnvWriteBacklightValue(brightnessValue);
         selectBarPosition = selectBarPosition + 15;
         if(selectBarPosition > 46) selectBarPosition = 46;
         if(iSelectedSubMenuItem > subMenu3)
         {
            subMenu0++;
            subMenu1++;
            subMenu2++;
            subMenu3++;
         }
      }
      break;

      case BUTTON_SELECT:
      {
         switch (stSubMenuConfigTable[iSelectedSubMenuItem].enMenuItem)
         {
            case SUBMENU_CONFIG_RETURN:
            {
               subMenu0 = 0;
               subMenu1 = 1;
               subMenu2 = 2;
               subMenu3 = 3;
               selectBarPosition = 1;
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

/**
 * @brief Set the value according to the brightness table 
 * 
 */
void fnvSetBrightness(void)
{
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
} 

/**
 * @brief Write bightness into "BACKLIGHT_ADDRESS" EEPROM Address
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

void fnvNothingHere()
{
  //Nothing here
}
