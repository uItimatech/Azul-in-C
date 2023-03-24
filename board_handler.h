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

void clearConsole();

void printEmptyLines(int lines);

void printLogo(int displacement);

void printCredits();

void printTileLine(int tile, int line);

void printPlayerBoard(int board[5][5], int sideBoard[5][5]);

// --- CONSOLE AND DISPLAY FUNCTIONS ---

// Clears the console using adequate commands for Windows and Linux
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// Prints empty lines
void printEmptyLines(int lines) {
    for (int i = 0; i < lines; i++) {
        printf("\n");
    }
}


// Prints the logo line by line
void printLogo(int displacement) {  
    for (int i = 0; i < 35; i++) {

        // Prints the displacement
        for (int i = 0; i < displacement; i++) {
        printf(" ");
        }

        // Prints the line
        printf("%s\n", logoSprite[i]);
    }
}


// Prints the credits
void printCredits() {
    printf("%s\n", credits[0]);
    printf("%s\n", credits[1]);
}


// Prints the nth line of the mth tile
void printTileLine(int tile, int line) {
    printf("%s ", tileSprites[tile][line]);
}


// Prints the main board (the 5x5 matrix) from the matrix array using the printTileLine function
// This functions draws each line in 3 lines of characters
void printPlayerBoard(int board[5][5], int sideBoard[5][5]) {

    // Prints the column numbers
    printf("                                                 1       2       3       4       5");
    printf("\n                                                 v       v       v       v       v");

    // Prints the board
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