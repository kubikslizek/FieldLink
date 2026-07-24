// ============================
// chat.cpp
// ============================

#include "chat.h"
#include "display.h"
#include "theme.h"
#include "keyboard.h"
#include "sound.h"
#include "joystick.h"
#include "icons.h"

void drawKeyboardText();
void drawChatMessages();


// ============================
// Keyboard temporary text
// ============================

String keyboardText = "";

const uint16_t CHAT_MAX_CHARS = 40;


// ============================
// Message storage
// ============================

#define MAX_MESSAGES 8

struct ChatMessage
{
    String text;
    bool fromUser;
};

ChatMessage messages[MAX_MESSAGES];

int messageCount = 0;


// ============================
// Chat state
// ============================

ChatState chatState = CHAT_MESSAGES;

ChatInputSelection chatSelection = CHAT_SELECT_BOX;

bool chatExit = false;


// ============================
// Cursor
// ============================

unsigned long cursorTimer = 0;

bool cursorVisible = true;


// ============================
// Add message
// ============================

void addChatMessage(String text, bool fromUser)
{
    if(text.length() == 0)
        return;


    if(messageCount >= MAX_MESSAGES)
    {
        for(int i = 0; i < MAX_MESSAGES - 1; i++)
        {
            messages[i] = messages[i + 1];
        }

        messageCount = MAX_MESSAGES - 1;
    }


    messages[messageCount].text = text;
    messages[messageCount].fromUser = fromUser;

    messageCount++;
}


// ============================
// Character limiter
// ============================

void addKeyboardCharacter(char c)
{
    if(keyboardText.length() >= CHAT_MAX_CHARS)
    {
        soundError();
        return;
    }

    keyboardText += c;
}


// ============================
// Bottom input preview
// ============================

String getBottomBarText(String text)
{
    if(text.length() == 0)
        return "";


    String out = text;


    int16_t x,y;
    uint16_t w,h;


    tft.setTextSize(1);


    while(out.length() > 0)
    {
        tft.getTextBounds(
            out,
            0,
            0,
            &x,
            &y,
            &w,
            &h
        );


        if(w <= 60)
            break;


        out.remove(0,1);
    }


    if(out.length() < text.length())
    {
        return "..." + out;
    }


    return out;
}


// ============================
// Open chat
// ============================

void openChat()
{
    chatState = CHAT_MESSAGES;

    chatSelection = CHAT_SELECT_BOX;

    keyboardText = "";

    chatExit = false;


    cursorVisible = true;

    cursorTimer = millis();


    clearScreen();

    drawHeader("CHAT");

    drawChat();
}


// ============================
// chat.cpp PART 2/3
// ============================


// ============================
// Input bar
// ============================

void drawChatInputBar()
{
    int y = 105;


    bool exitSel =
        chatSelection == CHAT_SELECT_EXIT;

    bool boxSel =
        chatSelection == CHAT_SELECT_BOX;

    bool sendSel =
        chatSelection == CHAT_SELECT_SEND;



    drawExitIcon(
        4,
        y,
        exitSel ? UI_PRIMARY : UI_TEXT
    );


    tft.drawRoundRect(
        31,
        y,
        97,
        16,
        6,
        boxSel ? UI_PRIMARY : UI_TEXT
    );


    tft.setTextSize(1);


    tft.setCursor(
        37,
        y + 5
    );


    if(keyboardText.length() == 0)
    {
        tft.setTextColor(UI_DISABLED);

        tft.print(
            "TYPE HERE..."
        );
    }
    else
    {
        tft.setTextColor(UI_TEXT);

        tft.print(
            getBottomBarText(keyboardText)
        );
    }



    drawSendIcon(
        133,
        y,
        sendSel ? UI_PRIMARY : UI_TEXT
    );
}


// ============================
// Message bubble renderer
// ============================

void drawMessageBubble(
    String text,
    bool fromUser,
    int y
)
{
    tft.setTextSize(1);


    int16_t bx,by;

    uint16_t bw,bh;


    tft.getTextBounds(
        text,
        0,
        0,
        &bx,
        &by,
        &bw,
        &bh
    );


    int bubbleW =
        bw + 12;


    int bubbleH =
        bh + 10;


    int x;



    if(fromUser)
    {
        x =
            160 - bubbleW - 5;


        tft.fillRoundRect(
            x,
            y,
            bubbleW,
            bubbleH,
            5,
            UI_BACKGROUND
        );


        tft.drawRoundRect(
            x,
            y,
            bubbleW,
            bubbleH,
            5,
            UI_PRIMARY
        );


        tft.setTextColor(
            UI_PRIMARY
        );
    }
    else
    {
        x = 5;


        tft.fillRoundRect(
            x,
            y,
            bubbleW,
            bubbleH,
            5,
            UI_PRIMARY
        );


        tft.setTextColor(
            ST77XX_BLACK
        );
    }


    tft.setCursor(
        x + 6,
        y + 5
    );


    tft.print(text);
}


// ============================
// Draw stored messages
// ============================

void drawChatMessages()
{
    int y = 25;


    int start = 0;


    if(messageCount > 5)
    {
        start =
            messageCount - 5;
    }


    for(
        int i = start;
        i < messageCount;
        i++
    )
    {
        drawMessageBubble(
            messages[i].text,
            messages[i].fromUser,
            y
        );


        y += 18;


        if(y > 95)
            break;
    }
}


// ============================
// Keyboard text
// ============================

void drawKeyboardText()
{
    tft.fillRect(
        0,
        20,
        160,
        40,
        UI_BACKGROUND
    );


    String line1 = "";

    String line2 = "";


   const int maxChars = 22;


if(keyboardText.length() <= maxChars)
{
    line1 = keyboardText;
}
else
{
    int split = maxChars;


    // move backwards until a space
    while(
        split > 0 &&
        keyboardText[split] != ' '
    )
    {
        split--;
    }


    // if there was no space, hard split
    if(split == 0)
    {
        split = maxChars;
    }


    line1 =
        keyboardText.substring(
            0,
            split
        );


    line2 =
        keyboardText.substring(
            split + 1
        );
}


    tft.setTextSize(1);

    tft.setTextColor(
        UI_TEXT
    );



    tft.setCursor(
        4,
        30
    );

    tft.print(">");



    tft.setCursor(
        14,
        30
    );

    tft.print(line1);



    int cursorY = 30;

    String cursorLine =
        line1;



    if(line2.length())
    {
        tft.setCursor(
            14,
            42
        );

        tft.print(line2);


        cursorY = 42;

        cursorLine = line2;
    }



    if(cursorVisible)
    {
        int16_t bx,by;

        uint16_t bw,bh;


        tft.getTextBounds(
            cursorLine,
            14,
            cursorY,
            &bx,
            &by,
            &bw,
            &bh
        );


        tft.setCursor(
            14 + bw,
            cursorY
        );


        tft.print("_");
    }
}

// ============================
// chat.cpp PART 3/3
// ============================


// ============================
// Draw chat screen
// ============================

void drawChat()
{
    if(chatState == CHAT_MESSAGES)
    {
        tft.fillRect(
            0,
            20,
            160,
            105,
            UI_BACKGROUND
        );


        drawChatMessages();


        drawChatInputBar();
    }


    else if(chatState == CHAT_KEYBOARD)
    {
        tft.fillRect(
            0,
            20,
            160,
            120,
            UI_BACKGROUND
        );


        drawKeyboard();


        drawKeyboardText();
    }
}


// ============================
// Update chat
// ============================

void updateChat()
{

    // ============================
    // Message screen
    // ============================

    if(chatState == CHAT_MESSAGES)
    {

        JoyDirection dir =
            joystick.getDirection();



        if(dir == JOY_LEFT)
        {
            if(chatSelection > CHAT_SELECT_EXIT)
            {
                chatSelection =
                    ChatInputSelection(
                        chatSelection - 1
                    );


                soundKeyHover();

                drawChatInputBar();
            }
        }



        if(dir == JOY_RIGHT)
        {
            if(chatSelection < CHAT_SELECT_SEND)
            {
                chatSelection =
                    ChatInputSelection(
                        chatSelection + 1
                    );


                soundKeyHover();

                drawChatInputBar();
            }
        }




        if(dir == JOY_PRESS)
        {

            if(chatSelection == CHAT_SELECT_EXIT)
            {
                chatExit = true;

                return;
            }



            if(chatSelection == CHAT_SELECT_BOX)
            {
                soundSelect();


                keyboardText = "";


                chatState =
                    CHAT_KEYBOARD;


                initKeyboard();


                cursorVisible = true;

                cursorTimer =
                    millis();


                drawChat();

                return;
            }




            if(chatSelection == CHAT_SELECT_SEND)
            {

                if(keyboardText.length())
                {
                    soundSuccess();


                    addChatMessage(
                        keyboardText,
                        true
                    );


                    keyboardText = "";


                    drawChat();

                }
                else
                {
                    soundError();
                }


                return;
            }
        }
    }



    // ============================
    // Keyboard screen
    // ============================

    else if(chatState == CHAT_KEYBOARD)
    {

        if(
            millis() - cursorTimer > 500
        )
        {
            cursorTimer =
                millis();


            cursorVisible =
                !cursorVisible;


            drawKeyboardText();
        }



        updateKeyboard();



        char c =
            getSelectedKey();



        if(c)
        {

            cursorVisible = true;

            cursorTimer =
                millis();



            if(c == 8)
            {

                if(keyboardText.length())
                {
                    keyboardText.remove(
                        keyboardText.length()-1
                    );
                }

            }


            else
            {
                addKeyboardCharacter(c);
            }



            drawKeyboardText();

        }




        if(keyboardExitRequested())
        {

            soundBack();


            keyboardText = "";


            chatState =
                CHAT_MESSAGES;


            chatSelection =
                CHAT_SELECT_BOX;



            drawChat();


            return;

        }




       if(keyboardSendRequested())
{

    if(keyboardText.length())
    {

        soundMinorSuccess();


        chatState =
            CHAT_MESSAGES;


        chatSelection =
            CHAT_SELECT_BOX;


        drawChat();

    }
    else
    {
        soundError();
    }


    return;


        }

    }

}


// ============================
// Exit request
// ============================

bool chatExitRequested()
{
    if(chatExit)
    {
        chatExit = false;

        return true;
    }


    return false;
}