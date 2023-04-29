#include <stdio.h>
#include <stdlib.h>

#include "tile_handler.h"


// THIS IS WHERE THE TILES ARE STORED AND MANIPULATED


// --- TILE MANAGEMENT FUNCTIONS ---


// Resets the tile bank to 100 tiles
// There are 20 tiles of each color (0=none, 1=blue, 2=yellow, 3=red, 4=black, 5=turquoise)
void resetTileBank(TileBankStruct* tileBank)
{
    for (int i=0; i<BANK_TILE_COUNT; i++) {
        tileBank->tiles[i] = (i % 20) / 4 + 1;
    }
    tileBank->nbTilesRemaining = BANK_TILE_COUNT;
}


// Resets the center bank to 0 tiles
void resetCenterBank(TileBankStruct* centerBank)
{
    for (int i=0; i<BANK_TILE_COUNT; i++) {
        centerBank->tiles[i] = 0;
    }
    centerBank->nbTilesRemaining = 0;
}


// Refills all factories with tile from the tile bank
void refillFactory(TileFactoryStruct* tileFactory, TileBankStruct* bank) {
    for (int j = 0; j < FACTORY_TILE_COUNT; j++) {
        tileFactory->tiles[j] = pickTileFromBank(bank);
    }
}


// Shuffles the tile bank (swap elements randomly)
void shuffleTileBank(TileBankStruct* bank) {
    for (int i = 0; i < BANK_TILE_COUNT; i++) {
        int j = rand() % BANK_TILE_COUNT;
        int temp = bank->tiles[i];
        bank->tiles[i] = bank->tiles[j];
        bank->tiles[j] = temp;
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


// Moves all tiles from a specific color in a specific factory
void moveTilesFromFactory(GameStruct* game, int factory, int tile, int row) {

    if (factory == 9) {
        moveTilesFromCenterBank(game, tile, row);
        return;
    }

    int color = game->tileFactories[factory].tiles[tile];

    for (int i = 0; i < FACTORY_TILE_COUNT; i++) {
        if (game->tileFactories[factory].tiles[i] == color) {
            placeTileInSideBoard(&game->players[game->currentPlayer], color, row);
        } else {
            game->centerBank.tiles[game->centerBank.nbTilesRemaining] = game->tileFactories[factory].tiles[i];
            game->centerBank.nbTilesRemaining++;
        }
        game->tileFactories[factory].tiles[i] = 0;
    }
}


// Moves all tiles from a specific color in the center bank
void moveTilesFromCenterBank(GameStruct* game, int tile, int row) {

    // Moves all tiles of the given color
    for (int i = 0; i < game->centerBank.nbTilesRemaining; i++) {
        game->centerBank.tiles[i] = 0;
        game->centerBank.nbTilesRemaining--;
        placeTileInSideBoard(&game->players[game->currentPlayer], tile, row);
    }

    // Offsets the remaining tiles to the left when there are empty spaces
    for (int i = 0; i < game->centerBank.nbTilesRemaining; i++) {
        if (game->centerBank.tiles[i] == 0) {
            for (int j = i; j < game->centerBank.nbTilesRemaining; j++) {
                game->centerBank.tiles[j] = game->centerBank.tiles[j + 1];
            }
            i--;
        }
    }
}


// Moves a tile row from side board to main board
void moveRowToMain(GameStruct* game, int color, int row, const int board[5][5]){
    int col;

    for (int i=0 ; i<5 ; i++){
        if (board[i][row] == color)
            col = i;
    }

    game->players[game->currentPlayer].boardMatrix[row][col] = color;
}


// Places a tile at the end of the side board, if the row is full, the tile is placed in the overflow
void placeTileInSideBoard(PlayerStruct* player, int tileColor, int row) {

    // Detects how many tiles of this color are already in the row
    int tilesInRow = 0;

    /*while (player->sideBoardMatrix[row][4-tilesInRow] == tileColor && tilesInRow<5) tilesInRow++;

    // Places the tile in the row
    if (tilesInRow < 5) {
        player->boardMatrix[row][4-tilesInRow] = tileColor;
        tilesInRow++;
    } else {
        player->overflowTiles++;
    }*/

    // Calculates the number of tiles in the row
    for (int i = 0; i < 5; i++) {
        if (player->sideBoardMatrix[row][i] == tileColor) {
            tilesInRow++;
        }
    }

    // If the row is full, the tile is placed in the overflow
    if (tilesInRow == row+1) {
        player->overflowTiles++;
    } else {
        // Places the tile at the end of the row (to the left)
        player->sideBoardMatrix[row][4-tilesInRow] = tileColor;
    }
}


// Tests if the selected tile row has the correct color, is not full or is empty
int isValidSideBoardMove(GameStruct* game, int factory, int tile, int row) {

    int firstRowTile = game->players[game->currentPlayer].sideBoardMatrix[row][4];

    if (factory==9 && (firstRowTile == 0 || firstRowTile == game->centerBank.tiles[tile]) && (game->players[game->currentPlayer].sideBoardMatrix[row][4-row] == 0)) {
        return 1;
    } else if ((firstRowTile == 0 || firstRowTile == game->tileFactories[factory].tiles[tile]) && (game->players[game->currentPlayer].sideBoardMatrix[row][4-row] == 0)) {
        return 1;
    }

    return 0;
}


// Tests if the selected tile is a valid move
// A valid moves means an empty tile and a correct id in the emptyBoardMatrix
int isValidMainBoardMove(GameStruct* game, int tile, int row, int col) {

    if (game->players[game->currentPlayer].boardMatrix[row][col] == 0 && emptyBoardMatrix[row][col] == tile) {
        return 1;
    }
    return 0;
}


// Tests if all factories are empty
int areFactoriesEmpty(GameStruct* game) {
    for (int i = 0; i < FACTORY_COUNT; i++) {
        for (int j = 0; j < FACTORY_TILE_COUNT; j++) {
            if (game->tileFactories[i].tiles[j] != 0) {
                return 0;
            }
        }
    }
    return 1;
}


// Returns the amount of tiles of a specific color in the center bank
int getCenterBankTileCount(TileBankStruct centerBank, int color){
    int count = 0;

    for (int i=0 ; i<centerBank.nbTilesRemaining ; i++){
        if (centerBank.tiles[i] == color)
            count++;
    }

    return count;
}