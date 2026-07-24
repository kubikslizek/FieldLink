#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "config.h"


extern Adafruit_ST7735 tft;


void initDisplay();

void clearScreen();

void drawHeader(const char* title);


#endif