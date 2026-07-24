#include <Arduino.h>
#include <string.h>

#include "statusbar.h"
#include "display.h"
#include "theme.h"
#include "gps.h"


const char* currentPage = "MENU";


// ============================
// STATUS CACHE
// ============================

const char* oldPage = "";

int oldHour = -1;
int oldMinute = -1;

bool oldTimeValid = false;

bool firstStatusDraw = true;



// ============================
// SET PAGE
// ============================

void setStatusPage(
  const char* page
)
{

  currentPage = page;

  firstStatusDraw = true;

}


// ============================
// DRAW STATUS BAR
// ============================

void drawStatusBar()
{

  int hour =
    getHour();


  int minute =
    getMinute();


  bool valid =
    gpsTimeValid();



  bool pageChanged =
    strcmp(
      currentPage,
      oldPage
    ) != 0;



  bool timeChanged =
    hour != oldHour ||
    minute != oldMinute ||
    valid != oldTimeValid;



  // NOTHING CHANGED

  if(
    !pageChanged &&
    !timeChanged &&
    !firstStatusDraw
  )
  {

    return;

  }




  // BACKGROUND

  tft.fillRect(
    0,
    3,
    160,
    12,
    UI_BACKGROUND
  );


  tft.drawLine(
    0,
    17,
    160,
    17,
    UI_PRIMARY
  );



  tft.setTextSize(
    1
  );


  tft.setTextColor(
    UI_TEXT
  );



  // ============================
  // PAGE LEFT
  // ============================

  tft.setCursor(
    4,
    5
  );


  tft.print(
    currentPage
  );




  // ============================
  // TIME RIGHT
  // ============================

  tft.setCursor(
    120,
    5
  );


  if(
    valid
  )
  {

    if(
      hour < 10
    )
    {
      tft.print(
        "0"
      );
    }


    tft.print(
      hour
    );


    tft.print(
      ":"
    );


    if(
      minute < 10
    )
    {
      tft.print(
        "0"
      );
    }


    tft.print(
      minute
    );

  }
  else
  {

    tft.print(
      "--:--"
    );

  }



  // SAVE CACHE

  oldPage =
    currentPage;


  oldHour =
    hour;


  oldMinute =
    minute;


  oldTimeValid =
    valid;


  firstStatusDraw =
    false;

}