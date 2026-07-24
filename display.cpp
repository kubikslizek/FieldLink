#include <Arduino.h>

#include "display.h"
#include "theme.h"
#include "statusbar.h"


Adafruit_ST7735 tft =
Adafruit_ST7735(
  TFT_CS,
  TFT_DC,
  TFT_RST
);



// ============================
// INIT DISPLAY
// ============================

void initDisplay()
{

  tft.initR(
    INITR_BLACKTAB
  );


  tft.setRotation(1);


  tft.fillScreen(
    UI_BACKGROUND
  );


  tft.setTextColor(
    UI_TEXT
  );


  tft.setTextSize(1);

}



// ============================
// CLEAR SCREEN
// ============================

void clearScreen()
{

  tft.fillScreen(
    UI_BACKGROUND
  );

}



// ============================
// HEADER
// ============================

void drawHeader(
  const char* title
)
{

  setStatusPage(title);


  drawStatusBar();


}