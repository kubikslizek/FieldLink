#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>


void initKeyboard();

void drawKeyboard();

void updateKeyboard();


char getSelectedKey();


bool keyboardExitRequested();

bool keyboardSendRequested();


#endif