// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Custom libraries
#include "console_handler.h"
#include "tile_handler.h"
#include "game_handler.h"





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

    //clearConsole();

    extern int emptyBoardMatrix[5][5];

    toggleFullscreen();

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

    // --- TESTING ---

    printLogo(2);
    printCredits(38);

    printBackground(42);
    printGameBoard(42, P1BoardMatrix);
    printSideBoard(42, P1SideBoardMatrix);


    consolePointer(0, 40);


    printBank();

    printf("Press enter to continue...");
    getchar();

    //Prints the mouse position on the screen
    //printf("Mouse position: %d, %d\n", getMouseX(), getMouseY());


    return 0;
}