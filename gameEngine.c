/**************************
* GAME ENGINE 
* Controls game dynamics, 
*
* Author: Jeffrey Dugmore
* Date Created: 29/09/2019
* Date Modified: 04/10/2019
*TODO: 1. checkwin - win condition 
2. input will accept more than 2 coordinates (x,y,z) - fix with get
* Known Issues: reading extra line on input of getCorrds() results in error msg
being printed.
*************************/

#include "gameEngine.h"
/* Static Definitions */
static int numLinedUpY(int**, int, int, int, int); 
static int numLinedUpX(int**, int, int, int, int); 
static int numLinedUpDiagon(int**, int, int, int, int); 
static int numLinedUpDiagonFlip(int**, int, int, int, int); 
static int numLinedUpYNeg(int**, int, int, int, int); 
static int numLinedUpXNeg(int**, int, int, int, int); 
static int numLinedUpDiagonNeg(int**, int, int, int, int); 
static int numLinedUpDiagonFlipNeg(int**, int, int, int, int); 

/*
* Calls initialise to recieve fresh game board (2D array of zeros)
* Uses UI printBoard() with graphics parameter to display game state
* Creates a game log
*/

GameLog* runGame(int m, int n, int k, int gamenum)
{
    /* gamenum tracks game number in this program run */
    static int turncount = 0; /* tracks turns, initialised each game */
    int x, y, gameover;
    int **board;
    GameLog* thisGame = NULL;
    board = initialiseGame(m, n);
    thisGame = createGameLog(gamenum); /* create gamelog when board 
                                                succesfully set up */
     
    printf("===== WELCOME TO TICTACTOE =====\n");
    /* Use while !complete loop and use if win to complete condition 
    *   will use X's as first turn as this is how i've always played - 
    *   much like chess.
    */
    gameover = 0;
    do
    {
        if(!gameover)
        {
            system("clear");
            displayBoard(m, n, graphics(board, m ,n)); /* display the board of
                     its size using graphical representaion with X's and Os' */
            printf("Player 1 - X's Turn:");
            getCoords(&x, &y, m, n);
            while(playerMove(board, 1, x, y, thisGame, turncount) 
                    == 1)
            {
                getCoords(&x, &y, m ,n);
            }
            gameover = checkWin(board, m , n, k, x ,y);
        }   
        if(!gameover)
        {
            system("clear");
            displayBoard(m, n, graphics(board, m ,n));
            printf("Player 2 - O's Turn:");
            getCoords(&x, &y, m, n);
            while(playerMove(board, 2, x, y, thisGame, turncount) 
                == 1) /* on error get new coords*/
            {
                getCoords(&x, &y, m, n);
            }
            gameover = checkWin(board, m, n, k, x, y);
        }
    }
    while(!gameover);
    if(gameover == 1)
    { /* X's win */
        
    }
    else if(gameover == 2)
    { /* O's win */
        
    }
    else
    { /* DRAW */
        
    }
    free(board);
    clearInBuff();
    printf("Press Enter to continue...");
    getchar();
    return thisGame;
}
/********
* Gets User input, sanitised and within range
* Returns via pointers
*/
void getCoords(int* x, int* y, int width, int height)
{
    char line[MAX_TERM_LINE];
    int xtemp, ytemp, num;
    static int tries = 0;
    int done = 0;
    /*fgets(line, MAX_TERM_LINE, stdin);*/
    do
    {
        clearInBuff();
        printf("\n\tCoordinates: ");
        fgets(line, MAX_TERM_LINE, stdin); 
        num = sscanf(line, " (%d,%d) ", &xtemp, &ytemp);
        if(xtemp < width && xtemp >= 0 && ytemp < height && ytemp >= 0 && 
            num == 2) 
        /* within range - no negatives, within the confines of the board and
         only 2 coords provided */
        {
            *x = xtemp;
            *y = ytemp;
            done = 1;
        }
        else
        {   
            tries++;
            printf("Invalid coordinates, try again.\n");
            if(tries > 2 && tries < 5)
            {   
                printf("Hint: use the form (x,y)\n");
            }
            if(tries == 5)
            {
                printf("Have you tried using the brackets...\n");
            }
            if(tries == 7)
            {
                printf("Have you tried switching it off and on again...\n");
            }
            if(tries == 8)
            {
                printf("I'm sorry that last comment was a little sarcastic,"
                " just try your best.\n");
            }
            if(tries == 9)
            {
                printf("You got this, just focus on the board.\n");
            }
            if(tries==10)
            {
                printf("I take it back, 10 failed entries is ghastly...");
            }
        }   
    }
    while(!done);
}
/*******
* Handles the actual user inputted coordinates, places a distinct number in 
    location to be translated later by graphics function.
* If could not place (occupied) then returns 1 (issue arose)
* x and y already sterilised input || X = Width Y = Height
* includes creation of corersponding move log
*/
int playerMove(int** board, int player, int x, int y, GameLog* game,
                 int turnno)
{
    int issue;
    if(board[x][y] == 0)
    {
        board[x][y] = player;
        turnno++;
        addMoveLog(game,createMoveLog(turnno,player,x,y));/*log if successful 
                                                                        turn*/
        issue = 0;
    }
    else
    {
        printf("Cannot select a filled tile.\n");
        issue = 1;
    }
    return issue;
}

/********
* Checks the state of the board and determines if a win has occurred, if yes
    return the player who won (1 or 2 or 3 for draw), 
        otherwise return 0 - in progress
* [0][i] y axis check TODO
* [i][0] x axis check TODO
* [i][i] Diagonal check TODO
* Direction is relative to 2D array not board display where up would be lower 
on the screen.
* returns number found in line (k)
*/
int checkWin(int** arr, int w, int h, int k, int posx, int posy)
{
    int numel, temp;
    if(posx < w && posy < h && posx >= 0 && posy >= 0) /*within bounds - each 
    func has bound checks also */
    {
        /* RECURSIVE METHODS */
        temp = numLinedUpY(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpYNeg(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpX(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpDiagon(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpDiagonFlip(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
      
        temp = numLinedUpXNeg(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpDiagonNeg(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
        temp = numLinedUpDiagonFlipNeg(arr, w, h, posx, posy);
        if(temp == k)
        {
            numel = temp;
        }
    }
    return numel;
}
/***************** TODO determine true directions
* Positive Direction Counters
* Determine how many matching elements lined up in positive x y and xy directi-
-ons
* Recursively used via numLinedUp wrapper method
*/
static int numLinedUpY(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(ii+1 < h)
    {
        if(arr[i][ii] == arr[i][ii+1]) /* y axis condition */
        {
            num += numLinedUpY(arr, w, h, i, ii+1);
        }
        else
        {
            num = 1;
        }   
    }
    else
    {
        num = 1;
    }
    return num;

 }

static int  numLinedUpX(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i+1 < w)
    {
        if(arr[i][ii] == arr[i+1][ii]) /* try up */
        {
            num += numLinedUpX(arr, w, h, i+1, ii);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}

static int numLinedUpDiagon(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i+1 < w && ii+1 < h)
    {
        if(arr[i][ii] == arr[i+1][ii+1])
        {
            num += numLinedUpDiagon(arr, w, h, i+1, ii+1);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}

static int numLinedUpDiagonFlip(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i-1 >= 0 && ii+1 < h)
    {
        if(arr[i][ii] == arr[i-1][ii+1]) /* Recurse in negative x and pos y */
        {
            num += numLinedUpDiagonFlip(arr, w, h, i-1, ii+1);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}


/*****************
* Negative Direction Counters
* Determine how many matching elements are lined up in an -x, -y and -xy direc-
tion
* Recursively used via numLinedUp wrapper method
*/
static int numLinedUpYNeg(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(ii-1 >= 0)
    {
        if(arr[i][ii] == arr[i][ii-1])
        {
            num += numLinedUpYNeg(arr, w, h, i, ii-1);
        }
        else
        {
            num = 1;
        }   
    }
    else
    {
        num = 1;
    }
    return num;

 }

static int  numLinedUpXNeg(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i-1 > 0)
    {
        if(arr[i][ii] == arr[i-1][ii])
        {
            num += numLinedUpXNeg(arr, w, h, i-1, ii);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}

static int numLinedUpDiagonNeg(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i-1 >= 0 && ii-1 >= 0)
    {
        if(arr[i][ii] == arr[i-1][ii-1])
        {
            num += numLinedUpDiagonNeg(arr, w, h, i-1, ii-1);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}

static int numLinedUpDiagonFlipNeg(int** arr, int w, int h, int i, int ii)
{
    int num = 0;
    if(i+1 < w && ii-1 >= 0)
    {
        if(arr[i][ii] == arr[i+1][ii-1]) /* Recurse in pos x and neg y */
        {
            num += numLinedUpDiagonFlipNeg(arr, w, h, i+1, ii-1);
        }
        else
        {
            num = 1;
        }
    }
    else
    {
        num = 1;
    }
    return num;
}




/*********
* Takes a 2D array and converts it to a displayable 2D char array wherein
* 0's are converted to empty spaces, 1 are converted to X's and 2's are convert
-ed to O's
* For use with UserInterface displayBoard() func
* REQUIRES FREE
*/
char** graphics(int** gameState, int width, int height)
{   
    int i, ii;
    char** board = (char**)calloc(width, sizeof(char*));
    for(i=0; i < width; i++)
    {
        board[i] = (char*)calloc(height, sizeof(char));
    }
    for(ii=0; ii < width; ii++)
    {
        for(i=0; i<height;i++) /* converts the array to 1=X 2=O else=space*/
        {
            if(gameState[ii][i] == 1)
            {
                board[ii][i] = 'X';
            }
            else if(gameState[ii][i] == 2)
            {
                board[ii][i] = 'O';
            }
            else
            {
                board[ii][i] = ' ';
            }
        }
    }
    return board;
}
/****************
* Creates the game using the settings from file 
* Responsible for setting up the board
* REQUIRES FREE
*/
int** initialiseGame(int m, int n)
{
    
    /*Use a 2D array to store gamestate - where X's and O's are (1 or 2 
    respectvely) - O(1) access time faster read, no shuffling required
    and set amount of space (area of board n * m)
    Width = m | Height = n
    */
    int i;
    int** gameState = (int**)calloc(m, sizeof(int*)); /* use calloc to 
                                initialise unused values to 0 (unused state) */
    for(i=0; i < m; i++) /* potentially non contiguous */
    {
        gameState[i] = (int*)calloc(n, sizeof(int));
    } 
    return gameState;      
}

