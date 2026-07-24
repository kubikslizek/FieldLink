#ifndef ICONS_H
#define ICONS_H

#include <Adafruit_GFX.h>


#define ICON_SIZE 16



// Main FieldLink icons

enum IconID
{
  ICON_NAV,
  ICON_CHAT,
  ICON_COMPASS,
  ICON_GPS,
  ICON_MAP,
  ICON_BATTERY,
  ICON_SETTINGS,

  // Chat icons
  ICON_SEND,
  ICON_BACKSPACE,
  ICON_EXIT
};



// Generic icon drawer
void drawIcon(
  Adafruit_GFX &display,
  int x,
  int y,
  int id,
  uint16_t color
);



// Chat function icons

void drawSendIcon(
  int x,
  int y,
  uint16_t color
);


void drawBackIcon(
  int x,
  int y,
  uint16_t color
);


void drawExitIcon(
  int x,
  int y,
  uint16_t color
);


#endif