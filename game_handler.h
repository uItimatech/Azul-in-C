#ifndef __GAME_HANDLER_H__
#define __GAME_HANDLER_H__


// THIS IS WHERE PLAYER POINTS ARE CALCULATED


// Creates the scores
extern int scoreMatrix[4];

extern int gamemode; // 0 = default, 1 = free tile placement NOT IMPLEMENTED YET
extern int playerCount; // NOT IMPLEMENTED YET

extern int currentPlayer;

// --- PROTOTYPES ---


// Resets the game
void resetGame();

// Calculates the negative points for the player based on the number of overflowing tiles
int negativePoints(int overflowingTiles);


// Moove tiles from factory to side board
void moveTiles(int playerNumber, int factory, int color, int row);

// Starts a new game round
void startRound();



#endif // __GAME_HANDLER_H__
