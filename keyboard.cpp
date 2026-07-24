#include "keyboard.h"
#include "display.h"
#include "theme.h"
#include "joystick.h"
#include "icons.h"
#include "sound.h"


static const char keyboardKeys[3][10] =
{
    { 'Q','W','E','R','T','Z','U','I','O','P' },
    { 'A','S','D','F','G','H','J','K','L','Y' },
    { 'X','C','V','B','N','M',',','.','!','?' }
};


static int keyX = 0;
static int keyY = 0;

static bool functionRow = false;

static int functionSelected = 1; 
// 0=EXIT,1=SPACE,2=BACK,3=SEND

static bool pressLock = false;

static char pressedKey = 0;

static bool exitRequest = false;
static bool sendRequest = false;



void initKeyboard()
{
    // HARD RESET POSITION

    keyX = 0;
    keyY = 0;

    functionRow = false;
    functionSelected = 1;

    pressedKey = 0;

    exitRequest = false;
    sendRequest = false;


    // flush joystick state

    delay(50);

    joystick.getDirection();
}



// ======================================================
// Draw single key
// ======================================================

static void drawKey(
    int x,
    int y,
    char c,
    bool selected
)
{
    int px = x * 16;
    int py = 70 + y * 13;


    tft.fillRect(
        px,
        py - 1,
        16,
        14,
        UI_BACKGROUND
    );


    if(selected)
    {
        tft.drawRoundRect(
            px + 1,
            py - 1,
            13,
            13,
            3,
            UI_PRIMARY
        );
    }


    tft.setTextSize(1);

    tft.setTextColor(
        selected ? UI_PRIMARY : UI_TEXT
    );


    tft.setCursor(
        px + 5,
        py + 2
    );


    tft.print(c);
}



// ======================================================
// Space button
// ======================================================

static void drawSpaceButton(bool selected)
{
    const int x = 22;
    const int y = 110;
    const int w = 90;
    const int h = 15;


    uint16_t color =
        selected ? UI_PRIMARY : UI_TEXT;


    tft.drawRoundRect(
        x,
        y,
        w,
        h,
        6,
        color
    );


    tft.setTextSize(1);

    tft.setTextColor(color);


    int16_t bx;
    int16_t by;

    uint16_t bw;
    uint16_t bh;


    tft.getTextBounds(
        "SPACE",
        0,
        0,
        &bx,
        &by,
        &bw,
        &bh
    );


    int tx =
        x + (w - bw) / 2;


    int ty =
        y + (h - bh) / 2;


    tft.setCursor(
        tx,
        ty
    );


    tft.print("SPACE");
}



// ======================================================
// Function buttons
// ======================================================

static void drawFunctionButton(
    int id,
    bool selected
)
{
    uint16_t color =
        selected ? UI_PRIMARY : UI_TEXT;


    switch(id)
    {
        case 0:
            drawExitIcon(
                3,
                109,
                color
            );
            break;


        case 1:
            drawSpaceButton(selected);
            break;


        case 2:
            drawBackIcon(
                116,
                109,
                color
            );
            break;


        case 3:
            drawSendIcon(
                136,
                109,
                color
            );
            break;
    }
}



// ======================================================
// Draw keyboard
// ======================================================

void drawKeyboard()
{
    tft.fillRect(
        0,
        65,
        160,
        70,
        UI_BACKGROUND
    );


    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            drawKey(
                x,
                y,
                keyboardKeys[y][x],
                (!functionRow &&
                 x == keyX &&
                 y == keyY)
            );
        }
    }


    for(int i = 0; i < 4; i++)
    {
        drawFunctionButton(
            i,
            functionRow &&
            (i == functionSelected)
        );
    }
}



// ======================================================
// Update keyboard
// ======================================================

void updateKeyboard()
{
    JoyDirection dir =
        joystick.getDirection();


    int oldX = keyX;
    int oldY = keyY;

    int oldFunc =
        functionSelected;

    bool oldMode =
        functionRow;


    bool moved = false;



    if(!functionRow)
    {

        if(dir == JOY_LEFT && keyX > 0)
        {
            keyX--;
            moved = true;
        }


        if(dir == JOY_RIGHT && keyX < 9)
        {
            keyX++;
            moved = true;
        }


        if(dir == JOY_UP && keyY > 0)
        {
            keyY--;
            moved = true;
        }


        if(dir == JOY_DOWN)
        {
            if(keyY < 2)
            {
                keyY++;
                moved = true;
            }
            else
            {
                functionRow = true;
                functionSelected = 1;
                moved = true;
            }
        }

    }
    else
    {

        if(dir == JOY_LEFT &&
           functionSelected > 0)
        {
            functionSelected--;
            moved = true;
        }


        if(dir == JOY_RIGHT &&
           functionSelected < 3)
        {
            functionSelected++;
            moved = true;
        }


        if(dir == JOY_UP)
        {
            functionRow = false;

            keyX = 3;
            keyY = 2;

            moved = true;
        }

    }



    if(moved)
    {
        soundKeyHover();


        if(oldMode == functionRow)
        {

            if(functionRow)
            {
                drawFunctionButton(
                    oldFunc,
                    false
                );

                drawFunctionButton(
                    functionSelected,
                    true
                );
            }
            else
            {
                drawKey(
                    oldX,
                    oldY,
                    keyboardKeys[oldY][oldX],
                    false
                );


                drawKey(
                    keyX,
                    keyY,
                    keyboardKeys[keyY][keyX],
                    true
                );
            }

        }
        else
        {

            if(oldMode)
            {
                drawFunctionButton(
                    oldFunc,
                    false
                );

                drawKey(
                    keyX,
                    keyY,
                    keyboardKeys[keyY][keyX],
                    true
                );
            }
            else
            {
                drawKey(
                    oldX,
                    oldY,
                    keyboardKeys[oldY][oldX],
                    false
                );

                drawFunctionButton(
                    functionSelected,
                    true
                );
            }

        }
    }



    if(dir == JOY_PRESS)
    {
        if(!pressLock)
        {
            pressLock = true;


            if(!(functionRow &&
                 functionSelected == 0))
            {
                soundKeyPress();
            }


            if(functionRow)
            {

                if(functionSelected == 0)
                {
                    exitRequest = true;
                }

                else if(functionSelected == 1)
                {
                    pressedKey = ' ';
                }

                else if(functionSelected == 2)
                {
                    pressedKey = 8;
                }

                else if(functionSelected == 3)
                {
                    sendRequest = true;
                }

            }
            else
            {
                pressedKey =
                    keyboardKeys[keyY][keyX];
            }

        }
    }


    if(dir != JOY_PRESS)
    {
        pressLock = false;
    }
}



// ======================================================
// Get pressed key
// ======================================================

char getSelectedKey()
{
    char c = pressedKey;

    pressedKey = 0;

    return c;
}



// ======================================================
// Requests
// ======================================================

bool keyboardExitRequested()
{
    if(exitRequest)
    {
        exitRequest = false;
        return true;
    }

    return false;
}



bool keyboardSendRequested()
{
    if(sendRequest)
    {
        sendRequest = false;
        return true;
    }

    return false;
}