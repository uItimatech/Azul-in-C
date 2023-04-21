#include <windows.h>
#include <stdio.h>


#include "input_handler.h"
#include "console_handler.h"


// THIS IS WHERE INPUTS ARE PROCESSED

// Default character size in pixels (Automatically adjusted)
int termCharWidth = 8;
int termCharHeight = 16;

double leftMargin = 0;
double topMargin = 0;

// --- FUNCTIONS ---


// CURRENTLY UNUSED
// Gets the size of a character of the terminal in pixels
/*SIZE getCharSize() {
    HDC hdc = GetDC(NULL);
    char character = 'X';
    SIZE size;
    GetTextExtentPoint32(hdc, &character, 1, &size);
    ReleaseDC(NULL, hdc);

    return size;
}*/

// Returns raw mouse coordinates as a POINT struct
POINT getMousePos() {
    POINT mousePos;
    GetCursorPos(&mousePos);
    mousePos.x -= leftMargin/2 - termCharWidth*consoleWidth/2; //414
    mousePos.y -= topMargin/2; //46
    return mousePos;
}

// Returns mouse coordinates on the terminal as a POINT struct
POINT getTMousePos() {

    POINT mousePos = getMousePos();
    POINT tMousePos;

    tMousePos.x = mousePos.x / termCharWidth;
    tMousePos.y = mousePos.y / termCharHeight;

    return tMousePos;
}

// Returns mouse coordinates on the game boards as a POINT struct
// Returns coordinates between (0, 0) and (10, 5) or (-1, -1) if the mouse is outside the boards
// Side board corners are (65,43) and (105,63) (by default; upper left and lower right)
// Main board corners are (109,43) and (149,63) (by default; upper left and lower right)
POINT getMouseBoardTilePos() {
    POINT mousePos = getMousePos();
    POINT tMousePos;

    tMousePos.x = mousePos.x / termCharWidth;
    tMousePos.y = mousePos.y / termCharHeight;

    if (tMousePos.x >= 173 && tMousePos.x <= 213 && tMousePos.y >= 43 && tMousePos.y <= 63) {
        tMousePos.x = (tMousePos.x - 172)/8+1;
        tMousePos.y = (tMousePos.y - 43)/4+1;
    } else if (tMousePos.x >= 216 && tMousePos.x <= 256 && tMousePos.y >= 43 && tMousePos.y <= 63) {
        tMousePos.x = (tMousePos.x - 216)/8+6;
        tMousePos.y = (tMousePos.y - 43)/4+1;
    } else {
        tMousePos.x = -1;
        tMousePos.y = -1;
    }

    return tMousePos;
}

// Returns 1 if the mouse is in the specified rectangle, 0 otherwise
int isCursorInRect(int x, int y, int width, int height){
    POINT mousePos = getMousePos();
    POINT tMousePos;

    tMousePos.x = mousePos.x / termCharWidth;
    tMousePos.y = mousePos.y / termCharHeight;

    if (tMousePos.x >= x && tMousePos.x <= x+width && tMousePos.y >= y && tMousePos.y <= y+height) {
        return 1;
    } else {
        return 0;
    }
}

// Returns the state of the left mouse button
int mousePressed() {
    return GetAsyncKeyState(VK_LBUTTON);
}
