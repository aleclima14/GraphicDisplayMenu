#include "display.h"
#include "configuration.h"
#include <U8g2lib.h>
#include "peripherals.h"
#include "display_screen.h"

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);

void fnvIncDecSelectedItemMenu();

/* GLOBAL VARIABLES */
bool toggleBackLight = true;

int iPreviusItem;
int iNextItem;
int iSelectedItem = 1;

/**
 * @brief Init u8g2 lib and backlight display
 * 
 */
void fnvDisplayInit(void)
{
  u8g2.begin();
  pinMode(ENABLE_BACKLIGHT, OUTPUT);
  digitalWrite(ENABLE_BACKLIGHT, true);
}

/**
 * @brief Turn on/off backlight
 * 
 * @param turnOn 
 */
void fnvBacklightEnable(bool turnOn)
{
  #ifdef ENABLE_TOGGLE_BACKLIGHT
  digitalWrite(ENABLE_BACKLIGHT, turnOn);
  #endif
}

/**
 * @brief Toggle backlight
 * 
 */
void fnvToggleBacklight(void)
{
  toggleBackLight = !toggleBackLight;
  fnvBacklightEnable(toggleBackLight);
}

/**
 * @brief Draw menu
 * 
 */
void fnvDrawFirstTest()
{
  iPreviusItem = iSelectedItem - 1;
  iNextItem = iSelectedItem + 1; 
    
  u8g2.firstPage();
  do {
    fnvIncDecSelectedItemMenu();
    u8g2.drawXBMP(0, 0, 128, 64, backGroundTeste);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(22, 14, cMenuItems[iPreviusItem]);
    u8g2.setFont(u8g2_font_t0_11b_mr);
    u8g2.drawStr(22, 36, cMenuItems[iSelectedItem]);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(22, 58, cMenuItems[iNextItem]);
  } while ( u8g2.nextPage() );
}

/**
 * @brief If the button Up or Down was pressed, change the selected menu item
 *        
 */
void fnvIncDecSelectedItemMenu()
{
  int buttonValue = fniButtonPressed();

  if(buttonValue == BUTTON_UP)
  {
    iSelectedItem--;
    if(iSelectedItem < 0)
    {
      iSelectedItem = NUMBER_ITEMS_MENU - 1; 
    }
  }
  else if (buttonValue == BUTTON_DOWN)
  {
    iSelectedItem++;
    if(iSelectedItem >= NUMBER_ITEMS_MENU)
    {
      iSelectedItem = 0;
    }
  }
  
  if(iPreviusItem < 0)
  {
    iPreviusItem = NUMBER_ITEMS_MENU - 1;
  }

  if (iNextItem >= NUMBER_ITEMS_MENU)
  {
    iNextItem = 0;
  }
}
