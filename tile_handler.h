#ifndef __TILE_HANDLER_H__
#define __TILE_HANDLER_H__


// THIS IS WHERE THE TILES ARE STORED AND MANIPULATED


// Structure for a player containing board and sideBoard Matrix, score and number of overflowTiles
struct playerStruct {
    int boardMatrix[5][5];
    int sideBoardMatrix[5][5];
    int overflowTiles;
    int score;
};

extern struct playerStruct players[4];


// Creates 5x5 matrices of 0s for each player's board
extern int P1BoardMatrix[5][5];
extern int P2BoardMatrix[5][5];
extern int P3BoardMatrix[5][5];
extern int P4BoardMatrix[5][5];

// Creates 5x5 matrices of 0s for each player's side board
extern int P1SideBoardMatrix[5][5];
extern int P2SideBoardMatrix[5][5];
extern int P3SideBoardMatrix[5][5];
extern int P4SideBoardMatrix[5][5];

// Creates 4 variable for each player's overflow tiles that will count as negative points later
extern int P1OverflowTiles;
extern int P2OverflowTiles;
extern int P3OverflowTiles;
extern int P4OverflowTiles;

// Creates a 5x5 layout of the empty board and empty side board
extern int emptyBoardMatrix[5][5];
extern int emptySideBoardMatrix[5][5];

// Creates the tile bank
extern int tileBank[100];

extern int remainingBankTiles;

// Creates the 9 tile factories
extern int tileFactory[9][4];





// --- PROTOTYPES ---

// Resets all factories
void resetFactories();

// Resets the tile bank to 100 tiles
void resetTileBank();

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
int isValidSideBoardMove(int board[5][5], int tileColor, int row);

// Places a tile in the boardMatrix
void placeMainBoardTile(int *board[5][5], int tile, int row, int col);

// Places a tile in the sideBoardMatrix
void placeTilesInSideBoard(int* board[5][5], int* overflow, int tileAmount, int tileColor, int row);

#endif // __TILE_HANDLER_H__

