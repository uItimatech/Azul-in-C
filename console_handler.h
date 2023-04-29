#ifndef __CONSOLE_HANDLER_H__
#define __CONSOLE_HANDLER_H__

#include <stdio.h>
#include <windows.h>

#include "game_handler.h"

// THIS IS WHERE THE BOARD IS RENDERED


// Button structure containing the coordinates and size
struct BUTTON{
    int x;
    int y;
    int width;
    int height;
    const char *label[16];
};

typedef struct BUTTON BUTTON;

struct GAMEWINDOW{
    int DEBUG_MODE;

    int MAIN_MENU;
    int IN_GAME;
    int END_MENU;

    // Display state is used to prevent the interface from being redrawn every frame
    int DISPLAY_STATE;

    char Title[16];

    int backgroundColor;

    int boardVerticalOffset;

    int playerUIVerticalOffset;

    int menuVerticalOffset;

    // Default console width to center the game assets (Automatically adjusted)
    int consoleWidth;
    int consoleHeight;

    // Used to remove highlighting from the tiles
    int highlightedTile[2];
    int previousBoardState;

    BUTTON highlightedButton;

    // Default character size in pixels (Currently not automatically adjusted)
    int termCharWidth;
    int termCharHeight;

    // Margins to center the game assets (Automatically adjusted)
    double leftMargin;
    double topMargin;

    int tileState; // 0: tile not picked, 1: tile picked, 2: tile placed
    int boardState; // 0: no inputs, 1: side board inputs, 2: main board inputs, 3: factory inputs

};

typedef struct GAMEWINDOW GAMEWINDOW;

extern GAMEWINDOW gameWin;


// Stores the tiles in an array of matrices
extern const char *tileSprites[12][3];
extern const int tileColors[12][2];

// Stores the logo
extern const char *logoSprite[35];

// Stores the credits
extern const char *credits[2];

// Stores the menu buttons
extern const char *menuButtonLabels[4];

// Stores the menu buttons
extern BUTTON menuButtons[4];



// --- PROTOTYPES ---


// Toggles fullscreen mode and disables quick edit mode for mouse input
void toggleFullscreen();

// Clears the console
void clearConsole();

// Places the console pointer at the given coordinates
void consolePointer(int x, int y);

// Changes the console text and background colors
void consoleColor(int color, int background);

// Creates a button
BUTTON createButton(int x, int y, int width, int height, const char *label);

// Creates a game window
GAMEWINDOW createGameWindow();

// Prints the logo
void printLogo(int y);

// Prints the credits
void printCredits(int y);

// Prints the given title at the given coordinates
void printTitle(int tile, int x, int y);

// Prints a background for the game board
void printBackground(int x, int y, int width, int height);

// Prints the main 5x5 board for the given player
void printGameBoard(int board[5][5]);

// Prints the side board for the given player
void printSideBoard(int board[5][5]);

// Prints the current player's interface (board, side board, score, id)
void printPlayerUI(GameStruct* game);

// Prints the game hint corresponding to the current board state
void printGameHint();

// Prints the given factory at the given coordinates
void printFactory(TileFactoryStruct factory, int x, int y);

// Prints all factories
void printFactories(TileFactoryStruct factories[9]);

// Prints the center bank
void printCenterBank(TileBankStruct bank);

// Prints the whole game UI (factories, center bank, player UI)
void printGameUI(GameStruct *game);

// Prints the menu
void printMenu();

// Prints the game end menu
void printEndMenu();

// Higlights the given tile while removing previous highlights
void highlightTile(int x, int y, int tileState);

// Highlights the given button
void highlightButton(BUTTON button);

// If 'space' is pressed while the mouse is over the button, returns 1
int isButtonPressed(BUTTON button);



#endif // __CONSOLE_HANDLER_H__