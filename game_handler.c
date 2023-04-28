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


// Initializes the game
void initGame(GameStruct* game)
{
    // Initializes the players
    for (int i = 0; i < PLAYER_COUNT; i++) {
        initPlayer(&game->players[i]);
    }

    // Initializes the tile factories
    for (int i = 0; i < FACTORY_COUNT; i++) {
        resetFactory(&game->tileFactories[i]);
    }

    // Initializes the tile bank
    resetTileBank(&game->bank);
    resetCenterBank(&game->centerBank);
    shuffleTileBank(&game->bank);

    // Initializes the player's turn
    game->currentPlayer = 0;
}

// Initializes the player's informations
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

void gameRound(PlayerStruct* player, TileFactoryStruct* factory){
    int i = 1;
    int p = i % PLAYER_COUNT;
    int checkEmpty = 1;

    //while factories are not empty
    while (checkEmpty != 0){

        //condition : factories not empty
        for(i=0 ; i<9 ; i++){
            for(int j=0 ; j<4 ; j++){
                if (factory[i].tiles[j] == 0){
                    checkEmpty = 0;
                    break;
                }
            }
        }

        printf("player score: %d", player->score);

        //round phase
        printf("At player %d to play :\nMove tiles from factory to side board",p);
        // moveTilesSideBoard(player[p] , factory[???????]);
        // J'ai besoin de la position de la souris pour savoir quelle factory prendre


        i++;
    }

}


// --- POINT MANAGEMENT FUNCTIONS ---

void resetGame(GameStruct* game)
{
    for (int i = 0; i < PLAYER_COUNT; i++) {
        initPlayer(&game->players[i]);
    }

    // Resets the tile factories
    for (int i = 0; i < FACTORY_COUNT; i++) {
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