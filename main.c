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





// --- PROTOTYPES ---


// FOR TESTING PURPOSES ONLY, IS NOT USED IN THE GAME
void randomizeBoard(int *board[5][5]);





// --- FUNCTIONS ---


// Randomly generates a 5x5 matrix of numbers from 0 to 5
// FOR TESTING PURPOSES ONLY, IS NOT USED IN THE GAME
void randomizeBoard(int *board[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            *board[i][j] = rand() % 6;
        }
    }
}





// --- MAIN ---


int main(){

    // --- INITIALIZATION ---

    extern int emptyBoardMatrix[5][5];

    extern int consoleWidth;
    extern int consoleHeight;

    extern int termCharWidth;
    extern int termCharHeight;

    extern double leftMargin;
    extern double topMargin;

    toggleFullscreen();

    printf("Press enter to continue...");
    getchar();

    // Gets the console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    RECT windowRect;

    // Creates the empty board matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            emptyBoardMatrix[i][j] = (5-i+j) % 5 + 1;
        }
    }

    // Creates the empty side board matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i+j < 4) {
                emptySideBoardMatrix[i][j] = 0;
            }
            else {
                emptySideBoardMatrix[i][j] = 1;
            }
        }
    }

    // Random seed
    srand(time(NULL));

    // Resets the game
    resetGame();

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
    printGameBoard(P1BoardMatrix);
    printSideBoard(P1SideBoardMatrix);


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