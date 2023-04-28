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

        // Refreshes the game UI
        consoleColor(15,0);
        clearConsole();
        printFactories(game->tileFactories);
        printPlayerUI(game);

        // Let the player choose tiles from a factory or the center
        gameWin.boardState = 3;

        // Waits for the player to choose a factory or the center
        int validFactMove = 0;
        while (mousePressed()==0 || validFactMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);
            validFactMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1;
        }

        int selectedFactory = getMouseBoardTilePos(gameWin.boardState).x;
        int selectedTile = getMouseBoardTilePos(gameWin.boardState).y;

        // Let the player choose a sideboard row
        gameWin.boardState = 1;

        // Waits for the player to choose a sideboard row
        int validSideMove = 0;
        while (mousePressed()==0 || validSideMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);
            validSideMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1 && isValidSideBoardMove(game, selectedFactory, selectedTile, getMouseBoardTilePos(gameWin.boardState).x);
        }

        // Moves the tiles from the factory or the center to the sideboard
        moveTilesFromFactory(game, selectedFactory, selectedTile, getMouseBoardTilePos(gameWin.boardState).x);






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
// (1-2: -1, 3-5: -2, 5-infinity: -3)
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