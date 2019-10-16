#ifndef LOGS_H
#define LOGS_H
#include <stdio.h>
#include "linked_list.h"
/* struct to hold turn-by-turn data such as player, move num in the game and
coords placed in */
typedef struct{
    int movenum;
    char player;
    int x;
    int y;
} MoveLog; /* MOVELOG STRUCT FOR TURN BASED DATA, position player and number */
/* struct to hold the logs for one game, containing linked list of all turns
that occur in the game and the number this game holds in this instance of
TicTacToe */
typedef struct{
    LinkedList* turnLogs;
    int gameno;
} GameLog; /* GAMELOG STRUCT FOR PER-GAME DATA, move logs and number of game */
/* struct to hold all logs for a particular instance of the program, contains
the settings and a linked list of all the game logs */
typedef struct{
    int m;
    int n;
    int k;
    LinkedList* gameLogs;
} Logs; /* LOGS STRUCT, settings, game collection, time initialised in menu */
Logs* createLogs(int,int,int);
void addGameLog(Logs*, GameLog*);
GameLog* createGameLog(int);
MoveLog* createMoveLog(int, int, int, int);
void addMoveLog(GameLog*, MoveLog*);
/* STARTER FUNCTIONS THAT LAUNCH THE FREE/PRINT CHAIN */
void freeAllLogs(Logs*);
void printAllLogs(Logs*);
/* FUNCTIONS FOR USE WITH LINKED LIST TO BE POINTED TO */
void freeGameLogs(void*);
void freeMoveLogs(void*);
void printGameLog(void*);
void printMoveLogs(void*);
#endif
