#include <stdlib.h>
#include <stdio.h>
#include "chords.h"
#include "random.h"
#include "dsp.h"
#include "typedefs.h"

note g_sawData;
note g_squData;
note g_outData;

chord g_first;
chord g_second;
chord g_third;
chord g_fourth;
chord g_fifth;
chord g_sixth;
chord g_seventh;
chord g_eighth;
chord *g_chord;

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
int getNextChord(int currChord)
{
    int tmp;
    int per;
    switch(currChord)
    {
        case 1:
            tmp=getRandNum(1,100);
            per=10;
            if(tmp<=per)
                return 2;
            per+=15;
            if(tmp<=per)
                return 3;
            per+=25;
            if(tmp<=per)
                return 4;
            per+=25;
            if(tmp<=per)
                return 5;
            per+=10;
            if(tmp<=per)
                return 6;
            //7 has 15% chance
            return 7;
        case 2:
            tmp=getRandNum(1,100);
            per=25;
            if(tmp<=per)
                return 1;
            per+=50;
            if(tmp<=per)
                return 5;
            //7 has 25% chance
            return 7;
        case 3:
            tmp=getRandNum(1,100);
            per=20;
            if(tmp<=per)
                return 2;
            per+=40;
            if(tmp<=per)
                return 4;
            //6 has 4% chance
            return 6;
        case 4:
            tmp=getRandNum(1,100);
            per=35;
            if(tmp<=per)
                return 1;
            per+=10;
            if(tmp<=per)
                return 2;
            per+=35;
            if(tmp<=per)
                return 5;
            //7 has 15% chance
            return 7;
        case 5:
            tmp=getRandNum(1,100);
            per=49;
            if(tmp<=per)
                return 1;
            //6 has a 51% chance
            return 6;
        case 6:
            tmp=getRandNum(1,100);
            per=50;
            if(tmp<=per)
                return 2;
            //4 has 50% chance
            return 4;
        case 7:
            tmp=getRandNum(1,100);
            per=20;
            if(tmp<=per)
                return 1;
            //6 has 80% chance
            return 6;
    }
    fprintf(stderr, "ERROR! Invalid input to getNextChord!\n");
    return 1;
}

void updateNexts(int *nChord, int *nChordCount, int *nInver)
{
    int tmp;
    *nChord=getNextChord(*nChord);
    *nChordCount=getRandNum(3,10);
    *nInver=getRandNum(1,3);
}

void initInversionNotes(chord *data, inversionType type, float base, float third, float fifth)
{
    switch(type)
    {
        case ROOTPOS:
            data->rootPos.n_base=base;
            data->rootPos.n_third=third;
            data->rootPos.n_fifth=fifth;
        break;
        case FIRSTINV:
            data->firstInv.n_base=base;
            data->firstInv.n_third=third;
            data->firstInv.n_fifth=fifth;
        break;
        case SECONDINV:
            data->secondInv.n_base=base;
            data->secondInv.n_third=third;
            data->secondInv.n_fifth=fifth;
        break;
        default:
            fprintf(stderr,"ERROR: invalid inversionType in initInversionNotes!\n");
        break;
    }
}

void setChordInversion(chord *data, inversionType type)
{
    switch(type)
    {
        case ROOTPOS:
            setFreq(&(data->base),data->rootPos.n_base);
            setFreq(&(data->third),data->rootPos.n_third);
            setFreq(&(data->fifth),data->rootPos.n_fifth);
        break;
        case FIRSTINV:
            setFreq(&(data->base),data->firstInv.n_base);
            setFreq(&(data->third),data->firstInv.n_third);
            setFreq(&(data->fifth),data->firstInv.n_fifth);
        break;
        case SECONDINV:
            setFreq(&(data->base),data->secondInv.n_base);
            setFreq(&(data->third),data->secondInv.n_third);
            setFreq(&(data->fifth),data->secondInv.n_fifth);
        break;
        default:
            fprintf(stderr,"ERROR: invalid inversionType in setChordInversion!\n");
        break;
    }
}

void initChords()
{
    //First chord init
    initNote(&(g_first.base), g_sineWave); 
    initNote(&(g_first.third),  g_sineWave); 
    initNote(&(g_first.fifth), g_sineWave);

    initInversionNotes(&g_first, ROOTPOS, Bb1, D1, F1);
    initInversionNotes(&g_first, FIRSTINV, F0, Bb1, D1);
    initInversionNotes(&g_first, SECONDINV,  D0, F0, Bb1);
    
    setChordInversion(&g_first, ROOTPOS);

    //Second chord init
    initNote(&(g_second.base), g_sineWave); 
    initNote(&(g_second.third),  g_sineWave); 
    initNote(&(g_second.fifth), g_sineWave);

    initInversionNotes(&g_second, ROOTPOS, C1, Eb1, G1);
    initInversionNotes(&g_second, FIRSTINV, G0, C1, Eb1);
    initInversionNotes(&g_second, SECONDINV, Eb0, G0, C1); 
    
    setChordInversion(&g_second, ROOTPOS);

    //Third chord init
    initNote(&(g_third.base), g_sineWave); 
    initNote(&(g_third.third),  g_sineWave); 
    initNote(&(g_third.fifth), g_sineWave);

    initInversionNotes(&g_third, ROOTPOS, D1, F1, A1);
    initInversionNotes(&g_third, FIRSTINV, A0, D1, F1);
    initInversionNotes(&g_third, SECONDINV, F0, A0, D1);
    
    setChordInversion(&g_third, ROOTPOS);

    //Fourth chord init
    initNote(&(g_fourth.base), g_sineWave); 
    initNote(&(g_fourth.third),  g_sineWave); 
    initNote(&(g_fourth.fifth), g_sineWave);

    initInversionNotes(&g_fourth, ROOTPOS, Eb1, G1, Bb2);
    initInversionNotes(&g_fourth, FIRSTINV, Bb1, Eb1, G1);
    initInversionNotes(&g_fourth, SECONDINV, G0, Bb1, Eb1);
    
    setChordInversion(&g_fourth, ROOTPOS);

    //Fifth chord init
    initNote(&(g_fifth.base), g_sineWave); 
    initNote(&(g_fifth.third),  g_sineWave); 
    initNote(&(g_fifth.fifth), g_sineWave);

    initInversionNotes(&g_fifth, ROOTPOS, F1, A1, C2);
    initInversionNotes(&g_fifth, FIRSTINV, C1, F1, A1);
    initInversionNotes(&g_fifth, SECONDINV, A0, C1, F1);
    
    setChordInversion(&g_fifth, ROOTPOS);

    //sixth chord init
    initNote(&(g_sixth.base), g_sineWave); 
    initNote(&(g_sixth.third),  g_sineWave); 
    initNote(&(g_sixth.fifth), g_sineWave);

    initInversionNotes(&g_sixth, ROOTPOS, G1, Bb2, D2);
    initInversionNotes(&g_sixth, FIRSTINV, D1, G1, Bb2);
    initInversionNotes(&g_sixth, SECONDINV, Bb1, D1, G1);
    
    setChordInversion(&g_sixth, ROOTPOS);

    //Seventhchord init
    initNote(&(g_seventh.base), g_sineWave); 
    initNote(&(g_seventh.third),  g_sineWave); 
    initNote(&(g_seventh.fifth), g_sineWave);

    initInversionNotes(&g_seventh, ROOTPOS, A1, C2, Eb2);
    initInversionNotes(&g_seventh, FIRSTINV, Eb1, A1, C2);
    initInversionNotes(&g_seventh, SECONDINV, C1, Eb1, A1);
    
    setChordInversion(&g_seventh, ROOTPOS);

}

void initNote(note *data, float *type)
{
    data->lVal=0;
    data->rVal=0;
    setFreq(data, 0);
    data->pos=0;
    data->waveTable=type;
}

