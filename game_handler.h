#ifndef __GAME_HANDLER_H__
#define __GAME_HANDLER_H__


// THIS IS WHERE PLAYER POINTS ARE CALCULATED


#define PLAYER_COUNT        4
#define BANK_TILE_COUNT     100
#define FACTORY_TILE_COUNT  4
#define FACTORY_COUNT       9

extern const int emptyBoardMatrix[5][5];

extern const int emptySideBoardMatrix[5][5];


// Player structure (2 boards (int[5][5]), 1 overflow tiles counter (int), 1 score (int))
struct PlayerStruct {
    int boardMatrix[5][5];
    int sideBoardMatrix[5][5];
    int overflowTiles;
    int score;
};

typedef struct PlayerStruct PlayerStruct;


// Factory will be instanciated 9 times
struct TileFactoryStruct {
    int tiles[FACTORY_TILE_COUNT];
};

typedef struct TileFactoryStruct TileFactoryStruct;

// Bank
struct TileBankStruct {
    int tiles[BANK_TILE_COUNT];
    int nbTilesRemaining;
};

typedef struct TileBankStruct TileBankStruct;


// Game Structure
struct GameStruct {
    PlayerStruct         players[PLAYER_COUNT];
    TileFactoryStruct    tileFactories[FACTORY_COUNT];
    TileBankStruct       bank;
    TileBankStruct       centerBank;
    int                  currentPlayer;
    int                  priorityPlayer;
};

typedef struct GameStruct GameStruct;



// --- PROTOTYPES ---

// Initializes the game
void initGame(GameStruct* game);

// Initializes the player's informations
void initPlayer(PlayerStruct* player);

// Resets the game
void resetGame(GameStruct* game);

// Calculates the negative points for the player based on the number of overflowing tiles
int negativePoints(int overflowingTiles);

// Starts a game round
void gameRound(GameStruct* game);

// Tests if the game is over (one player has a full row)
int isGameOver(GameStruct game);



#endif // __GAME_HANDLER_H__