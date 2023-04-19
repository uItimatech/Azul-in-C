// Standard libraries
#include <stdio.h>

#include "game_handler.h"
#include "tile_handler.h"


const int emptyBoardMatrix[5][5] = {
    { BLUE,         YELLOW,     RED,        BLACK,      TURQUOISE   },
    { TURQUOISE,    BLUE,       YELLOW,     RED,        BLACK       },
    { BLACK,        TURQUOISE,  BLUE,       YELLOW,     RED         },
    { RED,          BLACK,      TURQUOISE,  BLUE,       YELLOW      },
    { YELLOW,       RED,        BLACK,      TURQUOISE,  BLUE,       }
};

const int emptySideBoardMatrix[5][5] = {
    { 0, 0, 0, 0, 1},
    { 0, 0, 0, 1, 1},
    { 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1},
    { 1, 1, 1, 1, 1}
};

// THIS IS WHERE THE PLAYER POINTS ARE CALCULATED



// --- ROUND MANAGEMENT FUNCTIONS ---

//player chooses factory, tile and its color, then move the tiles of the factory into a row
void moveTilesSideBoard(PlayerStruct* player, TileFactoryStruct* factory, int color, int row)
{
    int numberofTilesPicked;

    numberofTilesPicked = pickTilesFromFactory(factory, color);

    placeTilesInSideBoard(player,
                          numberofTilesPicked,
                          color,
                          row);
}

//move tiles from side to main board, needs active row and coordinates of main board place
void moveTilesMainBoard(PlayerStruct* player, int color, int row, const int board[5][5]){
    int col;
    for (int i=0 ; i<5 ; i++){
        if (board[i][row] == color)
            col = i;
    }
    placeMainBoardTile(player,color,row,col);
}

void gameRound(PlayerStruct* player, TileFactoryStruct* factory){
    int i = 1;
    int p = i % NB_PLAYER;
    int checkEmpty = 1;



    //while factories are not empty
    while (checkEmpty != 0){

        //condition : factories not empty
        for(int i=0 ; i<9 ; i++){
            for(int j=0 ; j<4 ; j++){
                if (factory[i].tiles[j] == 0){
                    checkEmpty = 0;
                    break;
                }
            }
        }

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
            player->boardMatrix[i][j] = NONE;
            player->sideBoardMatrix[i][j] = NONE;
        }
    }
    player->score = 0;
    player->overflowTiles = 0;
}

