#include "config.h"
#include "theme.h"

#include "display.h"
#include "icons.h"
#include "joystick.h"
#include "boot.h"
#include "compass.h"
#include "statusbar.h"
#include "gps.h"
#include "sound.h"
#include "chat.h"
#include "keyboard.h"
#include "status.h"

// ============================
// MENU DATA
// ============================

const char* menuItems[] =
{
  "Navigation",
  "Chat",
  "Compass",
  "GPS",
  "Waypoints",
  "Status",
  "Settings"
};


const int menuIcons[] =
{
  ICON_NAV,
  ICON_CHAT,
  ICON_COMPASS,
  ICON_GPS,
  ICON_MAP,
  ICON_BATTERY,
  ICON_SETTINGS
};


const int menuCount = 7;


int selected = 0;
int menuStart = 0;



// ============================
// DRAW ONE ITEM
// ============================

void drawMenuItem(
  int item,
  int y,
  bool active
)
{

  tft.fillRect(
    0,
    y - 4,
    160,
    26,
    UI_BACKGROUND
  );


  uint16_t color = UI_TEXT;



  if(active)
  {

    tft.drawRoundRect(
      2,
      y - 2,
      156,
      21,
      5,
      UI_PRIMARY
    );


    color = UI_PRIMARY;

  }



  drawIcon(
    tft,
    8,
    y,
    menuIcons[item],
    color
  );



  tft.setTextSize(1);

  tft.setTextColor(color);


  tft.setCursor(
    32,
    y + 5
  );


  tft.print(
    menuItems[item]
  );

}



// ============================
// CLEAR MENU AREA
// ============================

void clearMenuArea()
{

  tft.fillRect(
    0,
    MENU_START_Y - 5,
    160,
    105,
    UI_BACKGROUND
  );

}



// ============================
// DRAW MENU
// ============================

void drawMenu()
{

  clearMenuArea();



  for(int i = 0; i < 4; i++)
  {

    int item =
      menuStart + i;



    if(item >= menuCount)
      break;



    int y =
      MENU_START_Y +
      i * MENU_ITEM_HEIGHT;



    drawMenuItem(
      item,
      y,
      item == selected
    );

  }

}



// ============================
// UPDATE MENU WINDOW
// ============================

void updateMenuWindow()
{

  if(selected < menuStart)
  {

    menuStart = selected;

  }



  if(selected >= menuStart + 4)
  {

    menuStart = selected - 3;

  }



  if(menuStart < 0)
    menuStart = 0;



  if(menuStart > menuCount - 4)
    menuStart = menuCount - 4;

}



// ============================
// UPDATE SELECTION
// ============================

void updateSelection(
  int oldSelected,
  int newSelected
)
{

  int oldStart =
    menuStart;



  selected = newSelected;


  updateMenuWindow();



  if(oldStart != menuStart)
  {

    drawMenu();

    return;

  }



  int oldY =
    MENU_START_Y +
    (oldSelected - menuStart)
    * MENU_ITEM_HEIGHT;



  int newY =
    MENU_START_Y +
    (newSelected - menuStart)
    * MENU_ITEM_HEIGHT;



  drawMenuItem(
    oldSelected,
    oldY,
    false
  );


  drawMenuItem(
    newSelected,
    newY,
    true
  );

}



// ============================
// SETUP
// ============================

void setup()
{

  Serial.begin(115200);


  initDisplay();


  initSound();


  joystick.begin();


  initCompass();


  initGPS();


  bootAnimation();


soundBoot();


  clearScreen();


  drawHeader(
    "MENU"
  );


  drawMenu();


}



// ============================
// LOOP
// ============================

void loop()
{
updateGPS();


  JoyDirection dir =
    joystick.getDirection();



if(dir == JOY_UP)
{
  if(selected > 0)
  {
    int old = selected;

    selected--;

    soundMove();

    updateSelection(
      old,
      selected
    );
  }

  delay(150);
}





 if(dir == JOY_DOWN)
{
  if(selected < menuCount - 1)
  {
    int old = selected;

    selected++;

    soundMove();

    updateSelection(
      old,
      selected
    );
  }

  delay(150);
}




 if(dir == JOY_PRESS)
{

    // ============================
    // COMPASS
    // ============================

    if(selected == 2)
    {

      soundSelect();

      openCompass();


      while(
        joystick.getDirection()
        !=
        JOY_PRESS
      )
      {

        drawCompass();

        delay(100);

      }

    }



    // ============================
    // GPS STATUS
    // ============================

    else if(selected == 3)
    {

      soundSelect();

      openGPS();


      while(
        joystick.getDirection()
        !=
        JOY_PRESS
      )
      {

        drawGPS();

        delay(100);

      }

    }



    // ============================
    // WAYPOINTS
    // ============================

    else if(selected == 4)
    {

      soundSelect();

      clearScreen();

      drawHeader(
        "WAYPOINTS"
      );


      tft.setTextSize(2);
      tft.setTextColor(UI_TEXT);

      tft.setCursor(
        35,
        65
      );

      tft.print(
        "COMING"
      );


      delay(700);

    }



    // ============================
    // CHAT
    // ============================

    else if(selected == 1)
    {

      soundSelect();

      openChat();


      while(
        !chatExitRequested()
      )
      {

        updateChat();

        delay(40);

      }


      soundBack();


      // wait for joystick release
      while(
        joystick.getDirection()
        == 
        JOY_PRESS
      )
      {
        delay(10);
      }


      delay(100);

    }



    // ============================
// STATUS
// ============================

else if(selected == 5)
{

  soundSelect();


  openStatus();


  while(
    joystick.getDirection()
    !=
    JOY_PRESS
  )
  {

    drawStatus();


    delay(200);

  }


  while(
    joystick.getDirection()
    ==
    JOY_PRESS
  )
  {
    delay(10);
  }


  delay(100);

}


// ============================
// OTHER MENUS
// ============================

else
{

  soundSelect();


  clearScreen();


  drawHeader(
    menuItems[selected]
  );


  tft.setTextSize(2);

  tft.setTextColor(
    UI_TEXT
  );


  tft.setCursor(
    35,
    65
  );


  tft.print(
    "COMING"
  );


  delay(700);

}



    clearScreen();


    drawHeader(
      "MENU"
    );


    drawMenu();

}



  delay(20);

}