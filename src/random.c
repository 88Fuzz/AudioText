#include <stdlib.h>
#include <stdio.h>
#include "random.h"

/*
 *  based off this webpage
 *  http://globalguitarnetwork.com/wp-content/uploads/2014/05/Chord-Motion_Major-Key.png
 *
 *
 *   I   ->  ii, iii, IV, V, vi, vii
 *   ii  ->  I, V, vii
 *   iii ->  ii, IV, vi
 *   IV  ->  I, ii, V, vii
 *   V   ->  I, vi
 *   vi  ->  ii, IV
 *   vii ->  I, vi
 */






 //make 7 not so frequentm 7 to 6 sounds really good
int getNextChord(int currChord)
{
    switch(currChord)
    {
        case 1:
            return getRandNum(2,7);
        case 2:
            switch(getRandNum(1,3))
            {
                case 1:
                    return 1;
                case 2:
                    return 5;
                case 3:
                    return 7;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 2;
        case 3:
            switch(getRandNum(1,3))
            {
                case 1:
                    return 2;
                case 2:
                    return 4;
                case 3:
                    return 6;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 3;
        case 4:
            switch(getRandNum(1,4))
            {
                case 1:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 5;
                case 4:
                    return 7;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 4;
        case 5:
            switch(getRandNum(1,2))
            {
                case 1:
                    return 1;
                case 2:
                    return 6;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 5;
        case 6:
            switch(getRandNum(1,2))
            {
                case 1:
                    return 2;
                case 2:
                    return 4;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 6;
        case 7:
            switch(getRandNum(1,2))
            {
                case 1:
                    return 1;
                case 2:
                    return 6;
            }
            fprintf(stderr, "ERROR! Unexpected return from getRanNum\n");
            return 7;
    }
    fprintf(stderr, "ERROR! Invalid input to getNextChord!\n");
    return 1;
}

int getRandNum(int min, int max)
{
    double randNum = myRand()/(1.0 + RAND_MAX); 
    int range = max - min + 1;
    return (randNum*range) + min;
}

int myRand()
{
    return rand();
}

void updateNexts(int *nChord, int *nChordCount)
{
   *nChord=getNextChord(*nChord);
   *nChordCount=getRandNum(3,10);
   printf("\nnChord: %d changes in %d\n", *nChord, *nChordCount);
}
