#include "compass.h"

#include <Wire.h>
#include <Adafruit_QMC5883P.h>

#include "display.h"
#include "theme.h"


// ============================
// SENSOR
// ============================

Adafruit_QMC5883P qmc;


// ============================
// DATA
// ============================

float heading = 0;

float magX = 0;
float magY = 0;
float magZ = 0;


// ============================
// FILTER
// ============================

float filteredHeading = 0;
float displayHeading = 0;

bool firstReading = true;


// ============================
// DRAW CONTROL
// ============================

float lastDrawHeading = -100;



// ============================
// INIT
// ============================

void initCompass()
{

  Wire.begin(
    21,
    22
  );


  if(!qmc.begin())
  {
    Serial.println(
      "QMC FAILED"
    );

    return;
  }



  qmc.setRange(
    QMC5883P_RANGE_8G
  );


  qmc.setMode(
    QMC5883P_MODE_CONTINUOUS
  );


  qmc.setODR(
    QMC5883P_ODR_100HZ
  );


  qmc.setOSR(
    QMC5883P_OSR_8
  );


  qmc.setDSR(
    QMC5883P_DSR_1
  );


  qmc.setSetResetMode(
    QMC5883P_SETRESET_ON
  );


  Serial.println(
    "QMC READY"
  );

}



// ============================
// UPDATE SENSOR
// ============================

void updateCompass()
{

  if(
    !qmc.getGaussField(
      &magX,
      &magY,
      &magZ
    )
  )
  {
    return;
  }



  float raw =
    atan2(
      -magY,
      -magX
    )
    *
    180.0
    /
    PI;



  if(raw < 0)
    raw += 360;



  if(firstReading)
  {

    filteredHeading = raw;
    displayHeading = raw;

    firstReading = false;

  }



  float diff =
    raw - filteredHeading;



  if(diff > 180)
    diff -= 360;


  if(diff < -180)
    diff += 360;



  // fast sensor smoothing

  filteredHeading +=
    diff * 0.18;



  if(filteredHeading < 0)
    filteredHeading += 360;


  if(filteredHeading >= 360)
    filteredHeading -= 360;




  float displayDiff =
    filteredHeading -
    displayHeading;



  if(displayDiff > 180)
    displayDiff -= 360;


  if(displayDiff < -180)
    displayDiff += 360;



  // display smoothing

  displayHeading +=
    displayDiff * 0.35;



  if(displayHeading < 0)
    displayHeading += 360;


  if(displayHeading >= 360)
    displayHeading -= 360;



  heading =
    displayHeading;

}



// ============================
// GET HEADING
// ============================

float getHeading()
{
  return heading;
}



// ============================
// OPEN COMPASS
// ============================

void openCompass()
{

  clearScreen();

  drawHeader(
    "COMPASS"
  );


  // static divider

  tft.drawLine(
    0,
    50,
    160,
    50,
    UI_TEXT
  );


  // static pointer

  tft.fillTriangle(
    80,
    57,
    75,
    50,
    85,
    50,
    UI_PRIMARY
  );

}



// ============================
// DRAW COMPASS
// ============================

void drawCompass()
{

  updateCompass();



  // redraw only when needed

  if(
    abs(
      heading -
      lastDrawHeading
    )
    <
    0.5
  )
  {
    return;
  }


  lastDrawHeading =
    heading;



  // ============================
  // CLEAR ONLY MOVING AREAS
  // ============================


  tft.fillRect(
    0,
    22,
    160,
    26,
    UI_BACKGROUND
  );


  tft.fillRect(
    30,
    70,
    100,
    35,
    UI_BACKGROUND
  );



// ============================
// COMPASS TAPE
// ============================

String dirs[8] =
{
  "N",
  "NE",
  "E",
  "SE",
  "S",
  "SW",
  "W",
  "NW"
};


int angles[8] =
{
  0,
  45,
  90,
  135,
  180,
  225,
  270,
  315
};


for(
  int i = 0;
  i < 8;
  i++
)
{

  float diff =
    angles[i] - heading;


  if(diff > 180)
    diff -= 360;


  if(diff < -180)
    diff += 360;



  int x =
    80 + (diff * 1.2);



  // REAL text bounds
  int textWidth =
    dirs[i].length() * 12;


  int textX =
    x - textWidth / 2;



  // leave safety margin

  if(
    textX >= 15 &&
    textX + textWidth <= 145
  )
  {

    tft.setTextSize(2);


    if(
      abs(diff) < 8
    )
    {
      tft.setTextColor(
        UI_PRIMARY
      );
    }
    else
    {
      tft.setTextColor(
        UI_TEXT
      );
    }


    tft.setCursor(
      textX,
      27
    );


    tft.print(
      dirs[i]
    );

  }

}

  // redraw divider after tape

  tft.drawLine(
    0,
    50,
    160,
    50,
    UI_TEXT
  );


  // redraw pointer

  tft.fillTriangle(
    80,
    57,
    75,
    50,
    85,
    50,
    UI_PRIMARY
  );



  // ============================
  // BIG HEADING
  // ============================


  tft.setTextColor(
    UI_PRIMARY
  );


  tft.setTextSize(
    4
  );


  int x;


  if(heading < 10)
    x = 68;

  else if(heading < 100)
    x = 58;

  else
    x = 48;



  tft.setCursor(
    x,
    75
  );


  tft.print(
    (int)heading
  );

}