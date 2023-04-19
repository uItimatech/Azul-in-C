// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Custom libraries
#include "console_handler.h"
#include "tile_handler.h"
#include "game_handler.h"
#include "input_handler.h"



// --- MAIN ---


int main(){

    // --- INITIALIZATION ---
    GameStruct game;

    toggleFullscreen();

    printf("Press enter to continue...");
    getchar();

    // Gets the console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    RECT windowRect;


    // Random seed
    srand(time(NULL));

    // Resets the game
    resetGame(&game);

    // Clears the console
    clearConsole();

    // Updates the console width
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }





    // --- TESTING ---

    printLogo(2);
    printCredits(38);

    printBackground();
    printGameBoard(game.players[0].boardMatrix);
    printSideBoard(game.players[0].sideBoardMatrix);


    consolePointer(0, 40);



    //printf("Press enter to continue...");
    //getchar();

    //Prints the mouse position on the screen
    /*int Mx = getTMousePos().x;
    int My = getTMousePos().y;
    consolePointer(Mx, My);
    printf("Selected tile: %ld, %ld", getMouseBoardTilePos().x, getMouseBoardTilePos().y);
    printf("Press enter to continue...");*/



    while (1) {
        highlightTile(getMouseBoardTilePos().x, getMouseBoardTilePos().y);
        //highlightTile(-1, -1);
        consolePointer(0, 40);
        consoleColor(15, 0);
        printf("Window position: %lf, %lf", leftMargin, topMargin);

        if (GetWindowRect(GetConsoleWindow(), &windowRect)) {
            leftMargin = round(windowRect.left);
            topMargin = round(windowRect.top);
        }
    }

    return 0;
}
