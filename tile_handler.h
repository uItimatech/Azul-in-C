#include <stdio.h>
#include <stdlib.h>


// THIS IS WHERE THE TILES ARE STORED


// Creates 5x5 matrices of 0s for each player's board
int P1BoardMatrix[5][5] = {0}, P2BoardMatrix[5][5] = {0}, P3BoardMatrix[5][5] = {0}, P4BoardMatrix[5][5] = {0};

// Creates 5x5 matrices of 0s for each player's side board
int P1SideBoardMatrix[5][5] = {0}, P2SideBoardMatrix[5][5] = {0}, P3SideBoardMatrix[5][5] = {0}, P4SideBoardMatrix[5][5] = {0};

// Creates 4 variable for each player's overflow tiles that will count as negative points later

// Creates the tile bank
int tileBank[100] = {0};

int remainingBankTiles = 100;

// Creates the 9 tile factories
int tileFactory[9][4] = {0};





// --- PROTOTYPES ---

// Resets all factories
void resetFactories();

// Resets the tile bank to 100 tiles
void refillBank();

// Shuffles the tile bank
void shuffleTileBank();

// Picks a random tile from the tile bank
int pickTileFromBank();

// Tests if the selected tile is a valid move
int isValidMove(int board[5][5], int tile, int row, int col);

// Places a tile in the boardMatrix
void placeTile(int *board[5][5], int tile, int row, int col);





// --- TILE MANAGEMENT FUNCTIONS ---


// Resets all factories
void resetFactories() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            tileFactory[i][j] = 0;
        }
    }
}

// Refills all factories with tile from the tile bank
void refillFactories() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 4; j++) {
            tileFactory[i][j] = pickTileFromBank();
        }
    }
}

// Resets the tile bank to 100 tiles7
// There are 20 tiles of each color (0=none, 1=blue, 2=yellow, 3=red, 4=black, 5=turquoise)
void refillTileBank() {
    for (int i = 0; i < 100; i++) {
        tileBank[i] = (i % 20) / 4 + 1;
    }
    remainingBankTiles = 100;
}

// Shuffles the tile bank
void shuffleTileBank() {
    for (int i = 0; i < 100; i++) {
        int j = rand() % 100;
        int temp = tileBank[i];
        tileBank[i] = tileBank[j];
        tileBank[j] = temp;
    }
}

// Picks the last tile from the tile bank
int pickTileFromBank() {
    int tile = 0;
    if (remainingBankTiles > 0) {
        tile = tileBank[remainingBankTiles - 1];
        remainingBankTiles--;
    }
    return tile;
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