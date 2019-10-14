/*************************
* FILE INPUT AND OUTPUT
* Handles reading settings from and storing logs to a file.

* Author: Jeffrey Dugmore
* Student ID: 18816538

* Date Created: 29/09/2019
* Date Modified: 04/10/2019
************************/

#include "FileIO.h"


/******************
* loadSettings
* REQUIRES FREE
* Exports struct containing n, m & k parameters, ignoring case where each is
    defined as "=" no spaces to a positive integer.
* RETURNS NULL ON INVALID SETTINGS FILE - FORCES CORRECT FILE FORMAT
*****************/
BoardSettings* loadSettings(char* fileN)
{
    int inval, nval, mval, kval, nvalset, mvalset, kvalset, res, done;
    char inc;
    FILE* settings;
    BoardSettings* game = NULL;
    /* read in characters, using toUpper to guarantee upercase - making case
    * insensitive.
    * reading also requires the number to be valid i.e. positive integer
    */
    settings = fopen(fileN, "r");

    if(settings == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        done = 0;
        mvalset = 0;
        nvalset = 0;
        kvalset = 0;
        do /* until fscanf returns EOF */
        {
            res = fscanf(settings, "%c=%d%*[^\n]", &inc, &inval);
            if(res == 2) /* if read in correct amount of data */
            {
                inc = (char)toupper((int)inc);
                /* check inval to ensure its valid quantity */
                if(inval > 0)
                {
                    if(inc == 'M')
                    {
                        mval = inval;
                        mvalset += 1;
                    }
                    else if(inc == 'N')
                    {
                        nval = inval;
                        nvalset += 1;
                    }
                    else if(inc == 'K')
                    {
                        kval = inval;
                        kvalset += 1;
                    }
                    else
                    {
                        printf("Invalid setting detected: %c", inc);
                    }
                }
            }
            else if(res == EOF)
            {
                done = 1;
            }
            else
            {
                /* do nothing - ignore invalid bindings
                printf("Invalid line format found.\n"); */
            }
        }
        while(!done);

        if(ferror(settings))
        {
            perror("Error occured when attempting to read file");
        }
        fclose(settings);
        /* Once file is processed, verify data and return null if invalid */
        /* VERIFY SETTINGS DATA
        * ensure 1. all set 2. none are set more than once */
        if((mval != 0 && nval != 0 && kval != 0)
            && (mvalset == 1 && nvalset == 1 && kvalset == 1))
        {
            /* if valid populate struct values */
            game = (BoardSettings*)calloc(1,sizeof(BoardSettings));
            game->m = mval;
            game->n = nval;
            game->k = kval;
        }
        else
        {
            /* keep game as equal NULL and print problem */
            printf("Settings Error: Please ensure all setting values "
                    "are set and no duplicates exist.\n");
        }
    }
    return game;
}

/********************
* SAVE GAME LOG
* Responsible for saving all current logs to file
* Includes null handling
*/
void saveLogs(Logs* log)
{
    FILE* fileout;
    fileout = fopen(makeFileName(log), "w");
    if(fileout == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        int i, ii;
        GameLog* game;
        fprintf(fileout, "SETTINGS:\n    M: %d\n    N: %d\n    K: %d\n",
        log->m, log->n, log->k);
        if(log->gameLogs != NULL && log->gameLogs->count > 0)
        {
            for(i=0; i < getListLength(log->gameLogs); i++)
            {
                game = (GameLog*)accessNode(log->gameLogs, i);
                if(game!=NULL)
                {
                    fprintf(fileout, "Game %d\n", game->gameno);
                    for(ii=0; ii<getListLength(game->turnLogs); ii++) /* for
                        each game loop over and get all moves, printing them
                        to file */
                    {
                        MoveLog* move = NULL;
                        move = (MoveLog*)accessNode(game->turnLogs, ii);
                        if(move!=NULL) /* guard against invalid writes */
                        {
                            fprintf(fileout, "    Turn: %d\n    Player: %c\n"
                            "    Location: %d,%d\n\n", move->movenum,
                            move->player, move->x, move->y);
                        }
                    }
                }
            }
        }
        else
        {
            fprintf(fileout, "\nNo games found.");
        }

    }
    if(ferror(fileout))
    {
        perror("Error writing logs");
    }
    fclose(fileout);

}
/***********
Takes a game log and makes equivilent file name for that log.
* Responsible for creating filename in correct format:
    MNK_<M>-<N>-<K>_<HOUR>-<MIN>_<DAY>-<MONTH>.log
* Time corresponds file creation time
* May reqiure limit on m n and k values
*/
char* makeFileName(Logs* log)
{
    int dayn, month, min, hour;
    time_t rawt = time(NULL);   /*time(NULL) From https://stackoverflow.com/
    questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
                                  answered Sep 18 '09 at 0:58
                                  By Adam Rosenfield */
    struct tm *localtnow;
    char *namebuf = (char*)calloc(40, sizeof(char));
    localtnow = localtime(&rawt);

    dayn=localtnow->tm_mday;
    month=localtnow->tm_mon + 1;
    min=localtnow->tm_min;
    hour=localtnow->tm_hour;

    sprintf(namebuf, "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", log->m, log->n,
    log->k,hour,min,dayn,month);

    return namebuf;
}
