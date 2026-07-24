#ifndef CHAT_H
#define CHAT_H

#include <Arduino.h>


enum ChatState
{
  CHAT_MESSAGES,
  CHAT_KEYBOARD
};


// Selection in message input bar

enum ChatInputSelection
{
  CHAT_SELECT_EXIT,
  CHAT_SELECT_BOX,
  CHAT_SELECT_SEND
};



void openChat();

void drawChat();

void updateChat();

bool chatExitRequested();


#endif