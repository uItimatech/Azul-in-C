// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

// Project headers
#include "console_handler.h"
#include "tile_handler.h"
#include "game_handler.h"
#include "input_handler.h"





// --- MAIN ---


int main(){

    // --- INITIALIZATION ---

    toggleFullscreen();

    // Gets the console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    RECT windowRect;

    gameWin = createGameWindow();

    // Sets the console title
    SetConsoleTitle(gameWin.Title);


    // Random seed
    srand(time(NULL));

    // Clears the console
    clearConsole();

    // Updates the console width
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        gameWin.consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 2;
        gameWin.consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top;
        //gameWin.consoleWidth = GetSystemMetrics(SM_CXSCREEN)/gameWin.termCharWidth*0.87;
        //gameWin.consoleHeight = GetSystemMetrics(SM_CYSCREEN)/gameWin.termCharHeight*0.87;
    }

    // Menu buttons displacement
    int MBDx = gameWin.consoleWidth/2;
    int MBDy = gameWin.menuVerticalOffset+41;

    // Menu buttons
    menuButtons[0] = createButton(MBDx-strlen(menuButtonLabels[0])/2, MBDy,   strlen(menuButtonLabels[0])+3, 3, menuButtonLabels[0]);
    menuButtons[1] = createButton(MBDx-strlen(menuButtonLabels[1])/2, MBDy+4, strlen(menuButtonLabels[1])+3, 3, menuButtonLabels[1]);
    menuButtons[2] = createButton(MBDx-strlen(menuButtonLabels[2])/2, MBDy+8, strlen(menuButtonLabels[2])+3, 3, menuButtonLabels[2]);

    // Initializes the game
    GameStruct game;
    initGame(&game);


    gameWin.boardState = 3; // TESTING ONLY



    // Main loop
    while (1) {

        if (GetWindowRect(GetConsoleWindow(), &windowRect)) {
            gameWin.leftMargin = round(windowRect.left);
            gameWin.topMargin = round(windowRect.top);
        }

        if (gameWin.DEBUG_MODE) {
            consoleColor(15, 0);

            // Fills the first line with "X"
            for (int i = 0; i < gameWin.consoleWidth-1; i++) {
                consolePointer(i, 0);
                printf("X");
            }

            consolePointer(0, 20);
            printf("Console size: %d, %d        \n", gameWin.consoleWidth, gameWin.consoleHeight);
            printf("Console position: %1f, %1f      \n", gameWin.leftMargin, gameWin.topMargin);
            printf("Mouse position: %1ld, %1ld      \n", getTMousePos().x, getTMousePos().y);
            printf("Mouse board position: %ld, %ld      ", getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y);

            //consolePointer(getTMousePos().x, getTMousePos().y);
            //printf("X");
        }

        if (gameWin.MAIN_MENU) {
            if (!gameWin.DISPLAY_STATE) {clearConsole(); printMenu(); gameWin.DISPLAY_STATE = 1;}

            // Play button
            if (isButtonPressed(menuButtons[0])) {
                resetGame(&game);
                gameWin.IN_GAME = 1;
                gameWin.MAIN_MENU = 0;
                gameWin.DISPLAY_STATE = 0;
            }

            // Rules button
            if (isButtonPressed(menuButtons[1])) {
                // Opens rules.pdf in the default application if it exists
                if (access("rules.pdf", F_OK) == 0) system("start rules.pdf"); 
            }

            // Quit button
            if (isButtonPressed(menuButtons[2])) {
                return 0;
            }

            // Highlighting
            int buttonCollided = 0;
            for (int i = 0; i < 4; i++) {
                if (isMouseInRect(menuButtons[i].x, menuButtons[i].y, menuButtons[i].width, menuButtons[i].height)) {
                    highlightButton(menuButtons[i]);
                    buttonCollided = 1;
                }
            }
            if (!buttonCollided) highlightButton(createButton(-1, -1, -1, -1, ""));
        }

        if (gameWin.IN_GAME) {
            if (!gameWin.DISPLAY_STATE) {
                clearConsole(); 
                gameWin.DISPLAY_STATE = 1;
                printFactories(game.tileFactories);
                printPlayerInterface(game);
            }

            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);
        }

        if (gameWin.END_MENU) {
            if (!gameWin.DISPLAY_STATE) {clearConsole(); printEndMenu(); gameWin.DISPLAY_STATE = 1;}}
    
        // Exits if the user presses ESC
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return 0;
        }
    }
    return 0;
}