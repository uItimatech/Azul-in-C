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

    // Sets the console title
    SetConsoleTitle("Azul");


    // Random seed
    srand(time(NULL));

    // Clears the console
    clearConsole();

    // Updates the console width
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        //consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        //consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        consoleWidth = GetSystemMetrics(SM_CXSCREEN)/termCharWidth;
        consoleHeight = GetSystemMetrics(SM_CYSCREEN)/termCharHeight;
    }

    // Menu buttons displacement
    int MBDx = consoleWidth/2-35;
    int MBDy = menuVerticalOffset+45;

    // Menu buttons
    menuButtons[0] = createButton(MBDx-2,  MBDy-2, strlen(menuButtonLabels[0])+2, 3, menuButtonLabels[0]);
    menuButtons[1] = createButton(MBDx+19, MBDy-2, strlen(menuButtonLabels[1])+2, 3, menuButtonLabels[1]);
    menuButtons[2] = createButton(MBDx+42, MBDy-2, strlen(menuButtonLabels[2])+2, 3, menuButtonLabels[2]);
    menuButtons[3] = createButton(MBDx+63, MBDy-2, strlen(menuButtonLabels[3])+2, 3, menuButtonLabels[3]);

    // Initializes the game
    GameStruct game;
    initGame(&game);
    
    // Resets the game (for testing purposes)
    //resetGame(&game);


    // Main loop

    while (1) {

        if (GetWindowRect(GetConsoleWindow(), &windowRect)) {
            leftMargin = round(windowRect.left);
            topMargin = round(windowRect.top);
        }

        if (DEBUG_MODE) {
        consolePointer(0, 40);
        consoleColor(15, 0);

        printf("Console size: %ld, %ld\n", consoleWidth, consoleHeight);
        printf("Console position: %1f, %1f\n", leftMargin, topMargin);
        printf("Mouse position: %1ld, %1ld\n", getTMousePos().x, getTMousePos().y);
        printf("Mouse board position: %ld, %ld", getMouseBoardTilePos().x, getMouseBoardTilePos().y);

        //consolePointer(getTMousePos().x, getTMousePos().y);
        //printf("X");
        }

        if (MAIN_MENU) {
            if (!DISPLAY_STATE) {clearConsole(); printMenu(); DISPLAY_STATE = 1;}

            // Play button
            if (isButtonPressed(menuButtons[0])) {
                resetGame(&game);
                IN_GAME = 1;
                MAIN_MENU = 0;
                DISPLAY_STATE = 0;
            }

            // Options button
            if (isButtonPressed(menuButtons[1])) {
                MAIN_MENU = 0;
                OPTIONS_MENU = 1;
                DISPLAY_STATE = 0;
            }

            // Rules button
            if (isButtonPressed(menuButtons[2])) {
                // Opens rules.pdf in the default application if it exists
                if (access("rules.pdf", F_OK) == 0) system("start rules.pdf"); 
            }

            // Quit button
            if (isButtonPressed(menuButtons[3])) {
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

        if (IN_GAME) {
            if (!DISPLAY_STATE) {clearConsole(); //printPlayerInterface(game.players[game.currentPlayer]); 
            DISPLAY_STATE = 1;}

            highlightTile(getMouseBoardTilePos().x, getMouseBoardTilePos().y);
        }

        if (END_MENU) {
            if (!DISPLAY_STATE) {clearConsole(); printEndMenu(); DISPLAY_STATE = 1;}}
    }

    return 0;
}