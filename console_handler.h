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

// Used to remove highlighting from the tiles
extern int highlightedTile[];

extern const int backgroundColor;

extern const int boardVerticalOffset;

extern const int menuVerticalOffset;

// Default console width to center the game assets (Automatically adjusted)
extern int consoleWidth;
extern int consoleHeight;

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


// Toggles fullscreen mode
void toggleFullscreen();

// Clears the console
void clearConsole();

// Places the console pointer at the given coordinates
void consolePointer(int x, int y);

// Changes the console text and background colors
void consoleColor(int color, int background);

// Creates a button
BUTTON createButton(int x, int y, int width, int height, const char *label);

// Prints the logo
void printLogo(int y);

// Prints the credits
void printCredits(int y);

// Prints the given title at the given coordinates
void printTitle(int tile, int x, int y);

// Prints a background for the game board
void printBackground();

// Prints the main 5x5 board for the given player
void printGameBoard(int board[5][5]);

// Prints the side board for the given player
void printSideBoard(int board[5][5]);

// Prints a given player's interface (board, side board, score, id)
void printPlayerInterface(PlayerStruct player);

// Prints the menu
void printMenu();

// Prints the game end menu
void printEndMenu();

// Higlights the given tile while removing previous highlights
void highlightTile(int x, int y);

// If 'space' is pressed while the mouse is over the button, returns 1
int isButtonPressed(BUTTON button);

// Highlights the given button
void highlightButton(BUTTON button);


#endif // __CONSOLE_HANDLER_H__