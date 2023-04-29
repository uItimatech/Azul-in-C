// Standard libraries
#include <stdio.h>

#include "game_handler.h"
#include "tile_handler.h"
#include "console_handler.h"
#include "input_handler.h"


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
void initGame(GameStruct* game) {

    // Initializes the tile bank
    resetTileBank(&game->bank);
    resetCenterBank(&game->centerBank);
    shuffleTileBank(&game->bank);

    // Initializes the tile factories
    for (int i = 0; i < FACTORY_COUNT; i++) {
        refillFactory(&game->tileFactories[i], &game->bank);
    }

    // Initializes the players
    for (int i = 0; i < PLAYER_COUNT; i++) {
        initPlayer(&game->players[i]);
    }


    // Initializes the player's turn
    game->currentPlayer = 0;
    game->priorityPlayer = 0;
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

// Starts a game round
void gameRound(GameStruct* game) {

    game->currentPlayer = game->priorityPlayer;

    // While all factories are not empty
    while (!areFactoriesEmpty(game)){

        printGameUI(game);




        // Let the player choose tiles from a factory or the center
        gameWin.boardState = 3;
        printGameHint();

        // Waits for the player to choose a factory or the center
        int validFactMove = 0;
        while (mousePressed()==0 || validFactMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);

            // Checks if the player has chosen a valid factory
            validFactMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1;

            // If the player has chosen a factory, checks if it is the center bank
            if (validFactMove && getMouseBoardTilePos(gameWin.boardState).x == 9) {
                validFactMove = getCenterBankTileCount(game->centerBank, getMouseBoardTilePos(gameWin.boardState).y) > 0;

            // If the player has chosen a factory, checks if it is not empty
            } else if (validFactMove) {
                validFactMove = game->tileFactories[getMouseBoardTilePos(gameWin.boardState).x].tiles[getMouseBoardTilePos(gameWin.boardState).y] != 0;
            }
        }

        int selectedFactory = getMouseBoardTilePos(gameWin.boardState).x;
        int selectedTile = getMouseBoardTilePos(gameWin.boardState).y;
        int selectedTileColor = game->tileFactories[selectedFactory].tiles[selectedTile]; // Only used for debug





        // Let the player choose a sideboard row
        gameWin.boardState = 1;
        printGameHint();

        // Waits for the player to choose a valid sideboard row
        int validSideMove = 0;
        while (mousePressed()==0 || validSideMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);

            // Checks if the player has chosen a valid sideboard row
            validSideMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1 && isValidSideBoardMove(game, selectedFactory, selectedTile, getMouseBoardTilePos(gameWin.boardState).y-1);
        }

        // Moves the tiles from the factory or the center to the sideboard
        moveTilesFromFactory(game, selectedFactory, selectedTile, getMouseBoardTilePos(gameWin.boardState).y-1);

        int selectedSideRow = getMouseBoardTilePos(gameWin.boardState).y-1; // Only used for debug

        gameWin.boardState = 4;
        printGameUI(game);
        printGameHint();

        // DEBUG
        if (gameWin.DEBUG_MODE) {
            consolePointer(0,0);
            printf("Selected factory: %d\n", selectedFactory);
            printf("Selected tile: %d\n", selectedTile);
            printf("selected tile color: %d\n", selectedTileColor);
            printf("Selected sideboard row: %d\n", selectedSideRow);
        }





        // Waits for mouse click to switch to the next player
        while (mousePressed()!=0);
        while (mousePressed()==0);




        // Changes the current player
        game->currentPlayer = (game->currentPlayer + 1) % (PLAYER_COUNT);
    }
}


// Tests if the game is over (one player has a full row)
int isGameOver(GameStruct game) {
    int gameOver = 0;

    for (int i = 0; i < PLAYER_COUNT; i++) {
        for (int j = 0; j < 5; j++) {

            gameOver = 1;

            for (int k = 0; k < 5; k++){
                if (game.players[i].boardMatrix[j][k] == 0) {
                    gameOver = 0;
                }
            }

            if (gameOver == 1) {
                return 1;
            }
        }
    }
    return 0;
}


// --- POINT MANAGEMENT FUNCTIONS ---


// Calculates the negative points for the player based on the number of overflowing tiles
int negativePoints(int overflowingTiles) {
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