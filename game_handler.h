#ifndef __GAME_HANDLER_H__
#define __GAME_HANDLER_H__

#define     NB_PLAYER                   4
#define     NB_TILES_BANK               100
#define     NB_MAX_TILES_IN_FACTORY     4
#define     NB_FACTORY                  9

// THIS IS WHERE PLAYER POINTS ARE CALCULATED

#define NONE          0
#define BLUE          1
#define YELLOW        2
#define RED           3
#define BLACK         4
#define TURQUOISE     5


const int emptyBoardMatrix[5][5];

const int emptySideBoardMatrix[5][5];

// Player
struct PlayerStruct {
    int boardMatrix[5][5];
    int sideBoardMatrix[5][5];
    int overflowTiles;
    int score;
};

typedef struct PlayerStruct PlayerStruct;

// Factory will be instanciated 9 times
struct TileFactoryStruct {
    int tiles[NB_MAX_TILES_IN_FACTORY];
};

typedef struct TileFactoryStruct TileFactoryStruct;

// Bank
struct TileBankStruct {
    int tiles[NB_TILES_BANK];
    int nbTilesRemaining;
};

typedef struct TileBankStruct TileBankStruct;


// Game Structure
struct GameStruct {
   PlayerStruct         players[NB_PLAYER];
   TileFactoryStruct    tileFactories[NB_FACTORY];
   TileBankStruct       bank;
   int                  currentPlayer;
};

typedef struct GameStruct GameStruct;



// --- PROTOTYPES ---
void initPlayer(PlayerStruct* player);

// Resets the game
void resetGame(GameStruct* game);

// Calculates the negative points for the player based on the number of overflowing tiles
int negativePoints(int overflowingTiles);


// Moove tiles from factory to side board
void moveTilesSideBoard(PlayerStruct* player, TileFactoryStruct* factory, int color, int row);

//Moove tiles from side board to main board
void moveTilesMainBoard(PlayerStruct* player, int color, int row, const int board[5][5]);

// Starts a new game round
void gameRound(PlayerStruct* player, TileFactoryStruct* factory);



#endif // __GAME_HANDLER_H__
