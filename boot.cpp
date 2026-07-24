#include <Arduino.h>

#include "boot.h"
#include "display.h"
#include "theme.h"



void bootAnimation()
{

  clearScreen();



  // Version text

  tft.setTextSize(1);
  tft.setTextColor(UI_DISABLED);


  tft.setCursor(
    52,
    115
  );


  tft.print("V1.5 alpha");



  // Loading title

  tft.setTextSize(2);
  tft.setTextColor(UI_TEXT);


  tft.setCursor(
    48,
    35
  );


  tft.print("BOOT");



  // Loading bar outline

  tft.drawRoundRect(
    20,
    70,
    120,
    12,
    4,
    UI_DISABLED
  );



  // Animated loading

  for(int i = 0; i <= 100; i++)
  {


    tft.fillRoundRect(
      22,
      72,
      i + 1,
      8,
      3,
      UI_PRIMARY
    );


    delay(15);

  }



  delay(300);



  // Loading checks

  const char* checks[] =
  {
    "SYSTEM",
    "DISPLAY",
    "RADIO",
    "GPS",
    "READY"
  };


  for(int i = 0; i < 5; i++)
  {

    tft.fillRect(
      0,
      55,
      160,
      15,
      UI_BACKGROUND
    );


    tft.setTextSize(1);
    tft.setTextColor(UI_TEXT);


    tft.setCursor(
      58,
      58
    );


    tft.print(checks[i]);



    delay(250);

  }


  delay(300);

}