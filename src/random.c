#include <stdlib.h>
#include <stdio.h>
#include "random.h"

int g_seed;

int getRandNum(int min, int max)
{
    int tmp = myRand()&0xFFFFu; 
    double randNum=(double)tmp/(0xFFFFu);
    int range = max - min + 1;
    return (randNum*range) + min;
}

int myRand()
{
    int tmp=g_seed;
    int lsb;

    do
    {
        lsb=g_seed&1;
        g_seed >>= 1;
        if(lsb)
            g_seed ^=0xB400u;
    }while(tmp==g_seed);

    return g_seed;
}
