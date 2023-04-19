#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <windows.h>

// THIS IS WHERE INPUTS ARE PROCESSED


// --- PROTOTYPES ---


// Gets the size of a character of the terminal in pixels
//SIZE getCharSize();

// Returns raw mouse coordinates as a POINT struct
POINT getMousPos();

// Returns mouse coordinates on the terminal as a POINT struct
POINT getTMousePos();

// Returns mouse coordinates on the game boards as a POINT struct
POINT getMouseBoardTilePos();

// Returns the state of the left mouse button
int mousePressed();

// Default character size in pixels (Automatically adjusted)
extern int termCharWidth;
extern int termCharHeight;

extern double leftMargin;
extern double topMargin;

#endif



