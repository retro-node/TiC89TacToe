/***************************
* LOGS
* Manages logfile creation, display and free functions for LinkedList to point
to. Uses Linked List DS to hold logs within a GameLog struct

* Author: Jeffrey Dugmore
* Student ID: 18816538
* Date Created: 01/10/2019
* Date Modified: 03/10/2019
* ISSUES: typecase wasnt working on 1 line self = (struct*)self, had to
    impliment a copy and free and continued using the copied casted variable.
* SUSPECTED: copy typecase causing linked list to be uninitialsized.
*****************************/

#include "logs.h"

/************
* Most essential log method, creation of the struct to hold all logs of run
as more than one game can be played per run.
* REQUIRES FREE & sanitized parameters
*/
Logs* createLogs(int m, int n, int k)
{
    Logs* ThisRun = NULL;

    /* creates logs struct */
    ThisRun = (Logs*)calloc(1, sizeof(Logs));
    ThisRun->m = m;
    ThisRun->n = n;
    ThisRun->k= k;
    ThisRun->gameLogs = createLinkedList();
    return ThisRun;
}
/*
* ACCESSOR METHOD to avoid redundant imports
*/
void addGameLog(Logs* all, GameLog* thisGame)
{
    insertLast(all->gameLogs, thisGame);
}
/***********
* Allocates space for GameLog
* Returns LL of logsa
* REQUIRES FREE
*/
GameLog* createGameLog(int gameno)
{
    GameLog* game = (GameLog*)calloc(1, sizeof(GameLog));
    game->gameno= gameno;
    game->turnLogs = createLinkedList();
    return game;
}
/*********
* Creates move log struct
* Converts player to character representation 1=X 2=O

* REQUIRES FREE IN FREE LL FUNCTION
* Takes: destination LL to add to, what turn, which player and coords x & y
*/
MoveLog* createMoveLog(int turnNo, int player, int x, int y)
{
    MoveLog* moveLog = (MoveLog*)calloc(1,sizeof(MoveLog));
    char playerChar;
    if(player == 1)
    {
        playerChar = 'X';
    }
    else
    {
        playerChar = 'O';
    }
    moveLog->movenum = turnNo;
    moveLog->player = playerChar;
    moveLog->x= x;
    moveLog->y= y;
    return moveLog;
}

/********
* Adds to MoveLog to turnLogs Linked list in GameLog using insertLast to keep chronology
*/
void addMoveLog(GameLog* gamelog, MoveLog* movelog)
{
    insertLast(gamelog->turnLogs, movelog);
}
/*************
* Frees all Game logs, move logs freed first via the freeGameLogs func
* Starts free chain Logs --> gameLogs --> turnLogs then free against arrows
*/
void freeAllLogs(Logs* all)
{
    freeLinkedList(all->gameLogs, freeGameLogs);
    free(all);
}

/************
* Describes to LL how to free game logs
* first free MoveLogs from logs LL, then free itself
*/
void freeGameLogs(void* games)
{
    GameLog* gamesL = NULL;
    gamesL = (GameLog*)games; /* copy typecast */
    freeLinkedList(gamesL->turnLogs, freeMoveLogs);
    free(gamesL);
}
/***************
* For use with freeLinkedList() and printLinkedList() as function to point to,
free logs required on program exit.
* If not saved will be lost, only free the data
* REQUIRES LINKED LIST
*/

void freeMoveLogs(void* logs)
{
    free(logs);
}
/***********
* Prints entire Logs struct including all games
* Prints all gameLogs by --> GameLog --> MoveLog so that MoveLogs are printed
last of all
*/
void printAllLogs(Logs* all)
{
    printf("\nSETTINGS:\n\tM: %d\n\tN: %d\n\tK: %d\n", all->m, all->n, all->k);
    if(all->gameLogs->count > 0)
    {
        printLinkedList(all->gameLogs, printGameLog);
    }
    else
    {
        printf("No games found.\n");
    }
}
/********
* Prints out all atributes of all logs prefixed by the game settings
*/
void printGameLog(void* glog) /* TODO: turnlogs causing error as count
 unreachable when it should be - possible loss of data when copy typecasted?*/
{
    if(glog!=NULL)
    {
        GameLog* glogG = NULL;
        glogG = (GameLog*)glog; /* typecast, copy then free original */
        printf("GAME %d:",/*(GameLog*)glog->gameno-doesnt work*/glogG->gameno);
        if(glogG->turnLogs->count > 0) /* turnLogs is uninitialised*/
        {
            printLinkedList(glogG->turnLogs, printMoveLogs);
        }/* possible memory leak - TODO VERIFY */
    }
    else
    {
        printf("Games not found.\n");
    }
}

/*********
* Prints each move from GameLog linked list in format
Turn: n
Player: X or O
Location: x,y
*/
void printMoveLogs(void* logs)
{
    if(logs!= NULL)
    {
        MoveLog* logsm = NULL;
        logsm = (MoveLog*)logs; /* copy typecast */
        printf("\n\tTurn: %d", logsm->movenum);
        printf("\n\tPlayer: %c", logsm->player);
        printf("\n\tLocation: %d,%d\n", logsm->x, logsm->y);
    } /* possible memory leak - TODO VERIFY */
}
