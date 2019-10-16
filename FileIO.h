#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "logs.h"
/* struct to hold board settings allowing returning of all values required */
typedef struct BoardSettings{
    int m; /* width */
    int n; /* height */
    int k; /* win condition - # of mathcing tiles to win */
} BoardSettings;
BoardSettings* loadSettings(char* filename);
void saveLogs(Logs*);
char* makeFileName(Logs*);
#endif
