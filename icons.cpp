#include "icons.h"
#include "display.h"
#include "theme.h"
#include <Arduino.h>

void drawIcon(
  Adafruit_GFX &d,
  int x,
  int y,
  int id,
  uint16_t unused
)
{


uint16_t c;


switch(id)
{


// =====================
// NAVIGATION
// =====================

case ICON_NAV:

c = 0x07FF; // cyan


d.fillTriangle(
  x+8,
  y,
  x+2,
  y+15,
  x+8,
  y+11,
  c
);


d.fillTriangle(
  x+8,
  y,
  x+14,
  y+15,
  x+8,
  y+11,
  0xFFFF
);


break;



// =====================
// CHAT
// =====================

case ICON_CHAT:

c = 0x07E0; // green


d.fillRoundRect(
  x+1,
  y+2,
  14,
  11,
  3,
  c
);


d.fillTriangle(
  x+5,
  y+12,
  x+3,
  y+15,
  x+9,
  y+12,
  c
);


break;




// =====================
// COMPASS
// =====================

case ICON_COMPASS:


d.fillTriangle(
  x+8,
  y+1,
  x+6,
  y+8,
  x+10,
  y+8,
  0xF800
);



d.fillTriangle(
  x+8,
  y+15,
  x+6,
  y+8,
  x+10,
  y+8,
  0xFFFF
);


break;





// =====================
// GPS SATELLITE
// =====================

case ICON_GPS:


c = 0x001F; // dark blue solar panels


// left solar panel

d.fillRect(
  x+1,
  y+6,
  5,
  5,
  c
);


// right solar panel

d.fillRect(
  x+10,
  y+6,
  5,
  5,
  c
);


// solar panel lines

d.drawLine(
  x+3,
  y+6,
  x+3,
  y+10,
  0x07FF
);


d.drawLine(
  x+12,
  y+6,
  x+12,
  y+10,
  0x07FF
);


// satellite body

d.fillRoundRect(
  x+6,
  y+4,
  4,
  9,
  1,
  0xFFFF
);


// small body detail

d.fillRect(
  x+7,
  y+6,
  2,
  3,
  0x07FF
);


// antenna

d.drawLine(
  x+8,
  y+2,
  x+8,
  y+4,
  0x07FF
);


// top antenna dot

d.fillCircle(
  x+8,
  y+2,
  1,
  0x07FF
);


break;



// =====================
// WAYPOINT PIN
// =====================

case ICON_MAP:


c = 0xF800;


d.fillCircle(
  x+8,
  y+6,
  5,
  c
);


d.fillTriangle(
  x+8,
  y+15,
  x+3,
  y+8,
  x+13,
  y+8,
  c
);


d.fillCircle(
  x+8,
  y+6,
  2,
  0xFFFF
);


break;







// =====================
// BATTERY
// =====================

case ICON_BATTERY:

c = 0x07E0;


d.drawRect(
  x+2,
  y+5,
  12,
  8,
  c
);


d.fillRect(
  x+4,
  y+7,
  7,
  4,
  c
);


d.fillRect(
  x+14,
  y+7,
  2,
  4,
  c
);


break;






// =====================
// SETTINGS
// =====================

case ICON_SETTINGS:

c = 0x8410;


d.drawCircle(
  x+8,
  y+8,
  7,
  c
);


d.fillCircle(
  x+8,
  y+8,
  3,
  c
);


break;


}


}




// ============================
// CHAT SEND ICON
// Slim rounded button + arrow
// Longer rectangle
// ============================

void drawSendIcon(
  int x,
  int y,
  uint16_t c
)
{

  // Rounded rectangle outline (longer)

  // top edge
  tft.drawLine(
    x + 5,
    y + 3,
    x + 16,
    y + 3,
    c
  );


  // top-right corner
  tft.drawPixel(
    x + 17,
    y + 4,
    c
  );


  // right edge
  tft.drawLine(
    x + 17,
    y + 4,
    x + 17,
    y + 12,
    c
  );


  // bottom-right corner
  tft.drawPixel(
    x + 16,
    y + 13,
    c
  );


  // bottom edge
  tft.drawLine(
    x + 16,
    y + 13,
    x + 5,
    y + 13,
    c
  );


  // bottom-left corner
  tft.drawPixel(
    x + 4,
    y + 12,
    c
  );


  // left edge
  tft.drawLine(
    x + 4,
    y + 12,
    x + 4,
    y + 4,
    c
  );


  // top-left corner
  tft.drawPixel(
    x + 5,
    y + 3,
    c
  );


  // ============================
  // Center arrow
  // ============================

  // shaft
  tft.drawLine(
    x + 8,
    y + 8,
    x + 13,
    y + 8,
    c
  );


  // arrow head
  tft.drawLine(
    x + 11,
    y + 6,
    x + 14,
    y + 8,
    c
  );

  tft.drawLine(
    x + 14,
    y + 8,
    x + 11,
    y + 10,
    c
  );

}

// ============================
// CHAT BACKSPACE ICON
// Slim modern delete symbol
// ============================

void drawBackIcon(
  int x,
  int y,
  uint16_t c
)
{

  // Left arrow point
  tft.drawLine(
    x + 1,
    y + 8,
    x + 5,
    y + 3,
    c
  );

  tft.drawLine(
    x + 1,
    y + 8,
    x + 5,
    y + 13,
    c
  );


  // Top edge
  tft.drawLine(
    x + 5,
    y + 3,
    x + 15,
    y + 3,
    c
  );


  // Rounded top-right corner
  tft.drawPixel(
    x + 16,
    y + 4,
    c
  );

  tft.drawLine(
    x + 16,
    y + 4,
    x + 16,
    y + 12,
    c
  );


  // Rounded bottom-right corner
  tft.drawPixel(
    x + 16,
    y + 12,
    c
  );


  // Bottom edge
  tft.drawLine(
    x + 16,
    y + 12,
    x + 15,
    y + 13,
    c
  );

  tft.drawLine(
    x + 15,
    y + 13,
    x + 5,
    y + 13,
    c
  );


  // Delete X
  tft.drawLine(
    x + 8,
    y + 6,
    x + 12,
    y + 10,
    c
  );

  tft.drawLine(
    x + 12,
    y + 6,
    x + 8,
    y + 10,
    c
  );

}

// ============================
// CHAT EXIT ICON
// Symmetrical X
// ============================

void drawExitIcon(
  int x,
  int y,
  uint16_t c
)
{

  // First diagonal
  tft.drawLine(
    x + 3,
    y + 3,
    x + 12,
    y + 12,
    c
  );


  // Second diagonal
  tft.drawLine(
    x + 12,
    y + 3,
    x + 3,
    y + 12,
    c
  );


  // Thickness
  tft.drawLine(
    x + 4,
    y + 3,
    x + 13,
    y + 12,
    c
  );


  tft.drawLine(
    x + 13,
    y + 3,
    x + 4,
    y + 12,
    c
  );

}