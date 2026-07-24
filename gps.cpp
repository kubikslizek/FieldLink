#include "gps.h"

#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#include "display.h"
#include "theme.h"
#include "sound.h"
#include "statusbar.h"



// ============================
// GPS
// ============================

TinyGPSPlus gps;

HardwareSerial GPSserial(2);



// ============================
// DATA
// ============================

float latitude = 0;
float longitude = 0;
float altitude = 0;
float speed = 0;
float gpsHeading = 0;

float hdop = 99;


int satellites = 0;

int gpsHour = 0;
int gpsMinute = 0;


bool timeValid = false;
bool fix = false;
bool previousFix = false;
bool firstGPSDraw = true;


// ============================
// DISPLAY CACHE
// ============================

float oldLatitude = -999;
float oldLongitude = -999;
float oldAltitude = -999;
float oldSpeed = -999;
float oldHeading = -999;
float oldHDOP = -999;

int oldSatellites = -1;

bool oldFix = false;

int oldAccState = -1;



// ============================
// INIT
// ============================

void initGPS()
{

  GPSserial.begin(
    9600,
    SERIAL_8N1,
    16,
    17
  );


  Serial.println(
    "GPS READY"
  );

}



// ============================
// UPDATE GPS DATA
// ============================

void updateGPS()
{

  while(
    GPSserial.available()
  )
  {

    gps.encode(
      GPSserial.read()
    );

  }



  // LOCATION

  if(
    gps.location.isValid()
  )
  {

    latitude =
      gps.location.lat();


    longitude =
      gps.location.lng();


    fix = true;

  }
  else
  {

    fix = false;

  }



  // TIME

  if(
    gps.time.isValid()
  )
  {

    gpsHour =
      gps.time.hour();


    gpsMinute =
      gps.time.minute();



    // Czech summer time

    gpsHour += 2;


    if(
      gpsHour >= 24
    )
    {
      gpsHour -= 24;
    }


    timeValid = true;

  }
  else
  {

    timeValid = false;

  }



  // GPS LOCK SOUND

  if(
    fix &&
    !previousFix
  )
  {

    soundGPSLock();

  }


  if(
    !fix &&
    previousFix
  )
  {

    soundWarning();

  }


  previousFix = fix;




  // ALTITUDE

  if(
    gps.altitude.isValid()
  )
  {

    altitude =
      gps.altitude.meters();

  }




  // SPEED

  if(
    gps.speed.isValid()
  )
  {

    speed =
      gps.speed.kmph();

  }




  // SATELLITES

  if(
    gps.satellites.isValid()
  )
  {

    satellites =
      gps.satellites.value();

  }




  // HEADING

  if(
    gps.course.isValid()
  )
  {

    gpsHeading =
      gps.course.deg();

  }




  // HDOP

  if(
    gps.hdop.isValid()
  )
  {

    hdop =
      gps.hdop.hdop();

  }

}



// ============================
// GETTERS
// ============================

bool gpsHasFix()
{
  return fix;
}


float getLatitude()
{
  return latitude;
}


float getLongitude()
{
  return longitude;
}


float getAltitude()
{
  return altitude;
}


float getSpeed()
{
  return speed;
}


float getHDOP()
{
  return hdop;
}



// ============================
// OPEN GPS SCREEN
// ============================

void openGPS()
{

  // reset display cache
  oldLatitude = -999;
  oldLongitude = -999;
  oldAltitude = -999;
  oldSpeed = -999;
  oldHeading = -999;
  oldHDOP = -999;

  oldSatellites = -1;
  oldFix = !fix;
  oldAccState = -1;

  firstGPSDraw = true;


  clearScreen();


  drawHeader(
    "GPS"
  );


  clearScreen();


  drawHeader(
    "GPS"
  );


  tft.setTextSize(1);

  tft.setTextColor(
    UI_TEXT
  );



  // STATIC LABELS


  tft.setCursor(
    5,
    50
  );

  tft.print(
    "SAT"
  );



  tft.setCursor(
    5,
    68
  );

  tft.print(
    "LAT"
  );



  tft.setCursor(
    5,
    80
  );

  tft.print(
    "LON"
  );



  tft.setCursor(
    5,
    100
  );

  tft.print(
    "ALT"
  );



  tft.setCursor(
    80,
    100
  );

  tft.print(
    "SPD"
  );



  tft.setCursor(
    5,
    115
  );

  tft.print(
    "HDG"
  );



  tft.setCursor(
    80,
    115
  );

  tft.print(
    "ACC"
  );

}


// ============================
// DRAW GPS
// ============================

void drawGPS()
{

  updateGPS();


  // ============================
  // STATUS BAR
  // ============================

  static unsigned long lastBarUpdate = 0;


  if(
    millis() - lastBarUpdate > 1000
  )
  {

    drawStatusBar();

    lastBarUpdate = millis();

  }



  // ============================
  // LOCK STATUS
  // ============================

 if(
  fix != oldFix ||
  firstGPSDraw
)
  {

    tft.fillRect(
      5,
      25,
      100,
      20,
      UI_BACKGROUND
    );


    tft.setTextSize(
      2
    );


    if(fix)
    {

      tft.fillCircle(
        15,
        35,
        5,
        UI_PRIMARY
      );


      tft.setTextColor(
        UI_PRIMARY
      );


      tft.setCursor(
        28,
        27
      );


      tft.print(
        "LOCKED"
      );

    }
    else
    {

      tft.fillCircle(
        15,
        35,
        5,
        UI_TEXT
      );


      tft.setTextColor(
        UI_TEXT
      );


      tft.setCursor(
        28,
        27
      );


      tft.print(
        "SEARCH"
      );

    }


    oldFix = fix;
firstGPSDraw = false;
  }



  tft.setTextSize(
    1
  );

  tft.setTextColor(
    UI_TEXT
  );



  // ============================
  // SATELLITES
  // ============================

  if(
    satellites != oldSatellites
  )
  {

    for(
      int i = 0;
      i < 10;
      i++
    )
    {

      tft.fillRect(
        30 + i * 6,
        50,
        4,
        8,
        i < satellites ?
        UI_PRIMARY :
        0x4208
      );

    }


    oldSatellites = satellites;

  }




  // ============================
  // LATITUDE
  // ============================

  if(
    latitude != oldLatitude
  )
  {

    tft.fillRect(
      30,
      65,
      130,
      10,
      UI_BACKGROUND
    );


    tft.setCursor(
      30,
      68
    );


    tft.print(
      latitude,
      5
    );


    oldLatitude = latitude;

  }




  // ============================
  // LONGITUDE
  // ============================

  if(
    longitude != oldLongitude
  )
  {

    tft.fillRect(
      30,
      77,
      130,
      10,
      UI_BACKGROUND
    );


    tft.setCursor(
      30,
      80
    );


    tft.print(
      longitude,
      5
    );


    oldLongitude = longitude;

  }




  // ============================
  // ALTITUDE
  // ============================

  if(
    altitude != oldAltitude
  )
  {

    tft.fillRect(
      30,
      97,
      45,
      10,
      UI_BACKGROUND
    );


    tft.setCursor(
      30,
      100
    );


    tft.print(
      altitude,
      0
    );


    tft.print(
      "m"
    );


    oldAltitude = altitude;

  }




  // ============================
  // SPEED
  // ============================

  if(
    speed != oldSpeed
  )
  {

    tft.fillRect(
      105,
      97,
      45,
      10,
      UI_BACKGROUND
    );


    tft.setCursor(
      105,
      100
    );


    tft.print(
      speed,
      1
    );


    oldSpeed = speed;

  }




  // ============================
  // HEADING
  // ============================

  if(
    gpsHeading != oldHeading
  )
  {

    tft.fillRect(
      30,
      112,
      45,
      10,
      UI_BACKGROUND
    );


    tft.setCursor(
      30,
      115
    );


    tft.print(
      gpsHeading,
      0
    );


    tft.print(
      "deg"
    );


    oldHeading = gpsHeading;

  }




  // ============================
  // ACCURACY
  // ============================

  int accState;


  if(
    hdop <= 1.5
  )
  {

    accState = 0; // green

  }
  else if(
    hdop <= 3.0
  )
  {

    accState = 1; // yellow

  }
  else
  {

    accState = 2; // red

  }



  if(
    accState != oldAccState
  )
  {

    uint16_t accColor;


    if(
      accState == 0
    )
    {

      accColor = 0x07E0;

    }
    else if(
      accState == 1
    )
    {

      accColor = 0xFFE0;

    }
    else
    {

      accColor = 0xF800;

    }



    tft.fillCircle(
      113,
      119,
      3,
      UI_BACKGROUND
    );


    tft.fillCircle(
      113,
      119,
      3,
      accColor
    );


    oldAccState = accState;

  }

}



// ============================
// TIME
// ============================

int getHour()
{
  return gpsHour;
}



int getMinute()
{
  return gpsMinute;
}



bool gpsTimeValid()
{
  return timeValid;
}