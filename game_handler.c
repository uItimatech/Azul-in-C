// Standard libraries
#include <stdio.h>
#include <math.h>

#include "game_handler.h"
#include "tile_handler.h"
#include "console_handler.h"
#include "input_handler.h"


// THIS IS WHERE THE GAME ROUNDS ARE MANAGED AND PLAYER POINTS ARE CALCULATED


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
    player->lastTilePos.x = -1;
    player->lastTilePos.y = -1;
}

// Starts a game round
void gameRound(GameStruct* game) {

    game->currentPlayer = game->priorityPlayer;
    game->priorityPlayer = -1;

    int roundEndCondition = 0;

    // --- DURING THE ROUND ---
    while (!roundEndCondition) {

        printGameUI(game);



        // 1) Let the player choose tiles from a factory or the center
        gameWin.boardState = 3;
        printGameHint();

        // Waits for the player to choose a factory or the center
        int validTileMove = 0;
        while (mousePressed()==0 || validTileMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);


            // Checks if the player has chosen a valid factory
            validTileMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1;


            // If the player has chosen a factory, checks if it is the center bank
            if (validTileMove && getMouseBoardTilePos(gameWin.boardState).x == 9) {
                // Checks if the choosen color is still available in the center bank
                validTileMove = (getCenterBankTileCount(game->centerBank, getMouseBoardTilePos(gameWin.boardState).y) > 0)  &&  (isThereValidMove(game, getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y));
            // If the player has chosen a factory, checks if it is not empty
            } else if (validTileMove) {
                // Checks if the choosen color is still available in the factory
                validTileMove = (game->tileFactories[getMouseBoardTilePos(gameWin.boardState).x].tiles[0] != 0)  &&  (isThereValidMove(game, getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y));
            }

            // NB: Those conditions could fit into a single if statement, but they are obviously separated for readability
        }

        int selectedFactory = getMouseBoardTilePos(gameWin.boardState).x;
        int selectedTile = getMouseBoardTilePos(gameWin.boardState).y;

        // DEBUG ONLY
        int selectedTileColor = game->tileFactories[selectedFactory].tiles[selectedTile];
        if (selectedFactory == 9) {
            selectedTileColor = selectedTile;
        }





        // 2) Let the player choose a sideboard row
        gameWin.boardState = 1;
        printGameHint();

        // Waits for the player to choose a valid sideboard row
        int validSideMove = 0;
        while (mousePressed()==0 || validSideMove == 0) {
            highlightTile(getMouseBoardTilePos(gameWin.boardState).x, getMouseBoardTilePos(gameWin.boardState).y, gameWin.boardState);

            // Checks if the player has chosen a valid sideboard row
            validSideMove = getMouseBoardTilePos(gameWin.boardState).x!=-1 && getMouseBoardTilePos(gameWin.boardState).y!=-1 && isValidSideBoardMove(game, selectedFactory, selectedTile, getMouseBoardTilePos(gameWin.boardState).y-1);
        }





        // 3) Moves the tiles from the factory or the center to the sideboard
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
            printf("Remaining center bank tiles: %d\n", game->centerBank.nbTilesRemaining);
        }





        // 5) Waits for mouse click to switch to the next player
        while (mousePressed()!=0);
        while (mousePressed()==0);

        // Changes the current player
        game->currentPlayer = (game->currentPlayer + 1) % (PLAYER_COUNT);

        // Checks if the round is over
        // This check is done here to avoid the round ending early because the center bank is empty
        roundEndCondition = areFactoriesEmpty(game) && isCenterBankEmpty(game);
    }




    // --- END OF ROUND ---


    // Refills the factories
    for (int i = 0; i < FACTORY_COUNT; i++) {
        refillFactory(&game->tileFactories[i], &game->bank);
    }

    // Moves the completed players side board rows to their main board
    for (int i = 0; i < PLAYER_COUNT; i++) {
        for (int j = 0; j < 5; j++) {
            if (isSideBoardRowFull(game->players[i], j)) {

                // Adds the other tiles back to the tile bank
                int tilesToAdd = j;
                
                for (int k = 0; k < tilesToAdd; k++) {
                    game->bank.tiles[game->bank.nbTilesRemaining] = game->players[i].sideBoardMatrix[j][k];
                    game->bank.nbTilesRemaining++;
                }

                // Moves the completed row to the main board
                moveRowToMain(&game->players[i], j);

                // Updates the scores for each tile placed
                updatedTileScore(&game->players[i], game->players[i].lastTilePos.x, game->players[i].lastTilePos.y);
            }
        }
        // Updates the player's negative points
        negatePoints(&game->players[i]);
    }

    // Shuffles the remaining tiles in the tile bank
    shuffleTileBank(&game->bank);
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


// Calculates the negative points at the end of the round for the player based on the number of overflowing tiles
void negatePoints(PlayerStruct *player) {

    if (player->overflowTiles >= 1 && player->overflowTiles <= 2) {
        player->score -= 1;
    } else if (player->overflowTiles >= 3 && player->overflowTiles <= 5) {
        player->score -= 2;
    } else if (player->overflowTiles >= 6) {
        player->score -= 3;
    }

    if (player->score < 0) {
        player->score = 0;
    }

    player->overflowTiles = 0;
}


// Updates the player score based on the latest tile placement
void updatedTileScore(PlayerStruct* player, int x, int y) {

    // If no tile was placed, returns
    if (x==-1 || y==-1) {
        return;
    }

    // Checks if the row is completed
    int rowCompleted = 1;
    for (int i = 0; i < 5; i++) {
        if (player->boardMatrix[i][y] == 0) {
            rowCompleted = 0;
        }
    }

    // Checks if the column is completed
    int columnCompleted = 1;
    for (int i = 0; i < 5; i++) {
        if (player->boardMatrix[x][i] == 0) {
            columnCompleted = 0;
        }
    }

    // Checks if the color is completed
    int tileColor = player->boardMatrix[x][y];
    int colorCompleted = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++){
            if (emptyBoardMatrix[i][j] == tileColor && player->boardMatrix[i][j] == 0) {
                colorCompleted = 0;
            }
        }
    }

    // Adds the points to the player score
    player->score += 1 + 2*rowCompleted + 7*columnCompleted + 10*colorCompleted;

    // Counts the number of connected tiles in each direction (including the placed tile)
    for (int i = 1; i < 5; i++) {
        if (x+i < 5 && player->boardMatrix[x+i][y] != 0) {
            player->score++;
        } 
        if (x-i >= 0 && player->boardMatrix[x-i][y] != 0) {
            player->score++;
        }
        if (y+i < 5 && player->boardMatrix[x][y+i] != 0) {
            player->score++;
        }
        if (y-i >= 0 && player->boardMatrix[x][y-i] != 0) {
            player->score++;
        }
    }

    player->lastTilePos.x = -1;
    player->lastTilePos.y = -1;
}