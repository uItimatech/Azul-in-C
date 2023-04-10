#include <stdio.h>
#include <stdlib.h>


// THIS IS WHERE THE TILES ARE STORED


// Creates 5x5 matrices of 0s for each player's board
int P1BoardMatrix[5][5] = {0}, P2BoardMatrix[5][5] = {0}, P3BoardMatrix[5][5] = {0}, P4BoardMatrix[5][5] = {0};

// Creates 5x5 matrices of 0s for each player's side board
int P1SideBoardMatrix[5][5] = {0}, P2SideBoardMatrix[5][5] = {0}, P3SideBoardMatrix[5][5] = {0}, P4SideBoardMatrix[5][5] = {0};

// Creates 4 variable for each player's overflow tiles that will count as negative points later
int P1OverflowTiles = 0, P2OverflowTiles = 0, P3OverflowTiles = 0, P4OverflowTiles = 0;

// Creates a 5x5 layout of the empty board and empty side board
int emptyBoardMatrix[5][5] = {0};
int emptySideBoardMatrix[5][5] = {0};

// Creates the tile bank
int tileBank[100] = {0};

int remainingBankTiles = 100;

// Creates the 9 tile factories
int tileFactory[9][4] = {0};





// --- PROTOTYPES ---

// Resets all factories
void resetFactories();

// Resets the tile bank to 100 tiles
void resetBank();

// Shuffles the tile bank
void shuffleTileBank();

// Picks a random tile from the tile bank
int pickTileFromBank();

// Picks all tiles from a specific color in a specific factory
// Returns the number of tiles picked and their color
int pickTilesFromFactory(int factory, int color);

// Tests if the selected tile is a valid move
int isValidMainBoardMove(int board[5][5], int tile, int row, int col);

// Tests if the selected tile row has the correct color or is empty
int isValidSideBoardMove(int board[5][5], int tileColor, int row, int col);

// Places a tile in the boardMatrix
void placeMainBoardTile(int *board[5][5], int tile, int row, int col);

// Places a tile in the sideBoardMatrix
void placeTilesInSideBoard(int* board[5][5], int* overflow, int tileAmount, int tileColor, int row);





// --- TILE MANAGEMENT FUNCTIONS ---


// Resets all factories
void resetFactories() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 4; j++) {
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

// Picks all tiles from a specific color in a specific factory
// Returns the number of tiles picked
int pickTilesFromFactory(int factory, int color) {
    int pickedTiles = 0;
    
    for (int i = 0; i < 4; i++) {
        if (tileFactory[factory][i] == color) {
            tileFactory[factory][i] = 0;
            pickedTiles++;
        }
    }

    return pickedTiles;
}

// Resets the tile bank to 100 tiles
// There are 20 tiles of each color (0=none, 1=blue, 2=yellow, 3=red, 4=black, 5=turquoise)
void resetTileBank() {
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
int isValidMainBoardMove(int board[5][5], int tile, int row, int col) {

    if (board[row][col] == 0 && emptyBoardMatrix[row][col] == tile) {
        return 1;
    }
    else {
        return 0;
    }
}

// Tests if the selected tile row has the correct color or is empty
int isValidSideBoardMove(int board[5][5], int tileColor, int row) {

    if (board[row][4] == 0 || board[row][4] == tileColor) {
        return 1;
    }
    else {
        return 0;
    }
}

// Places tiles at the end of the side board, if the row is full, the tile is placed in the overflow
// The first row has 1 tile, the second row has 2 tiles, the third row has 3 tiles, the fourth row has 4 tiles and the fifth row has 5 tiles
void placeTilesInSideBoard(int* board[5][5], int* overflow, int tileAmount, int tileColor, int row) {
    
    if (isValidSideBoardMove(board, tileColor, row)==1) {
        
        // Detects how many tiles of this color are already in the row
        int tilesInRow = 0;
        for (int i = 0; i < 4; i++) {
            if (board[row][i] == tileColor) {
                tilesInRow++;
            }
        }

        // Places the tiles in the row
        for (int i = 0; i < tileAmount; i++) {
            if (tilesInRow < 5) {
                *board[4-row][tilesInRow] = tileColor;
                tilesInRow++;
            }
            else {
                *overflow++;
            }
        }

    }
}

// Places a tile in the boardMatrix if it is a valid move
void placeMainBoardTile(int* board[5][5], int tile, int row, int col) {
    if (isValidMainBoardMove(*board, tile, row, col)==1) {
        *board[row][col] = tile;
    }
}

