/******************
* UserInterface
* Responsibile for displaying menu, accessing options, displaying logs and game
    board

* Author: Jeffrey Dugmore
* Date Created: 29/09/2019
* Date Modified: 04/10/2019
* TODO add system("clear")
* Issues: clearInBuff() causes program pause - one too many getchar() calls?
*****************/

#include "UserInterface.h"

/**********
*  DRIVER CODE
* ENSURES CORRECT AMOUNT OF PARAMETERS, LAUNCHES MENU, PRINTS USAGE
*/
int main(int argc, char* argv[])
{
    if(argc == 2) /* do program otherwise display usage */
    {
        BoardSettings* gameSettings = NULL;
        gameSettings = loadSettings(argv[1]); /* returns null if invalid file */
        MainMenu(gameSettings);
    }
    else
    {
        printf("Usage: ./TicTacToe [Filename]\n\t [Filename] - Name of"
                " settings file to use for this game.\n");
    }
    return 0;
}

/****************
* Uses gameEngine state of board that has been converted for display
* Prints out the board state to terminal
* FULFULS FREE OF char** 
*/
void displayBoard(int width, int height, char** state)
{
    int i, ii, iii;
    for(ii=0; ii < width; ii++) /* header divider */
    {
        printf("||===");
    }
    printf("||\n");
    for(iii=0; iii < height; iii++) 
    {
        printf("|");
        for(i=0; i < width; i++)
        {
            printf("| %c |", state[i][iii]); /* the cell */
        }
        printf("|\n");
        for(ii=0; ii < width; ii++) /* create a row divider after cells */
        {
            printf("||==="); 
        }
        printf("||\n"); /* end of row divider */
    }
    for(i=0; i < width; i++) /*free gamestate as it will be generated again*/
    {
        free(state[i]);
    }
    free(state);
}

/****************
* Uses gameEngine printLogs as function pointer to print the logs
* Prints out the linked list of logs to terminal
* MOVED TO LOGS.C AS NOT PARTICULARLY UI's JURISDICTION
void viewLogs(Logs* logs)
{
    printLinkedList(logs->gameLogs, printAllLogs);
}
*/
/******************
* MAIN MENU
* Holds options and calls all starter methods
* Displays options and validates input, only launches if gameSettings are valid
* 
*/

void MainMenu(BoardSettings* gameSettings)
{
    if(gameSettings != NULL) /* no else required as loadSettings prints */
    {
        int done, option;
        char menuselect[1];
        int *m, *n, *k;
        /* continue using settings */
        Logs* logs = NULL;
        GameLog* gamelog = NULL;
        static int gamenum = 1;
        m = &(gameSettings->m);
        n = &(gameSettings->n);
        k = &(gameSettings->k);
        logs = createLogs(*m, *n, *k);/* to be used in this run of program */
        printMenu();
        done = 0;
        do
        {
            /* printMenu(); */
            printf("\n\t\t\tOption: ");
            scanf("%s", &menuselect[0]);
            option = atoi(menuselect);
            switch(option) /* KEEP 0 CLEAR AS IF NOT VALID ATOI WILL RETURN 0*/
            {
                case 1:
                    gamelog = runGame(*m, *n, *k, gamenum);
                    if(gamelog != NULL) /* lodge the log if its valid */
                    {
                        addGameLog(logs, gamelog);
                    }
                    gamenum++;
                    printMenu();
                    break;
                case 2:
                    printf("=========== SETTINGS ============\n"
                        "Width [M]: %d\nHeight [N]: %d\nTiles to Win [K]: %d\n"
                        ,*m,*n,*k);
                   break;
                case 3:
                    printAllLogs(logs);        
                    break;
                #ifndef SECRET
                case 4:
                    if(logs != NULL)
                    {
                        if(logs->gameLogs != NULL)
                        {
                            printf("Saving Logs...\n");
                            saveLogs(logs);
                            printf("Done.\n");
                        }
                        else
                        {
                            printf("No game logs to save.");
                        }
                    }
                    else
                    {
                        printf("Error in saving logs.");
                    }
                    break;
                #endif
                #ifdef EDITOR    
                case 5: /* Assumes know what doing, no rigorous sanitation */
                    printf("=============EDIT SETTINGS=============\nNew Width"
                    " [M]: ");
                    scanf("%d", m);
                    printf("New Height [N]: ");
                    scanf("%d", n);
                    printf("New Tiles to Win [K]: ");
                    scanf("%d", k);
                    break;
                #endif
                case 9:
                    printf("Thanks for playing!\n=============Goodbye===="
                    "=========\n");
                    done = 1;
                    break;
                case 0: 
                    printf("Invalid option.\n");
                    break;
                default:
                    printf("Option not avaliable.\n"); /* Displays when a valid
                                    entry that is not being used is selected */
                    break;
            }
        }
        while(!done);
        /* Clean up of logs and settings structs on program exit*/
        freeAllLogs(logs);
        free(gameSettings);
    }
}
void printMenu(void)
{
        printf("\n=========== MAIN MENU ===========\n\t[1]- New Game\n\t"
            "[2]- View Settings\n\t[3]- View Logs\n\t");               
        #ifndef SECRET
            printf("[4]- Save Logs to File\n\t");
        #endif
        #ifdef EDITOR
            printf("[5]- Edit M, N & K\n\t");
        #endif
            printf("[9]- Exit\n");
 }

/***********
* Method to clear input buffer from:
https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
Accessed at 19:55 04-10-2019
* Utilised the clear buffer code and placed in method for easier use
* Causes apparent pause 
*/
void clearInBuff(void)
{
    printf("\nPress enter to continue...");
    while(getchar()!='\n'); /* preferred as not undefined by c standard as 
                            fflush(stdin); is */
    printf("\n");
}   
