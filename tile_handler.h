#ifndef __TILE_HANDLER_H__
#define __TILE_HANDLER_H__

#include "game_handler.h"


// THIS IS WHERE THE TILES ARE STORED AND MANIPULATED



// --- PROTOTYPES ---



// Refills all factories with tile from the tile bank
void refillFactory();

// Resets the tile bank to 100 tiles
void resetTileBank(TileBankStruct* tileBank);

// Resets the center bank to 0 tiles
void resetCenterBank(TileBankStruct* centerBank);

// Shuffles the tile bank
void shuffleTileBank(TileBankStruct* tileBank);

// Picks a random tile from the tile bank
int pickTileFromBank(TileBankStruct* bank);

// Moves all tiles from a specific color in a factory in the given row and removes them
void moveTilesFromFactory(GameStruct* game, int factory, int tile, int row);

// Moves all tiles from a specific color in the center bank
void moveTilesFromCenterBank(GameStruct* game, int tile, int row);

// Moves a tile row from side board to main board
void moveRowToMain(GameStruct* game, int color, int row, const int board[5][5]);

// Places a tile in the sideBoardMatrix
void placeTileInSideBoard(PlayerStruct* player, int tileColor, int row);

// Tests if the selected tile row has the correct color or is empty
int isValidSideBoardMove(GameStruct* game, int factory, int tile, int row);

// Tests if the selected tile is a valid move
int isValidMainBoardMove(GameStruct* game, int tile, int row, int col);

// Tests if all factories are empty
int areFactoriesEmpty(GameStruct* game);

// Returns the amount of tiles of a specific color in the center bank
int getCenterBankTileCount(TileBankStruct centerBank, int color);



#endif // __TILE_HANDLER_H__