#include <stdio.h>
#include <stdlib.h>

#include "tile_handler.h"


// THIS IS WHERE THE TILES ARE STORED AND MANIPULATED


// --- TILE MANAGEMENT FUNCTIONS ---


// Resets the tile bank to 100 tiles
// There are 20 tiles of each color (0=none, 1=blue, 2=yellow, 3=red, 4=black, 5=turquoise)
void resetTileBank(TileBankStruct* tileBank)
{
    for (int i=0; i<NB_TILES_BANK; i++) {
        tileBank->tiles[i] = (i % 20) / 4 + 1;
    }
    tileBank->nbTilesRemaining = NB_TILES_BANK;
}

void resetFactory(TileFactoryStruct* tileFactory)
{
    for (int i=0; i<NB_MAX_TILES_IN_FACTORY; i++) {
        tileFactory->tiles[i] = 0;
    }
}

// Refills all factories with tile from the tile bank
void refillFactory(TileBankStruct* bank, TileFactoryStruct* tileFactory) {
    for (int j = 0; j < NB_MAX_TILES_IN_FACTORY; j++) {
            tileFactory->tiles[j] = pickTileFromBank(bank);
    }
}

// Picks the last tile from the tile bank
// returns the tile color
int pickTileFromBank(TileBankStruct* bank) {
    int tile = 0;
    if (bank->nbTilesRemaining > 0) {
        tile = bank->tiles[bank->nbTilesRemaining - 1];
        bank->nbTilesRemaining--;
    }
    return tile;
}


// Picks all tiles from a specific color in a specific factory
// Returns the number of tiles picked
int pickTilesFromFactory(TileFactoryStruct* factory, int color) {
    int pickedTiles = 0;

    for (int i = 0; i < NB_MAX_TILES_IN_FACTORY; i++) {
        if (factory->tiles[i] == color) {
            factory->tiles[i] = 0;
            pickedTiles++;
        }
    }

    return pickedTiles;
}


// Shuffles the tile bank
// swap elements randomly
void shuffleTileBank(TileBankStruct* bank) {
    for (int i = 0; i < NB_TILES_BANK; i++) {
        int j = rand() % NB_TILES_BANK;
        int temp = bank->tiles[i];
        bank->tiles[i] = bank->tiles[j];
        bank->tiles[j] = temp;
    }
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
    int ret = 0;

    if (board[row][4] == 0 || board[row][4] == tileColor) {
        ret = 1;
    }

    return ret;
}

// Places tiles at the end of the side board, if the row is full, the tile is placed in the overflow
// The first row has 1 tile, the second row has 2 tiles, the third row has 3 tiles, the fourth row has 4 tiles and the fifth row has 5 tiles
// a revoir NbTiles
// a revoir NbTiles
void placeTilesInSideBoard(PlayerStruct* player, int nbTiles, int tileColor, int row) {

    if (isValidSideBoardMove(player->sideBoardMatrix, tileColor, row)==1) {

        // Detects how many tiles of this color are already in the row
        int tilesInRow = 0;
        for (int i = 0; i < 5; i++) {
            if (player->sideBoardMatrix[row][i] == tileColor) {
                tilesInRow++;
            }
        }

        // Places the tiles in the row
        for (int i = 0; i < nbTiles; i++) {
            if (tilesInRow < 5) {
                player->boardMatrix[4-row][tilesInRow] = tileColor;
                tilesInRow++;
        } else {
                player->overflowTiles++;
            }
        }
    }
}

// Places a tile in the boardMatrix if it is a valid move
void placeMainBoardTile(int board[5][5], int tile, int row, int col) {
    if (isValidMainBoardMove(board, tile, row, col)==1) {
        board[row][col] = tile;
    }
}

