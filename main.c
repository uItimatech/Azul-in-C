// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Custom libraries
#include "board_handler.h"




// --- GLOBAL VARIABLES & CHARACTER SPRITES ---

int gamemode = 0; // 0 = default, 1 = free tile placement NOT IMPLEMENTED YET
int playerCount = 4; // NOT IMPLEMENTED YET

int currentPlayer = 0;

// Creates 5x5 matrices of 0s
int P1BoardMatrix[5][5] = {0}, P2BoardMatrix[5][5] = {0}, P3BoardMatrix[5][5] = {0}, P4BoardMatrix[5][5] = {0};
int P1SideBoardMatrix[5][5] = {0}, P2SideBoardMatrix[5][5] = {0}, P3SideBoardMatrix[5][5] = {0}, P4SideBoardMatrix[5][5] = {0};

// Creates the scores
int scoreMatrix[4] = {0};

// Creates the tile bank
int tileBank[5] = {0};








// --- PROTOTYPES ---

void resetGame();

void randomizeBoard(int *board[5][5]);

int isValidMove(int board[5][5], int tile, int row, int col);

void placeTile(int *board[5][5], int tile, int row, int col);





// --- FUNCTIONS ---


void resetGame() {
    // Resets the board matrices
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            P1BoardMatrix[i][j] = 0;
            P2BoardMatrix[i][j] = 0;
            P3BoardMatrix[i][j] = 0;
            P4BoardMatrix[i][j] = 0;
        }
    }
    // Resets the side board matrices
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            P1SideBoardMatrix[i][j] = 0;
            P2SideBoardMatrix[i][j] = 0;
            P3SideBoardMatrix[i][j] = 0;
            P4SideBoardMatrix[i][j] = 0;
        }
    }

    // Resets the scores
    for (int i = 0; i < 4; i++) {
        scoreMatrix[i] = 0;
    }   
}


// Randomly generates a 5x5 matrix of numbers from 0 to 5
// FOR TESTING PURPOSES ONLY, IS NOT USED IN THE GAME
void randomizeBoard(int *board[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            *board[i][j] = rand() % 6;
        }
    }
}


// Tests if the selected tile is a valid move
// A valid moves means an empty tile and a correct id in the emptyBoardMatrix
int isValidMove(int board[5][5], int tile, int row, int col) {

    if (board[row][col] == 0 && emptyBoardMatrix[row][col] == tile) {
        return 1;
    }
    else {
        return 0;
    }
}


// Places a tile in the boardMatrix
void placeTile(int* board[5][5], int tile, int row, int col) {
    *board[row][col] = tile;
}





// --- MAIN ---


int main(){

    // --- INITIALIZATION ---

    //clearConsole();

    extern int emptyBoardMatrix[5][5];

    printLogo(5);
    printEmptyLines(3);
    printCredits();
    printEmptyLines(3);

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





    // --- TESTING ---

    //randomizeBoard(P1BoardMatrix);

    printPlayerBoard(P1BoardMatrix, P1SideBoardMatrix);
    
    return 0;
}




//TODO:
//- Current player and score indicator
//- Score calculator
//- Tile bank
//- Tile factories
//- End of game detection
//- End of game screen
//- Full game reset
//- Game 'menu' (start, options, read rules, exit) with game logo
//- Player interaction (select tile, select position, etc)
//- Table center bank
//- Player side boards fill restrictions
//- Player automatic negative score