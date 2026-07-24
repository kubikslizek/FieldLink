#include <Arduino.h>
#include "joystick.h"

Joystick joystick;

// ============================
// INIT
// ============================

void Joystick::begin()
{
    pinMode(JOY_SW, INPUT_PULLUP);

    analogReadResolution(12);

    delay(300);

    long sumX = 0;
    long sumY = 0;

    for(int i = 0; i < 60; i++)
    {
        sumX += analogRead(JOY_X);
        sumY += analogRead(JOY_Y);
        delay(5);
    }

    centerX = sumX / 60;
    centerY = sumY / 60;

    lastMove = 0;
    lastPress = 0;

    Serial.print("Joystick X center: ");
    Serial.println(centerX);

    Serial.print("Joystick Y center: ");
    Serial.println(centerY);
}

// ============================
// GET DIRECTION
// ============================

JoyDirection Joystick::getDirection()
{
    // ---------- Button ----------

    if(digitalRead(JOY_SW) == LOW)
    {
        if(millis() - lastPress > PRESS_DELAY)
        {
            lastPress = millis();
            return JOY_PRESS;
        }
    }

    // ---------- Repeat limiter ----------

    if(millis() - lastMove < MOVE_DELAY)
    {
        return JOY_NONE;
    }

    int x = analogRead(JOY_X);
    int y = analogRead(JOY_Y);

    int dx = x - centerX;
    int dy = y - centerY;

    int absX = abs(dx);
    int absY = abs(dy);

    // inside deadzone

    if(absX < DEADZONE && absY < DEADZONE)
        return JOY_NONE;

    lastMove = millis();

    // ----------------------------
    // Dominant axis
    // ----------------------------

    if(absX > absY)
    {
        if(dx < 0)
            return JOY_LEFT;
        else
            return JOY_RIGHT;
    }
    else
    {
        if(dy < 0)
            return JOY_UP;
        else
            return JOY_DOWN;
    }
}