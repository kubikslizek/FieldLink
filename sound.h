#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

void initSound();

void setVolume(uint8_t volume);

void beep(
  int frequency,
  int duration,
  uint8_t volume = 50
);


// FieldLink sounds

void soundBoot();

void soundMove();

void soundSelect();

void soundKeyHover();

void soundKeyPress();

void soundBack();

void soundGPSSearching();

void soundGPSLock();

void soundMessage();

void soundWarning();

void soundError();

void soundSuccess();

void soundMinorSuccess();

void soundBatteryLow();


// Easter eggs

void soundMozart();

void soundBeethoven();

void soundNokia();


#endif