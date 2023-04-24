#include <stdio.h>
#include <windows.h>

#include "console_handler.h"
#include "game_handler.h"
#include "input_handler.h"


// THIS IS WHERE THE BOARD IS RENDERED


const int backgroundColor = 8;

const int boardVerticalOffset = 32;

const int menuVerticalOffset = 10;

// Default console width to center the game assets (Automatically adjusted)
int consoleWidth = 214;
int consoleHeight = 30;

// Used to remove highlighting from the tiles
int highlightedTile[2] = {-1, -1};

BUTTON highlightedButton = {-1, -1, -1, -1, {""}};


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
        ".     .",
        "  Blu  ",
        ".     ."
    },{
        ".     .",
        "  Yel  ",
        ".     ."
    },{
        ".     .",
        "  Red  ",
        ".     ."
    },{
        ".     .",
        "  Blk  ",
        ".     ."
    },{
        ".     .",
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
    {// BLANK TILE
        0,
        8
    },{// BLUE TILE
        1,
        9
    },{// YELLOW TILE
        14,
        6
    },{// RED TILE
        4,
        12
    },{// BLACK TILE
        16,
        1
    },{// TURQUOISE TILE
        3,
        7
    },
    // EMPTY TILES (FOR THE EMPTY BOARD LAYOUT)
    {
        1,
        9
    },{
        14,
        6
    },{
        4,
        12
    },{
        16,
        1
    },{
        3,
        7
    },{
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
    "A game by Michael Kiesling, recreated in C by Evan Werquin and Quentin Thouvier",
    "This game is licensed under the GNU General Public License v3.0"
};

// Stores the menu buttons
const char *menuButtonLabels[4] = {
    "Play",
    "Options",
    "Rules",
    "Quit"
};

BUTTON menuButtons[4];



// --- CONSOLE AND DISPLAY FUNCTIONS ---


// Toggles fullscreen mode
void toggleFullscreen()
{
    keybd_event(VK_MENU,0x38,0,0); // Press 'ALT'
    keybd_event(VK_RETURN,0x1c,0,0); // Press 'ENTER'
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Release 'ENTER'
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); // Release 'ALT'
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

// Prints the logo line by line
void printLogo(int y) {
    int x = consoleWidth/2 - strlen(logoSprite[0])/2;
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
    int x = consoleWidth/2 - strlen(credits[0])/2;

    consolePointer(x, y);
    printf("%s", credits[0]);

    x = consoleWidth/2 - strlen(credits[1])/2;
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
        consoleColor(backgroundColor, backgroundColor);
        printf("_"); // Prints an invisible character to avoid color bleeding to the next line
    }
    consoleColor(15, 0); // Resets the color
}

void printBackground() {
    int x = consoleWidth/2 - 89/2 + 1;
    int y = boardVerticalOffset + 1;
    int boardSizeX = 86;
    int boardSizeY = 21;

    // Prints the background using consolePointer
    consolePointer(x, y);
    for (int i = 0; i < boardSizeY; i++) {
        for (int j = 0; j < boardSizeX; j++) {
            consolePointer(x+j, y+i);
            consoleColor(backgroundColor, backgroundColor);
            printf("%c", 219);
        }
    }
    consoleColor(15, 0); // Resets the color
}

// Prints the main 5x5 board for the given player
void printGameBoard(int board[5][5]) {
    int x = consoleWidth/2;
    int y = boardVerticalOffset;

    // Prints the column numbers
    /*consoleColor(15, backgroundColor);
    consolePointer(x+6, y);
    printf("1       2       3       4       5");
    consolePointer(x+6, y+1);
    printf("v       v       v       v       v");*/

    // Prints the board
    consolePointer(x, y+2);
    for (int i = 0; i < 5; i++) {

        // Prints the row arrows
        consoleColor(15, backgroundColor);
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
    int x = consoleWidth/2 - 45;
    int y = boardVerticalOffset;

    // Prints the side board
    consolePointer(x, y+2);
    for (int i = 0; i < 5; i++) {

        // Prints the row numbers
        /*consoleColor(15, backgroundColor);
        consolePointer(x, y+3+i*4);
        printf("%d", i+1);
        consolePointer(x+1, y+3+i*4);
        printf(">");*/

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

// Prints a given player's interface (board, side board, score, id)
void printPlayerInterface(PlayerStruct player){
    printBackground();
    printGameBoard(player.boardMatrix);
    printSideBoard(player.sideBoardMatrix);
}

// Prints the menu
void printMenu(){
    printLogo(menuVerticalOffset);
    printCredits(menuVerticalOffset+36);

    // Prints the 4 menu buttons on the same line (Play Options, Rules, Exit)
    for (int i = 0; i < 4; i++) {
        consolePointer(menuButtons[i].x, menuButtons[i].y);
        printf("%s",(const char*)menuButtons[i].label);
    }
}

// Prints the game end menu
void printEndMenu(){
    
}

// Higlights the given tile while removing previous highlights
// Higlighting consists of printing a white 7x7 frame arround the given tile
void highlightTile(int x, int y){

    int yDisplacement = boardVerticalOffset;

    // If the tile is already highlighted, returns
    if (highlightedTile[0] == x && highlightedTile[1] == y) return;

    // If the current tile is different from the previous tile, removes the highlight from the previous tile
    int prevX = highlightedTile[0];
    int prevY = highlightedTile[1];

    // Displacement is used to move the highlighted tile to the right if the tile is in the right side of the board
    int displacement = 0;

    if (prevX>5) displacement = 5;

    // Removes the highlight from the previous tile by highlighting it with the background color
    consolePointer(prevX*8 + consoleWidth/2 - 85/2 - 9 + displacement, prevY*4 + yDisplacement - 3);
    consoleColor(backgroundColor, backgroundColor);

    if ((prevX != -1 && prevY != -1) && (prevX != 11 && prevY != 6)) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(prevX*8 + consoleWidth/2 - 85/2 - 9 + displacement + j, prevY*4 + yDisplacement - 3 + i);

                // Places the highlight on the right side of the side board
                if (prevX<6) consolePointer(consoleWidth/2 - 85/2 + 31 + displacement + j, prevY*4 + yDisplacement - 3 + i);

                if ((i == 0 || i == 4 || j == 0 || j == 8) && prevX>5) printf("%c", 219);
                if (((i == 0 && j>5) || (i == 4 && j>5) || j == 8) && prevX<6) printf("%c", 219);
            }
        }
    }

    highlightedTile[0] = x;
    highlightedTile[1] = y;

    if ((x != -1 && y != -1) && (x != 11 && y != 6)) {

        displacement = 0;

        if (x>5) displacement = 5;

        // Highlights the current tile
        consolePointer(x*8 + consoleWidth/2 - 85/2 - 9 + displacement, y*4 + yDisplacement - 3);
        consoleColor(15, 0);

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                consolePointer(x*8 + consoleWidth/2 - 85/2 - 9 + displacement + j, y*4 + yDisplacement - 3 + i);

                // Places the highlight on the right side of the side board
                if (x<6) consolePointer(consoleWidth/2 - 85/2 + 31 + displacement + j, y*4 + yDisplacement - 3 + i);

                if ((i == 0 || i == 4 || j == 0 || j == 8) && x>5) printf("%c", 219);
                if (((i == 0 && j>5) || (i == 4 && j>5) || j == 8) && x<6) printf("%c", 219);
            }
        }

    } else {
        return;
    }
}

// If 'space' is pressed while the mouse is over the button, returns 1
int isButtonPressed(BUTTON button) {
    if (isMouseInRect(button.x, button.y, button.width, button.height)) {
        if (GetAsyncKeyState(VK_SPACE)) {
            // wait for the space key to be released
            while (GetAsyncKeyState(VK_SPACE));
            
            // checks if the mouse is still over the button
            if (isMouseInRect(button.x, button.y, button.width, button.height))
            return 1;
        }
    }
    return 0;
}

// Highlights the given button if the mouse is over it
void highlightButton(BUTTON button) {

    // If the button is already highlighted, returns
    if (highlightedButton.x == button.x && highlightedButton.y == button.y) return;

    // Removes the highlight from the previous button
    if (highlightedButton.x != -1 && highlightedButton.y != -1) {
        consolePointer(highlightedButton.x-2, highlightedButton.y);
        //consoleColor(15, backgroundColor);
        printf("  %s  ", (const char*)highlightedButton.label);
    }

    highlightedButton.x = button.x;
    highlightedButton.y = button.y;
    strcpy((char*)highlightedButton.label, (char*)button.label);

    if (isMouseInRect(button.x, button.y, button.width, button.height)) {
        consolePointer(button.x-2, button.y);
        //consoleColor(backgroundColor, 15);
        printf("- %s -", (const char*)button.label);
    } else {
        consolePointer(button.x-2, button.y);
        //consoleColor(15, backgroundColor);
        printf("  %s  ", (const char*)button.label);
    }
}