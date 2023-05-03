#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "input_handler.h"
#include "console_handler.h"


// THIS IS WHERE INPUTS ARE PROCESSED



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
    return mousePos;
}


// Returns mouse coordinates on the terminal as a POINT struct
POINT getTMousePos() {

    POINT mousePos = getMousePos();

    POINT tMousePos;

    //tMousePos.x = (mousePos.x*0.883-gameWin.leftMargin) / gameWin.termCharWidth; //DEBUG FOR SMALLER SCREENS
    //tMousePos.y = (mousePos.y*0.883-gameWin.topMargin)  / gameWin.termCharHeight;
    tMousePos.x = (mousePos.x-gameWin.leftMargin) / gameWin.termCharWidth;
    tMousePos.y = (mousePos.y-gameWin.topMargin)  / gameWin.termCharHeight;

    return tMousePos;
}


// Returns mouse coordinates on the game boards as a POINT struct
// Returns board coordinates of the tiles or (-1, -1) if the mouse is outside the boards
// boardState is used to determine which board to return the coordinates for
// 1 for the side board, 2 for the main board, 3 for the factories
POINT getMouseBoardTilePos(int boardState) {

    POINT tMousePos = getTMousePos();
    POINT boardMousePos;

    int boardHorizontalOffset = gameWin.consoleWidth/2 - 45; // Horizontal offset of the left side of the left board from the left side of the console
    int boardHorizontalSize = 41; // Width of each board in characters

    int boardVerticalOffset = gameWin.boardVerticalOffset;
    int boardVerticalSize = 21; // Height of each board in characters

    int factoriesHorizontalOffset = gameWin.consoleWidth/2 - 45; // Horizontal offset of the left side of the left factory from the left side of the console
    int factoriesVerticalOffset = 2;
    // Note: the vertical offset is already defined in the console_handler.h file


    // Check if the mouse is in the side board
    if (boardState == 1 && tMousePos.x >= boardHorizontalOffset && tMousePos.x <= boardHorizontalOffset+boardHorizontalSize && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize-1) {
        boardMousePos.x = (tMousePos.x - boardHorizontalOffset - gameWin.leftMargin -4)/8   +1;
        boardMousePos.y = (tMousePos.y - boardVerticalOffset   - gameWin.topMargin  -1)/4   +1;

    // Check if the mouse is in the main board (Not used currently in a game but still useful for debugging)
    } else if (boardState == 2 && tMousePos.x >= boardHorizontalOffset+boardHorizontalSize+4 && tMousePos.x <= boardHorizontalOffset+2*boardHorizontalSize+4 && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize) {
        boardMousePos.x = (tMousePos.x - boardHorizontalOffset - gameWin.leftMargin   )/8   -5;
        boardMousePos.y = (tMousePos.y - boardVerticalOffset   - gameWin.topMargin  -1)/4   +1;

    // Check if the mouse is in the first factory line:
    } else if (boardState == 3 && tMousePos.x >= factoriesHorizontalOffset+1 && tMousePos.x <= factoriesHorizontalOffset+17*5+4 && tMousePos.y >= factoriesVerticalOffset+1 && tMousePos.y <= factoriesVerticalOffset+7) {
        boardMousePos.x = (tMousePos.x - factoriesHorizontalOffset - gameWin.leftMargin -1)/18;
        boardMousePos.y = (tMousePos.x - boardMousePos.x*18 - factoriesHorizontalOffset - gameWin.leftMargin  -1)/9 + round((tMousePos.y - factoriesVerticalOffset - gameWin.topMargin -2)/4)*2;

    // Check if the mouse is in the second factory line:
    } else if (boardState == 3 && tMousePos.x >= factoriesHorizontalOffset+9 && tMousePos.x <= factoriesHorizontalOffset+17*4+11 && tMousePos.y >= factoriesVerticalOffset+11 && tMousePos.y <= factoriesVerticalOffset+17) {
        boardMousePos.x = (tMousePos.x - factoriesHorizontalOffset - gameWin.leftMargin -9)/18 +5;
        boardMousePos.y = (tMousePos.x - (boardMousePos.x-5)*18 - factoriesHorizontalOffset - gameWin.leftMargin  -9)/9 + round((tMousePos.y - factoriesVerticalOffset - gameWin.topMargin - 12)/4)*2;

    // Check if the mouse is in the center bank:
    } else if (boardState == 3 && tMousePos.x >= gameWin.consoleWidth/2-57 && tMousePos.x <= gameWin.consoleWidth/2-49 && tMousePos.y >= gameWin.boardVerticalOffset+1 && tMousePos.y <= gameWin.boardVerticalOffset+5*4) {
        boardMousePos.x = 9;
        boardMousePos.y = (tMousePos.y - gameWin.boardVerticalOffset - gameWin.topMargin - 1)/4+1;
    } else {
        boardMousePos.x = -1;
        boardMousePos.y = -1;
    }

    return boardMousePos;
}


// Returns 1 if the mouse is in the specified rectangle, 0 otherwises
int isMouseInRect(int x, int y, int width, int height){
    POINT tMousePos = getTMousePos();

    if (tMousePos.x >= x && tMousePos.x <= x+width && tMousePos.y >= y && tMousePos.y <= y+height) {
        return 1;
    } else {
        return 0;
    }
}


// Returns the state of the left mouse button (CURRENTLY UNUSED)
int mousePressed() {
    return GetAsyncKeyState(VK_LBUTTON);
}
