#include <stdio.h>
#include <windows.h>

#ifndef __CONSOLE_HANDLER_H__
#define __CONSOLE_HANDLER_H__



// THIS IS WHERE THE BOARD IS RENDERED


// Used to remove highlighting from the tiles
extern int highlightedTile[];

extern const int backgroundColor;

extern const int boardVerticalOffset;

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
const char *menuButtons[8];




// --- PROTOTYPES ---


// Toggles fullscreen mode
void toggleFullscreen();

// Clears the console
void clearConsole();

// Places the console pointer at the given coordinates
void consolePointer(int x, int y);

// Changes the console text and background colors
void consoleColor(int color, int background);

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

// Higlights the given tile while removing previous highlights
void highlightTile(int x, int y);

#endif // __CONSOLE_HANDLER_H__é



