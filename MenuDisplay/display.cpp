#include "display.h"
#include "configuration.h"
#include <U8g2lib.h>

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK_PIN, MOSI_PIN, CS_PIN, RESET_PIN);

/* GLOBAL VARIABLES */
bool toggleBackLight = true;

/**
 * @brief Init u8g2 lib and backlight display
 * 
 */
void fnvDisplayInit(void)
{
  u8g2.begin();
  pinMode(ENABLE_BACKLIGHT, OUTPUT);
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
  #else
  digitalWrite(ENABLE_BACKLIGHT, true);
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

void fnvDrawFirstTest()
{
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, 128, 64, backGroundTeste);
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(22, 14, "Localization");
    u8g2.setFont(u8g2_font_t0_11b_mr);
    u8g2.drawStr(22, 36, "Message");
    u8g2.setFont(u8g2_font_t0_11_mr);
    u8g2.drawStr(22, 58, "Support Chat");
  } while ( u8g2.nextPage() );
}
