#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include "FileIO.h"
#include "gameEngine.h"
#include "logs.h"
#include "linked_list.h"
void viewLogs(LinkedList*, dataMan);
void displayBoard(int, int, char**);
void MainMenu(BoardSettings*);
void printMenu(void);
void clearInBuff(void);
#endif
