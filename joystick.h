#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "config.h"

// ============================
// JOYSTICK DIRECTIONS
// ============================

enum JoyDirection
{
    JOY_NONE = 0,

    JOY_UP,
    JOY_DOWN,

    JOY_LEFT,
    JOY_RIGHT,

    JOY_PRESS
};

// ============================
// JOYSTICK CLASS
// ============================

class Joystick
{
public:

    void begin();

    JoyDirection getDirection();

private:

    // calibrated centers
    int centerX;
    int centerY;

    // deadzone
    static const int DEADZONE = 700;

    // repeat timing
    unsigned long lastMove;
    unsigned long lastPress;

    static const int MOVE_DELAY = 150;
    static const int PRESS_DELAY = 250;
};

// global object
extern Joystick joystick;

#endif