#ifndef __TILE_HANDLER_H__
#define __TILE_HANDLER_H__

#include "game_handler.h"


// THIS IS WHERE THE TILES ARE STORED AND MANIPULATED



// --- PROTOTYPES ---


// Resets a factory
void resetFactory(TileFactoryStruct* tileFactory);

// Resets the tile bank to 100 tiles
void resetTileBank(TileBankStruct* tileBank);

// Shuffles the tile bank
void shuffleTileBank(TileBankStruct* tileBank);

// Picks a random tile from the tile bank
int pickTileFromBank(TileBankStruct* bank);

// Picks all tiles from a specific color in a specific factory
// Returns the number of tiles picked and their color
int pickTilesFromFactory(TileFactoryStruct* factory, int color);

// Tests if the selected tile is a valid move
int isValidMainBoardMove(int board[5][5], int tile, int row, int col);

// Tests if the selected tile row has the correct color or is empty
int isValidSideBoardMove(int board[5][5], int tileColor, int row);

// Places a tile in the boardMatrix
void placeMainBoardTile(int board[5][5], int tile, int row, int col);

// Places a tile in the sideBoardMatrix
void placeTilesInSideBoard(PlayerStruct* player, int nbTiles, int tileColor, int row);



#endif // __TILE_HANDLER_H__