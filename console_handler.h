#include <windows.h>

// Fix console width to center the game assets
CONST SHORT consoleWidth = 214;

// Creates a 5x5 layout of the empty board and empty side board
int emptyBoardMatrix[5][5] = {0};
int emptySideBoardMatrix[5][5] = {0};


// Stores the tiles in an array of matrices
const char *tileSprites[17][3] = {
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

// Stores the logo
const char *logoSprite[35] = {
    "                                                              ,(/.                                                              ",
    "                                                             #&((&/                                                             ",
    "                                                   *    ,/ ./#&(#&(*. *.    *                                                   ",
    "                                                ,%(.  ,#/#&&&%(((#&@&&(((.  *%(.                                                ",
    "                                   /&(#&#/.     #%/,#&&&(((((#%%%%#(/(/#&&%/,(#(     *(&%(%%.                                   ",
    "                                      .*(&@#   #&&&&(/#%&%#(#(,%#/%#(#%&%(*#&&&&*  ,%@%/°                                       ",
    "                     .*.                /&&&#(#&%/%%#%#(#*...(%((%*..,#%/%%%%#(%&//%&&%*                ,,                      ",
    "               .#&@&&&/.                *&%@&#/%%#%%(##....,*%/°|##*,..,*%(#%%#%#(&&&%%,                ,#@&&&&(                ",
    "               ((,.,#&&(,             .(%%&(#%(#%#((%(..*#%(/°**|*|(#%(,.,%#((%&##%((&#%/              *#&&/..*#*               ",
    "                  ./%&&&@&%(//////(#%&&&#/%%#%##((((%,...  .*%/°|##,......(%(((##%%#&#/&&&&%#(/°*|/(#%&&&@&(*                   ",
    "      .%&&%###########################(/#%(*,,/%%(##%*..     (%((%,.   ...##%/#%%,,,/(%(/(###########################%&&#.      ",
    "          ,%((%/°************************|*,..*, . .*|.       .%(.      ../,..../...,**|***************|********|%/#(.          ",
    "         .(((%,,,/(/°.......,,,**,,......                                                  ...,,,,,.... ..,/(#*,.(%/%(          ",
    "        /%((#,.,*,,**.  ..    .#&&&@&/(.       /@&&@&&&&&&&&&&&(/. *&&&&&(/.  *%@@&#/.*&@@@&(/.           *,*|.*..*%/(#*        ",
    "     .(&((%/..,,,.             /&%&&#(,         ,&//°..  *&&&#(,    .&&&*,.     (&(,    &&&/°,                .,*,..##/%%/      ",
    "   (%&#(%(..,. ,&*            *@/#%&&%(,          .    .&&&%(/.     .&&&**.     (&(,    &&&(*,                %#..,,.,%#(%&#*   ",
    " /&#/#%/...  *&@#          #&#&/(. %&&%&&//.         .(&&&(#.       .&&&*,.     #&(,    &&&(*,                 &@%.... .#%(/&&, ",
    " /&/(#,#/.%@%,(@&@&.        .&&&/( /@&&#///(.       ,&&&##*         .&&&*,.     #&(.    &&&(*,              (@@&&*|@&*.%/°%((&, ",
    " /&/(%*....,(&&&/.         ,&(/°&&&#(&&&#(.       .%&&%(*.          .&&&*,.     #&(.    &&&(*,                .%@&%*...../##(%, ",
    " ,#@&(#%/......%&.       .*&&(,  ,(, .&&&//.     (&&&/(,    ,%/(.    %&&**,     %%(.   .&&&(*,    #%(,.       (&(  ...,####&&(. ",
    "    .(&((%/.,*,...      *%@&&((      .%&@&%#.  *&@&&%####%&&@@&#/,    /&@%#*,/%&#(*.  .#&&&#(//#&&@&&//,      ,  ,*..#(/%%/     ",
    "       ,%((%,,,*,,. .. .(###%##%*    ,####%%#%/,#%%##%%###%%#####,.     .(#((#%*,,    *(#%%%#######%#%(,. .. .,,*../%/%(.       ",
    "         *#(%*../°,**,,..                .... ..... ..... ..,,.,,,.,.,.. ...............              ...,*|,/°,.,#(/(,         ",
    "          *#/%/,./(**,,,,*,,,,,**|/°,,...(/##.###/(./(/#/ //((/(((((#(/#*|(//#(((((((((#.,,*|//°*,,,,,,*,,,,//,..#((#,          ",
    "       .,*(%#/%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%,............,,,,,,,,,,,,,,............(&%%%%%%%%%%%%%%%%%%%%%%%%%%%%(/&#/,..       ",
    "      .,,/((((#####%&&&&&&&&&&&&&&&&&&@&#(//((##%%%%%%#(##/,.,#*|(..*(#%#%%%%%%##((((((%&&&&&@@&&&&&&&&&&&&%%###(#(((/°,.       ",
    "                 ./°&%(((*  ,(///°.      *&&(&&(#&&&&&&&&#(#(#(#(##(#/%&&&&&&&%(%&##&#.      .//(//.  *((#&#*|                  ",
    "                   //                      (* .&%/°%#&&%(/%&(((##(/#&(/(&&#&#*(&#  //                      /,                   ",
    "                                               #&#  #&%&(&%/./%&&(/.(&%#&&@* ,&&*                                               ",
    "                                              ,%/.     *&#/%%* *, /&#/%%.     .##.                                              ",
    "                                                         ./%&#,  *&&#*.                                                         ",
    "                                                           ,%/    (#                                                            ",
    "                                                              (&%*                                                              ",
    "                                                             .%#%/                                                              ",
    "                                                              .&#*/                                                             "
};


// Stores the credits
const char *credits[2] = {
    "A game by Michael Kiesling, recreated in C by Evan Werquin and Quentin Thouvier",
    "This game is licensed under the GNU General Public License v3.0"
};





// --- PROTOTYPES ---

// [TBM] = To be modified
// [TBR] = To be removed
// [TBD] = To be done
// [TBF] = To be fixed


// Toggles fullscreen mode
void toggleFullscreen();

// Clears the console [TBM]
void clearConsole();

// Places the console pointer at the given coordinates
void consolePointer(int x, int y);

// Changes the console text and background colors
void consoleColor(int color, int background);

// Prints the logo
void printLogo(int y);

// Prints the credits
void printCredits(int y);

// Prints the tile line
void printTileLine(int tile, int line);

// Prints the board [TBM]
void printPlayerBoard(int y, int board[5][5], int sideBoard[5][5]);



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
void consoleColor (int textColor, int backgroundColor)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, backgroundColor*16+textColor);
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
    consoleColor(15, 0);
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


// Prints the nth line of the mth tile
void printTileLine(int tile, int line) {
    printf("%s ", tileSprites[tile][line]);
}


// Prints the main board (the 5x5 matrix) from the matrix array using the printTileLine function
// This functions draws each line in 3 lines of characters
void printPlayerBoard(int y, int board[5][5], int sideBoard[5][5]) {

    int x = consoleWidth/2 - 85/2;

    // Prints the column numbers
    consolePointer(x+49, y);
    printf("1       2       3       4       5");
    consolePointer(x+49, y+1);
    printf("v       v       v       v       v");

    // Prints the board
    consolePointer(x, y+2);
    for (int i = 0; i < 5; i++) {
        printf("\n");
        for (int j = 0; j < 3; j++) {

            // Prints the row number
            if (j == 1) {
                printf("%d> ", i+1);
            }
            else {
                printf("   ");
            }

            // SIDE BOARD
            for (int k = 0; k < 5; k++) {
                // If the tile is 0, prints from the emptyTiles array
                if (sideBoard[i][k] == 0) {
                    if (emptySideBoardMatrix[i][k] == 0) {
                        printTileLine(16, j);
                    }
                    else {
                        printTileLine(0, j);
                    }
                }
                else {
                    printTileLine(sideBoard[i][k], j);
                }
            }

            // Prints arrows between the main board and the side board
            if (j == 1) {
                printf("-> ");
            }
            else {
                printf("   ");
            }

            // MAIN BOARD
            for (int k = 0; k < 5; k++) {
                // If the tile is 0, prints from the emptyTiles array
                if (board[i][k] == 0) {
                    printTileLine(emptyBoardMatrix[i][k]+5, j);
                }
                else {
                    printTileLine(board[i][k], j);
                }
            }

            printf("\n");
        }
    }
}