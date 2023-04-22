#include <windows.h>
#include <stdio.h>
#include <math.h>

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

    tMousePos.x = mousePos.x / termCharWidth - 105;
    tMousePos.y = mousePos.y / termCharHeight;

    return tMousePos;
}

// Returns mouse coordinates on the game boards as a POINT struct
// Returns coordinates between (0, 0) and (10, 5) or (-1, -1) if the mouse is outside the boards
// Side board corners are (65,43) and (105,63) (by default; upper left and lower right)
// Main board corners are (109,43) and (149,63) (by default; upper left and lower right)
POINT getMouseBoardTilePos() {
    POINT tMousePos = getTMousePos();
    POINT boardMousePos;

    int boardHorizontalOffset = consoleWidth/2 - 45; // Horizontal offset of the left side of the left board from the left side of the console
    int boardHorizontalSize = 21; // Width of each board in characters
    int boardVerticalSize = 21; // Height of each board in characters
    // Note: the vertical offset is already defined in the console_handler.h file

    if (tMousePos.x >= boardHorizontalOffset && tMousePos.x <= boardHorizontalOffset+boardHorizontalSize && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize) {
        boardMousePos.x = (tMousePos.x - 172)/8;
        boardMousePos.y = (tMousePos.y - 43)/4;
    } else if (tMousePos.x >= 9999 && tMousePos.x <= 9999 && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize) {
        boardMousePos.x = (tMousePos.x - 216)/8;
        boardMousePos.y = (tMousePos.y - 43)/4;
    } else {
        boardMousePos.x = -1;
        boardMousePos.y = -1;
    }

    return boardMousePos;
}

// Returns 1 if the mouse is in the specified rectangle, 0 otherwise
int isCursorInRect(int x, int y, int width, int height){
    POINT tMousePos = getTMousePos();

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
