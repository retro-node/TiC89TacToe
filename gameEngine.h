#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <stdio.h>
#include <stdlib.h>
#include "UserInterface.h"
#include "logs.h"
#define MAX_TERM_LINE 8
/* Func pointer for use with determining if a win occurs, each direction Takes
same parameters so a func ptr is applicable with the assignment occuring in an
if statement in the engine */
typedef int (*numLinedUp)(int **, int , int, int, int);
GameLog* runGame(int, int, int, int);
int playerMove(int**, int, int, int, GameLog*, int);
int checkWin(int**, int, int, int, int, int);
void getCoords(int*, int*, int, int);
char** graphics(int**, int, int);
int** initialiseGame(int, int);
#endif
