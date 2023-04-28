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

    //tMousePos.x = (mousePos.x*0.883-gameWin.leftMargin) / gameWin.termCharWidth; DEBUG FOR SMALLER SCREENS
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
    if (boardState == 1 && tMousePos.x >= boardHorizontalOffset && tMousePos.x <= boardHorizontalOffset+boardHorizontalSize && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize) {
        boardMousePos.x = (tMousePos.x - boardHorizontalOffset - gameWin.leftMargin  -4)/8   +1;
        boardMousePos.y = (tMousePos.y - boardVerticalOffset   - gameWin.topMargin   -1)/4   +1;

    // Check if the mouse is in the main board
    } else if (boardState == 2 && tMousePos.x >= boardHorizontalOffset+boardHorizontalSize+4 && tMousePos.x <= boardHorizontalOffset+2*boardHorizontalSize+4 && tMousePos.y >= boardVerticalOffset+1 && tMousePos.y <= boardVerticalOffset+boardVerticalSize) {
        boardMousePos.x = (tMousePos.x - boardHorizontalOffset - gameWin.leftMargin    )/8   -5;
        boardMousePos.y = (tMousePos.y - boardVerticalOffset   - gameWin.topMargin   -1)/4   +1;

    // Check if the mouse is in the factories
    // There are 5 factories on 2 lines of tiles and 4 on the bottom
    // Each factory is 17 characters wide and 9 characters tall
    // Factories are spaced 1 character apart

    // Each factory has 4 tiles that are printed in a 2x2 matrix
    // Each tile is 7 characters wide and 3 characters tall
    // Tiles are spaced 1 character apart

    // There are 5 factories on the top line and 4 on the bottom
    // The bottom factories are offset by 8 characters to the right

    // The x value corresponds to the factory number (0 to 8)
    // The y value corresponds to the tile number (0 to 3)
    // The y value will correspond to this:
    // 0 1
    // 2 3

    // Check if the mouse if in the first factory line:
    } else if (boardState == 3 && tMousePos.x >= factoriesHorizontalOffset+1 && tMousePos.x <= factoriesHorizontalOffset+17*5+4 && tMousePos.y >= factoriesVerticalOffset && tMousePos.y <= factoriesVerticalOffset+7) {
        boardMousePos.x = (tMousePos.x - factoriesHorizontalOffset - gameWin.leftMargin  -1)/18;
        boardMousePos.y = (tMousePos.x - boardMousePos.x*18 - factoriesHorizontalOffset - gameWin.leftMargin  -1)/9 + round((tMousePos.y - factoriesVerticalOffset - gameWin.topMargin -2)/4)*2;

    // Check if the mouse if in the second factory line:
    } else if (boardState == 3 && tMousePos.x >= factoriesHorizontalOffset+9 && tMousePos.x <= factoriesHorizontalOffset+17*4+11 && tMousePos.y >= factoriesVerticalOffset+10 && tMousePos.y <= factoriesVerticalOffset+17) {
        boardMousePos.x = (tMousePos.x - factoriesHorizontalOffset - gameWin.leftMargin  -9)/18 +5;
        boardMousePos.y = (tMousePos.x - (boardMousePos.x-5)*18 - factoriesHorizontalOffset - gameWin.leftMargin  -9)/9 + round((tMousePos.y - factoriesVerticalOffset - gameWin.topMargin - 12)/4)*2;
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