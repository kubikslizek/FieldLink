#include <Arduino.h>
#include "sound.h"


#define BUZZER_PIN 25


uint8_t masterVolume = 50;



// ==========================
// INIT
// ==========================

void initSound()
{

  ledcAttach(
    BUZZER_PIN,
    2000,
    8
  );


  ledcWrite(
    BUZZER_PIN,
    0
  );

}



// ==========================
// VOLUME
// ==========================

void setVolume(
  uint8_t volume
)
{

  if(volume > 100)
    volume = 100;


  masterVolume = volume;

}



// ==========================
// BEEP ENGINE
// ==========================

void beep(
  int frequency,
  int duration,
  uint8_t volume
)
{

  uint8_t finalVolume =
    map(
      volume,
      0,
      100,
      0,
      masterVolume
    );


  int duty =
    map(
      finalVolume,
      0,
      100,
      0,
      255
    );


  ledcWriteTone(
    BUZZER_PIN,
    frequency
  );


  ledcWrite(
    BUZZER_PIN,
    duty
  );


  delay(duration);


  ledcWrite(
    BUZZER_PIN,
    0
  );


  ledcWriteTone(
    BUZZER_PIN,
    0
  );


  delay(20);

}



// ==========================
// NORMAL SOUNDS
// ==========================


void soundBoot()
{

  beep(523,100);
  beep(659,100);
  beep(784,250);

}



void soundMove()
{

  beep(1200,35,30);

}

void soundKeyHover()
{
  beep(
    1800,
    12,
    8
  );
}

void soundSelect()
{

  beep(700,80);
  beep(1200,120);

}

void soundKeyPress()
{
  beep(
    900,
    35,
    15
  );
}


void soundBack()
{

  beep(1200,80);
  beep(700,100);

}



void soundGPSSearching()
{

  beep(500,80,30);

}



void soundGPSLock()
{

  beep(600,100);
  beep(900,100);
  beep(1300,250);

}



void soundMessage()
{

  beep(1000,80);
  beep(1500,120);

}

void soundMinorSuccess()
{

  beep(1000,60);
  beep(1300,80);

}



void soundSuccess()
{

  beep(900,80);
  beep(1200,100);
  beep(1600,180);

}

void soundWarning()
{

  beep(350,200);
  beep(350,200);

}



void soundError()
{

  beep(250,300);
  beep(250,300);

}



void soundBatteryLow()
{

  beep(900,100);
  beep(650,120);
  beep(400,200);

}



// ==========================
// EASTER EGGS
// ==========================


void soundBeethoven()
{

  beep(659,150);
  beep(659,150);
  beep(659,150);
  beep(523,500);

}



void soundMozart()
{

  beep(784,180);
  beep(784,180);
  beep(784,180);

  beep(1046,300);

  beep(988,180);
  beep(880,180);
  beep(784,300);

}



void soundNokia()
{

  beep(659,200);
  beep(587,200);
  beep(523,200);
  beep(440,400);

  beep(523,200);
  beep(587,200);
  beep(659,400);

}


