// Standard libraries
#include <stdio.h>


// THIS IS WHERE THE PLAYER POINTS ARE CALCULATED


// Creates the scores
int scoreMatrix[4] = {0};

int gamemode = 0; // 0 = default, 1 = free tile placement NOT IMPLEMENTED YET
int playerCount = 4; // NOT IMPLEMENTED YET

int currentPlayer = 0;

// --- PROTOTYPES ---


// Resets the game
void resetGame();

// Calculates the negative points for the player based on the number of overflowing tiles
int negativePoints(int overflowingTiles);






// --- POINT MANAGEMENT FUNCTIONS ---

void resetGame() {
    // Resets the board matrices
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            P1BoardMatrix[i][j] = 0;
            P2BoardMatrix[i][j] = 0;
            P3BoardMatrix[i][j] = 0;
            P4BoardMatrix[i][j] = 0;
        }
    }
    // Resets the side board matrices
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            P1SideBoardMatrix[i][j] = 0;
            P2SideBoardMatrix[i][j] = 0;
            P3SideBoardMatrix[i][j] = 0;
            P4SideBoardMatrix[i][j] = 0;
        }
    }

    // Resets the scores
    for (int i = 0; i < 4; i++) {
        scoreMatrix[i] = 0;
    }   

    // Resets the tile factories
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            tileFactory[i][j] = 0;
        }
    }

    // Resets factories
    resetFactories();

    // Resets the tile bank
    resetTileBank();
    shuffleTileBank();
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