#include "status.h"

#include "display.h"
#include "theme.h"
#include "joystick.h"
#include "sound.h"


unsigned long statusStartTime;



// ============================
// Open STATUS
// ============================

void openStatus()
{
    statusStartTime = millis();

    clearScreen();

    drawHeader("STATUS");

    drawStatus();
}



// ============================
// Helper
// ============================

void drawLabel(
    const char* label,
    int y
)
{
    tft.setTextSize(1);

    tft.setTextColor(
        UI_PRIMARY
    );

    tft.setCursor(
        5,
        y
    );

    tft.print(label);
}



void drawValue(
    String value,
    int y
)
{
    tft.setTextSize(1);

    tft.setTextColor(
        UI_TEXT
    );

    tft.setCursor(
        70,
        y
    );

    tft.print(value);
}



// ============================
// Draw STATUS
// ============================

void drawStatus()
{

    tft.fillRect(
        0,
        20,
        160,
        108,
        UI_BACKGROUND
    );



    int y = 28;



    // --------------------
    // Battery
    // --------------------

    drawLabel(
        "BATTERY",
        y
    );


    drawValue(
        "3.85V  72%",
        y + 12
    );



    // --------------------
    // GPS
    // --------------------

    y += 30;


    drawLabel(
        "GPS",
        y
    );


    drawValue(
        "FIX: YES",
        y + 12
    );


    drawValue(
        "SAT: 08",
        y + 24
    );



    // --------------------
    // Radio
    // --------------------

    y += 42;


    drawLabel(
        "RADIO",
        y
    );


    drawValue(
        "NRF24: OK",
        y + 12
    );



    // --------------------
    // System
    // --------------------

    y += 30;


    drawLabel(
        "SYSTEM",
        y
    );


    drawValue(
        "RAM:",
        y + 12
    );


    tft.setCursor(
        105,
        y + 12
    );


    tft.print(
        ESP.getFreeHeap() / 1024
    );


    tft.print(
        "KB"
    );



    // uptime

    unsigned long seconds =
        millis() / 1000;


    char buffer[20];


    sprintf(
        buffer,
        "%02lu:%02lu:%02lu",
        seconds / 3600,
        (seconds / 60) % 60,
        seconds % 60
    );


    drawValue(
        String("UP ") + buffer,
        y + 24
    );
}



// ============================
// Update
// ============================

void updateStatus()
{

    JoyDirection dir =
        joystick.getDirection();


    if(dir == JOY_PRESS)
    {
        soundBack();
        return;
    }

}