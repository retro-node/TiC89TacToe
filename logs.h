#ifndef LOGS_H
#define LOGS_H
#include <stdio.h>
#include <time.h>
#include "linked_list.h"
typedef struct{
    int min;
    int hour;
    int dayn;
    int month;
} Time; /* To store time that the game occurred for later processing */
typedef struct{
    int movenum;
    char player;
    int x;
    int y;
} MoveLog; /* MOVELOG STRUCT FOR TURN BASED DATA, position player and number */
typedef struct{
    LinkedList* turnLogs;
    int gameno;
} GameLog; /* GAMELOG STRUCT FOR PER-GAME DATA, move logs and number of game */
typedef struct{
    int m;
    int n;
    int k;
    Time* Time;
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
