// Standard libraries
#include <stdio.h>

#include "game_handler.h"
#include "tile_handler.h"


// THIS IS WHERE THE PLAYER POINTS ARE CALCULATED


const int emptyBoardMatrix[5][5] = {
    { 1, 2, 3, 4, 5},
    { 5, 1, 2, 3, 4},
    { 4, 5, 1, 2, 3},
    { 3, 4, 5, 1, 2},
    { 2, 3, 4, 5, 1}
};

const int emptySideBoardMatrix[5][5] = {
    { 0, 0, 0, 0, 1},
    { 0, 0, 0, 1, 1},
    { 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1},
    { 1, 1, 1, 1, 1}
};


// --- ROUND MANAGEMENT FUNCTIONS ---

//player chooses factory, tile and its color, then move the tiles of the factory into a row
void moveTiles(PlayerStruct* player, TileFactoryStruct* factory, int color, int row)
{
    int numberofTilesPicked;

    numberofTilesPicked = pickTilesFromFactory(factory, color);

    placeTilesInSideBoard(player,
                        numberofTilesPicked,
                        color,
                        row);
}



// --- POINT MANAGEMENT FUNCTIONS ---


void resetGame(GameStruct* game)
{
    for (int i=0; i<NB_PLAYER; i++) {
        initPlayer(&game->players[i]);
    }

    // Resets the tile factories
    for (int i = 0; i < NB_FACTORY; i++) {
        resetFactory(&game->tileFactories[i]);
    }

    // Resets the tile bank
    resetTileBank(&game->bank);
    shuffleTileBank(&game->bank);
}

// Calculates the negative points for the player based on the number of overflowing tiles
// (1-2: -1, 3-5: -2, 5-infinity: -3)
int negativePoints(int overflowingTiles){
    int points = 0;

    if (overflowingTiles >= 1 && overflowingTiles <= 2) {
        points = -1;
    } else if (overflowingTiles >= 3 && overflowingTiles <= 5) {
        points = -2;
    } else if (overflowingTiles >= 6) {
        points = -3;
    }

    return points;
}

// init one player
void initPlayer(PlayerStruct* player)
{
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            player->boardMatrix[i][j] = 0;
            player->sideBoardMatrix[i][j] = 0;
        }
    }
    player->score = 0;
    player->overflowTiles = 0;
}

