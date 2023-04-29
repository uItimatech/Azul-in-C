#include <stdio.h>
#include <windows.h>
#include <math.h>

#include "console_handler.h"
#include "game_handler.h"
#include "input_handler.h"
#include "tile_handler.h"


// THIS IS WHERE THE BOARD IS RENDERED


// Stores the tiles in an array of matrices
const char *tileSprites[12][3] = {
    {// BLANK TILE
        "|     |",
        "|     |",
        "|     |"
    },{// BLUE TILE
        "[-   -]",
        "|  B  |",
        "[-   -]"
    },{// YELLOW TILE
        "[\\-.-/]",
        "|.-Y-.|",
        "[/-.-\\]"
    },{// RED TILE
        "['---']",
        "|  R  |",
        "['___']"
    },{// BLACK TILE
        "[X-O-X]",
        "|O-B-O|",
        "[X-O-X]"
    },{// TURQUOISE TILE
        "[\\-|-/]",
        "|--T--|",
        "[/-|-\\]"
    },
    // EMPTY TILES (FOR THE EMPTY BOARD LAYOUT)
    {
        "       ",
        "  Blu  ",
        ".     ."
    },{
        "       ",
        "  Yel  ",
        ".     ."
    },{
        "       ",
        "  Red  ",
        ".     ."
    },{
        "       ",
        "  Blk  ",
        ".     ."
    },{
        "       ",
        "  Tuq  ",
        ".     ."
    },{
        "       ",
        "       ",
        "       "
    }
};

const int tileColors[12][2] = {
    // Format: {BACKGROUND COLOR, TEXT COLOR}
    { // BLANK TILE
        0,
        8
    },{ // BLUE TILE
        1,
        9
    },{ // YELLOW TILE
        14,
        6
    },{ // RED TILE
        4,
        15
    },{ // BLACK TILE
        0,
        1
    },{ // TURQUOISE TILE
        3,
        7
    },
    // EMPTY TILES (FOR THE EMPTY BOARD LAYOUT)
    { // BLUE
        1,
        9
    },{ // YELLOW
        14,
        6
    },{ // RED
        4,
        12
    },{ // BLACK
        0,
        8
    },{ // TURQUOISE
        3,
        1
    },{ // EMPTY
        8,
        8
    }

};

// Stores the logo
const char *logoSprite[35] = {
    "                                                              ,(/.                                                              ",
    "                                                             #&((&/                                                             ",
    "                                                   *    ,/ ./#&(#&(*. *.    *                                                   ",
    "                                                ,%(.  ,#/#&&&%(((#&@&&(((.  *%(.                                                ",
    "                                   /&(#&#/.     #%/,#&&&(((((#%%%%#(/(/#&&%/,(#(     *(&%(%%.                                   ",
    "                                      .*(&@#   #&&&&(/#%&%#(#(,%#/%#(#%&%(*#&&&&*  ,%@%/�                                       ",
    "                     .*.                /&&&#(#&%/%%#%#(#*...(%((%*..,#%/%%%%#(%&//%&&%*                ,,                      ",
    "               .#&@&&&/.                *&%@&#/%%#%%(##....,*%/�|##*,..,*%(#%%#%#(&&&%%,                ,#@&&&&(                ",
    "               ((,.,#&&(,             .(%%&(#%(#%#((%(..*#%(/�**|*|(#%(,.,%#((%&##%((&#%/              *#&&/..*#*               ",
    "                  ./%&&&@&%(//////(#%&&&#/%%#%##((((%,...  .*%/�|##,......(%(((##%%#&#/&&&&%#(/�*|/(#%&&&@&(*                   ",
    "      .%&&%###########################(/#%(*,,/%%(##%*..     (%((%,.   ...##%/#%%,,,/(%(/(###########################%&&#.      ",
    "          ,%((%/�************************|*,..*, . .*|.       .%(.      ../,..../...,**|***************|********|%/#(.          ",
    "         .(((%,,,/(/�.......,,,**,,......                                                  ...,,,,,.... ..,/(#*,.(%/%(          ",
    "        /%((#,.,*,,**.  ..    .#&&&@&/(.       /@&&@&&&&&&&&&&&(/. *&&&&&(/.  *%@@&#/.*&@@@&(/.           *,*|.*..*%/(#*        ",
    "     .(&((%/..,,,.             /&%&&#(,         ,&//�..  *&&&#(,    .&&&*,.     (&(,    &&&/�,                .,*,..##/%%/      ",
    "   (%&#(%(..,. ,&*            *@/#%&&%(,          .    .&&&%(/.     .&&&**.     (&(,    &&&(*,                %#..,,.,%#(%&#*   ",
    " /&#/#%/...  *&@#          #&#&/(. %&&%&&//.         .(&&&(#.       .&&&*,.     #&(,    &&&(*,                 &@%.... .#%(/&&, ",
    " /&/(#,#/.%@%,(@&@&.        .&&&/( /@&&#///(.       ,&&&##*         .&&&*,.     #&(.    &&&(*,              (@@&&*|@&*.%/�%((&, ",
    " /&/(%*....,(&&&/.         ,&(/�&&&#(&&&#(.       .%&&%(*.          .&&&*,.     #&(.    &&&(*,                .%@&%*...../##(%, ",
    " ,#@&(#%/......%&.       .*&&(,  ,(, .&&&//.     (&&&/(,    ,%/(.    %&&**,     %%(.   .&&&(*,    #%(,.       (&(  ...,####&&(. ",
    "    .(&((%/.,*,...      *%@&&((      .%&@&%#.  *&@&&%####%&&@@&#/,    /&@%#*,/%&#(*.  .#&&&#(//#&&@&&//,      ,  ,*..#(/%%/     ",
    "       ,%((%,,,*,,. .. .(###%##%*    ,####%%#%/,#%%##%%###%%#####,.     .(#((#%*,,    *(#%%%#######%#%(,. .. .,,*../%/%(.       ",
    "         *#(%*../�,**,,..                .... ..... ..... ..,,.,,,.,.,.. ...............              ...,*|,/�,.,#(/(,         ",
    "          *#/%/,./(**,,,,*,,,,,**|/�,,...(/##.###/(./(/#/ //((/(((((#(/#*|(//#(((((((((#.,,*|//�*,,,,,,*,,,,//,..#((#,          ",
    "       .,*(%#/%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%,............,,,,,,,,,,,,,,............(&%%%%%%%%%%%%%%%%%%%%%%%%%%%%(/&#/,..       ",
    "      .,,/((((#####%&&&&&&&&&&&&&&&&&&@&#(//((##%%%%%%#(##/,.,#*|(..*(#%#%%%%%%##((((((%&&&&&@@&&&&&&&&&&&&%%###(#(((/�,.       ",
    "                 ./�&%(((*  ,(///�.      *&&(&&(#&&&&&&&&#(#(#(#(##(#/%&&&&&&&%(%&##&#.      .//(//.  *((#&#*|                  ",
    "                   //                      (* .&%/�%#&&%(/%&(((##(/#&(/(&&#&#*(&#  //                      /,                   ",
    "                                               #&#  #&%&(&%/./%&&(/.(&%#&&@* ,&&*                                               ",
    "                                              ,%/.     *&#/%%* *, /&#/%%.     .##.                                              ",
    "                                                         ./%&#,  *&&#*.                                                         ",
    "                                                           ,%/    (#                                                            ",
    "                                                              (&%*                                                              ",
    "                                                             .%#%/                                                              ",
    "                                                              .&/.                                                              ",
};


// Stores the credits
const char *credits[2] = {
    "A game by Michael Kiesling, recreated in C by Evan Werquin",
    "This game is licensed under the GNU General Public License v3.0"
};

// Stores the menu buttons
const char *menuButtonLabels[4] = {
    "Play",
    "Rules",
    "Quit"
};

// Stores the hints
const char *gameHints[5] = {
    "",
    "Select a row to place the tile(s) in",
    "Select a board tile", // Currently not used but still available
    "Select a tile color in one of the factories or the side of the table", //NB: the 'table side' is actually the 'center bank' in the physical game
    "Click to continue..."
};

BUTTON menuButtons[4];



// --- CONSOLE AND DISPLAY FUNCTIONS ---


// Toggles fullscreen mode and disables quick edit mode for mouse input
void toggleFullscreen()
{
    keybd_event(VK_MENU,0x38,0,0); // Press 'ALT'
    keybd_event(VK_RETURN,0x1c,0,0); // Press 'ENTER'
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Release 'ENTER'
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); // Release 'ALT'

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_QUICK_EDIT_MODE));
}


// Clears the console using adequate commands for Windows and Linux
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Places the console pointer at the given coordinates
void consolePointer(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos; // Struct type defined in windows.h
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hStdout, pos);
}


// Changes the console text and background colors
void consoleColor (int textColor, int backColor)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, backColor*16+textColor);
}


// Creates a button
BUTTON createButton(int x, int y, int width, int height, const char *label) {
    BUTTON button;
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    strcpy((char*)button.label, label);
    return button;
}


// Creates a game window
GAMEWINDOW createGameWindow() {

    GAMEWINDOW GW;

    GW.DEBUG_MODE   = 1; // Displays additional information in the console
    GW.MAIN_MENU    = 1; // Could use a simple menu ID but this is better for undestanding
    GW.IN_GAME      = 0;
    GW.END_MENU     = 0;

    GW.DISPLAY_STATE = 0;

    strcpy(GW.Title,"Azul");

    GW.backgroundColor = 8;

    GW.boardVerticalOffset = 27;

    GW.playerUIVerticalOffset = 0;

    GW.menuVerticalOffset = 1;

    // Default console width to center the game assets (Automatically adjusted)
    GW.consoleWidth = 250;
    GW.consoleHeight = 60;

    // Used to remove highlighting from the tiles
    GW.highlightedTile[0] = -1;
    GW.highlightedTile[1] = -1;
    GW.previousBoardState = -1;

    GW.highlightedButton = (BUTTON){-1, -1, -1, -1, {""}};

    // Default character size in pixels (Currently not automatically adjusted)
    GW.termCharWidth = 8;
    GW.termCharHeight = 16;

    // Margins to center the game assets (Automatically adjusted)
    GW.leftMargin = 0;
    GW.topMargin = 0;


    return GW;
}

GAMEWINDOW gameWin;


// Prints the logo line by line
void printLogo(int y) {
    int x = gameWin.consoleWidth/2 - strlen(logoSprite[0])/2 +2;
    consolePointer(x, y);
    consoleColor(3, 0);
    for (int i = 0; i < 35; i++) {
        consolePointer(x, y+i);
        printf("%s", logoSprite[i]);
    }
    consoleColor(15, 0); // Resets the color
}


// Prints the credits
void printCredits(int y) {
    int x = gameWin.consoleWidth/2 - strlen(credits[0])/2 +2;

    consolePointer(x, y);
    printf("%s", credits[0]);

    x = gameWin.consoleWidth/2 - strlen(credits[1])/2;
    consolePointer(x, y+1);
    printf("%s", credits[1]);
}


// Prints the the given tile at the given coordinates
void printTile(int tile, int x, int y) {
    consolePointer(x, y);
    for (int i = 0; i < 3; i++) {
        consoleColor(tileColors[tile][1], tileColors[tile][0]); // Sets the color of the tile from the tileColors array
        consolePointer(x, y+i);
        printf("%s", tileSprites[tile][i]);
        consoleColor(gameWin.backgroundColor, gameWin.backgroundColor);
        printf("_"); // Prints an invisible character to avoid color bleeding to the next line
    }
    consoleColor(15, 0); // Resets the color
}


void printBackground(int x, int y, int width, int height) {

    // Prints the background using consolePointer
    consolePointer(x, y);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            consolePointer(x+j, y+i);
            consoleColor(gameWin.backgroundColor, gameWin.backgroundColor);
            printf("%c", 219);
        }
    }
    consoleColor(15, 0); // Resets the color
}


// Prints the main 5x5 board for the given player
void printGameBoard(int board[5][5]) {
    int x = gameWin.consoleWidth/2;
    int y = gameWin.boardVerticalOffset;

    // Prints the board
    consolePointer(x, y+2);
    for (int i = 0; i < 5; i++) {

        // Prints the row arrows
        consoleColor(15, gameWin.backgroundColor);
        consolePointer(x-1, y+3+i*4);
        printf("->");

        for (int j = 0; j < 5; j++) {
            // If the tile is empty, prints from the empty tile sprites
            if (board[i][j] == 0) {
                printTile(emptyBoardMatrix[i][j]+5, x+3+j*8, y+2+i*4);
            }
            else {
                printTile(board[i][j], x+3+j*8, y+2+i*4);
            }
        }
    }
}


// Prints the side board for the given player
void printSideBoard(int board[5][5]) {
    int x = gameWin.consoleWidth/2 - 45;
    int y = gameWin.boardVerticalOffset;

    // Prints the side board
    consolePointer(x, y+2);
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {
            //printTile(board[i][j], x+3+j*8, y+2+i*3);
            // If the tile is 0, prints from the emptyTiles array
            if (board[i][j] == 0) {
                if (emptySideBoardMatrix[i][j] == 0) {
                    printTile(11, x+3+j*8, y+2+i*4);
                }
                else {
                    printTile(0, x+3+j*8, y+2+i*4);
                }
            }
            else {
                printTile(board[i][j], x+3+j*8, y+2+i*3);
            }
        }
    }
}


// Prints the current player's interface (board, side board, score, id)
void printPlayerUI(GameStruct *game) {

    PlayerStruct player = game->players[game->currentPlayer];

    printBackground(gameWin.consoleWidth/2-43, gameWin.boardVerticalOffset+1, 86, 21);
    printGameBoard(player.boardMatrix);
    printSideBoard(player.sideBoardMatrix);

    // Prints the player's score and id
    consoleColor(15, gameWin.backgroundColor);
    consolePointer(gameWin.consoleWidth/2 + 44, gameWin.boardVerticalOffset+21);
    printf("Score: %d", player.score);
    consolePointer(gameWin.consoleWidth/2 + 44, gameWin.boardVerticalOffset+19);
    printf("Player #%d", game->currentPlayer+1);
}


// Prints the game hint corresponding to the current board state
void printGameHint() {
    int x = gameWin.consoleWidth/2 - 43;
    int y = gameWin.boardVerticalOffset + 23;

    consoleColor(8, 0);

    // Clears the line
    consolePointer(x, y);
    for (int i = 0; i < 100; i++) {
        printf(" ");
    }

    // Prints the hint message
    consolePointer(x, y);
    printf("Hint: %s", gameHints[gameWin.boardState]);

}


// Prints the given factory at the given coordinates
void printFactory(TileFactoryStruct factory, int x, int y) {
    // Each factory has 4 tiles that are printed in a 2x2 matrix
    // Each tile is 7 characters wide and 3 characters tall
    // Tiles are spaced 1 character apart

    // The background should start in the top left corner of the board

    // Prints the background
    printBackground(x, y, 17, 9);

    // Prints the factory
    for (int i = 0; i < 2; i++) {
        consolePointer(x, y+i*4);
        for (int j = 0; j < 2; j++) {
            printTile(factory.tiles[2*i+j] , x+1+j*8, y+1+i*4);
        }
    }
}


// Prints all factories
void printFactories(TileFactoryStruct factories[9]) {

    int x = gameWin.consoleWidth/2 - 44;
    int y = 2;

    // Prints the factories
    for (int i = 0; i < 5; i++) {
        printFactory(factories[i], x+i*18, y);
    }
    for (int i = 0; i < 4; i++) {
        printFactory(factories[i+5], x+i*18+8, y+10);
    }
}


// Prints the center bank
void printCenterBank(TileBankStruct bank) {

    int x = gameWin.consoleWidth/2-57;
    int y = gameWin.boardVerticalOffset+1;

    // Prints the background
    printBackground(x-4, y, 13, 21);

    // Prints the bank
    for (int i = 0; i < 5; i++) {
        consoleColor(15, gameWin.backgroundColor);
        consolePointer(x-3, y+i*4+2);
        printf("%d x", getCenterBankTileCount(bank, i+1));
        printTile(i+1, x+1, y+1+i*4);
    }
}


// Prints the whole game UI
void printGameUI(GameStruct *game) {
    // Refreshes the game UI
    consoleColor(15,0);
    clearConsole();
    printFactories(game->tileFactories);
    printCenterBank(game->centerBank);
    printPlayerUI(game);
}


// Prints the menu
void printMenu() {

    char hint[21] = {"[Use mouse to select]"};

    printLogo(gameWin.menuVerticalOffset);
    printCredits(gameWin.menuVerticalOffset+37);

    consoleColor(8, 0);
    // Prints the 4 menu buttons on the same line (Play Options, Rules, Exit)
    for (int i = 0; i < 4; i++) {
        consolePointer(menuButtons[i].x+2, menuButtons[i].y);
        printf("%s",(const char*)menuButtons[i].label);
    }

    consoleColor(8, 0);
    consolePointer(gameWin.consoleWidth/2 - strlen(hint)/2 + 2, gameWin.consoleHeight-1);
    printf("%s", hint);
}


// Prints the game end menu
void printEndMenu() {
    
}


// Higlights the given tile while removing previous highlights
// Higlighting consists of printing a white 7x7 frame arround the given tile
void highlightTile(int x, int y, int boardState){

    consolePointer(gameWin.consoleWidth, gameWin.consoleHeight);

    int yDisplacement = gameWin.boardVerticalOffset;

    int prevX = gameWin.highlightedTile[0];
    int prevY = gameWin.highlightedTile[1];

    // If the tile is already highlighted, returns
    if (prevX == x && prevY == y) return;

    // Displacement is used to move the highlighted tile to the right if the tile is in the right side of the board
    int displacement = 0;

    if (gameWin.previousBoardState == 2) displacement = 5;

    // Removes the highlight from the previous tile by highlighting it with the background color
    //consolePointer(prevX*8 + gameWin.consoleWidth/2 - 85/2 - 9 + displacement, prevY*4 + yDisplacement - 3);
    consoleColor(gameWin.backgroundColor, gameWin.backgroundColor);

    // Removes highlight for board tiles
    if ((gameWin.previousBoardState == 1 || gameWin.previousBoardState == 2) && (prevX != -1 && prevY != -1) && (prevX != 11 && prevY != 6)) {

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(prevX*8 + gameWin.consoleWidth/2 - 85/2 - 9 + displacement + j, prevY*4 + yDisplacement - 3 + i);

                // Places the highlight on the right side of the side board
                if (gameWin.previousBoardState==1) consolePointer(gameWin.consoleWidth/2 - 85/2 + 31 + displacement + j, prevY*4 + yDisplacement - 3 + i);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8) && gameWin.previousBoardState==2) printf("%c", 219);
                if (((i == 0 && j>5) || (i == 4 && j>5) || j == 8) && gameWin.previousBoardState==1) printf("%c", 219);
            }
        }

    // Removes highlights factory tiles
    } else if (gameWin.previousBoardState == 3 && prevX != 9 && prevX != -1 && prevY != -1) {

        // Highlights the current tile
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {

                // If the tile is in the first row of the factorprevY
                if (prevX<5) consolePointer(gameWin.consoleWidth/2 +prevX*18+j     -44 +floor(prevY%2)*8, i+2  +floor(prevY/2)*4);
                // If the tile is in the second row of the factorprevY
                if (prevX>4) consolePointer(gameWin.consoleWidth/2 +(prevX-5)*18+j -36 +floor(prevY%2)*8, i+12 +floor(prevY/2)*4);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8)) printf("%c", 219);
            }
        }
    } else if (gameWin.previousBoardState == 3  && prevX == 9 && prevY != -1) {
            
        // Highlights the current tile
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(gameWin.consoleWidth/2 - 57 + j, gameWin.boardVerticalOffset + i+prevY*4 -3);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8)) printf("%c", 219);
            }
        }
    }


    // If the tile is in the main board, adds 5 to the x coordinate
    if (boardState==2) x += 5;
    

    // Updates the currently highlighted tile id
    gameWin.highlightedTile[0] = x;
    gameWin.highlightedTile[1] = y;
    gameWin.previousBoardState = boardState;

    consoleColor(15,0);

    // Highlights main board tiles
    if ((boardState == 1 || boardState == 2) && (x != 11 && y != 6) && (x != -1 && y != -1)) {

        displacement = 0;

        if (x>5) displacement = 5;

        // Highlights the current tile
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(x*8 + gameWin.consoleWidth/2 - 85/2 - 9 + displacement + j, y*4 + yDisplacement - 3 + i);

                // Places the highlight on the right side of the side board
                if (boardState==1) consolePointer(gameWin.consoleWidth/2 - 85/2 + 31 + displacement + j, y*4 + yDisplacement - 3 + i);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8) && x>5) printf("%c", 219);
                if (((i == 0 && j>5) || (i == 4 && j>5) || j == 8) && x<6) printf("%c", 219);
            }
        }

    // Highlights factory tiles
    } else if (boardState == 3  && (x != 9 &&x != -1 && y != -1)) {

        // Highlights the current tile
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {

                // If the tile is in the first row of the factory
                if (x<=4) consolePointer(gameWin.consoleWidth/2 +x*18+j     -44 +round(y%2)*8, i+2  +round(y/2)*4);
                // If the tile is in the second row of the factory
                if (x>=5) consolePointer(gameWin.consoleWidth/2 +(x-5)*18+j -36 +round(y%2)*8, i+12 +round(y/2)*4);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8)) printf("%c", 219);
            }
        }

    // Highlights center bank tiles
    } else if (boardState == 3  && x == 9 && y != -1) {
            
        // Highlights the current tile
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(gameWin.consoleWidth/2 - 57 + j, gameWin.boardVerticalOffset + i+y*4 -3);

                // Creates the highlight frame
                if ((i == 0 || i == 4 || j == 0 || j == 8)) printf("%c", 219);
            }
        }
    }

    consolePointer(0,0);
    consoleColor(15,0);
}


// Highlights the given button if the mouse is over it
void highlightButton(BUTTON button) {

    consolePointer(gameWin.consoleWidth, gameWin.consoleHeight);

    // If the button is already highlighted, returns
    if (gameWin.highlightedButton.x == button.x && gameWin.highlightedButton.y == button.y) return;

    // Removes the highlight from the previous button
    if (gameWin.highlightedButton.x != -1 && gameWin.highlightedButton.y != -1) {
        consolePointer(gameWin.highlightedButton.x, gameWin.highlightedButton.y);
        consoleColor(gameWin.backgroundColor, 0);
        printf("  %s  ", (const char*)gameWin.highlightedButton.label);
    }

    gameWin.highlightedButton.x = button.x;
    gameWin.highlightedButton.y = button.y;
    strcpy((char*)gameWin.highlightedButton.label, (char*)button.label);

    if (isMouseInRect(button.x, button.y, button.width, button.height)) {
        consolePointer(button.x, button.y);
        consoleColor(15, 0);
        printf("~ %s ~", (const char*)button.label);
    } else {
        consolePointer(button.x, button.y);
        consoleColor(gameWin.backgroundColor, 0);
        printf("  %s  ", (const char*)button.label);
    }
}


// If mouse is pressed while the mouse is over the button, returns 1
int isButtonPressed(BUTTON button) {
    if (isMouseInRect(button.x, button.y, button.width, button.height)) {
        if (mousePressed()) {
            // wait for the space key to be released
            while (mousePressed());

            // checks if the mouse is still over the button
            if (isMouseInRect(button.x, button.y, button.width, button.height))
            return 1;
        }
    }
    return 0;
}