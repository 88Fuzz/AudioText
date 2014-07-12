#include <stdlib.h>
#include <stdio.h>
#include "portaudio.h"
#include "dsp.h"
#include "random.h"
#include "typedefs.h"



int main(int argc, char *argv[])
{
    PaStream *stream;
    PaError err;
    int chordCount=0;
    int nChordCount=0;
    int nChord=1;
    int nInver=1;
    int delay;
    int seed=0;
    float delayMult=1;
    char c;

    initNote(&g_sawData, g_sawWave);
    initNote(&g_squData, g_squWave);
    initNote(&g_outData, NULL);

    initChords();
    g_chord=&(g_first);

    if(argc!=3)
    {
        printf("Usage: %s <input file> <amount of time a note is played>\n",argv[0]);
        return 1;
    }

    delay=atoi(argv[2]);

    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL)
        return 1;


    if((err=Pa_Initialize()) != paNoError)
    {
        getErrorMsg(err);
        return 1;
    } 

    err=Pa_OpenDefaultStream( &stream, 0, 2, paFloat32, SAMPLE_RATE, 256, generateAudio, &g_outData);

    if(err != paNoError)
    {
        getErrorMsg(err);
            return 1;
    }
    if((err=Pa_StartStream(stream)) != paNoError)
    {
        getErrorMsg(err);
        return 1;
    }

    if((c=fgetc(fp))!=EOF)
    {
        seed=c*14*c;
    printf("SEED %d\n", seed);
        if((c=fgetc(fp))!=EOF)
        {
            seed*=c*(c+c);
    printf("SEED %d\n", seed);
            if((c=fgetc(fp))!=EOF)
            {
                seed+=((c%8)+1)*c;
    printf("SEED %d\n", seed);
                if((c=fgetc(fp))!=EOF)
                {
                    seed*=c*(2*c);
    printf("SEED %d\n", seed);
                }
            }
        }
    }

    g_seed=seed;
    printf("SEED %d\n", seed);
    fseek(fp,0,SEEK_SET);
    updateNexts(&nChord, &nChordCount, &nInver);

    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c",c);
        fflush(stdout);
        if(isalpha(c))
        {
            setFreq(&g_sawData,g_noteTable[toupper(c)-'A']);
            setFreq(&g_squData,g_noteTable[toupper(c)-'A']);
            Pa_Sleep(delay*delayMult);
            delayMult=getRandNum(1,100);

            if(delayMult<=25)
                delayMult=2;
            else
                delayMult=1;


            if(chordCount++==nChordCount)
            {
                chordCount=0;
                switch(nChord)
                {
                    case 1:
                        g_chord=&(g_first);
                    break;
                    case 2:
                        g_chord=&(g_second);
                    break;
                    case 3:
                        g_chord=&(g_third);
                    break;
                    case 4:
                        g_chord=&(g_fourth);
                    break;
                    case 5:
                        g_chord=&(g_fifth);
                    break;
                    case 6:
                        g_chord=&(g_sixth);
                    break;
                    case 7:
                        g_chord=&(g_seventh);
                    break;
                    default:
                        g_chord=&(g_first);
                    break;
                }
                setChordInversion(g_chord,nInver-1);
                updateNexts(&nChord, &nChordCount, &nInver);
            }
        }
        else
            Pa_Sleep(delay*1.25);
    }

    if((err=Pa_StopStream( stream )) != paNoError)
    {
        getErrorMsg(err);
        return 1;
    }
    if((err=Pa_CloseStream( stream )) != paNoError)
    {
        getErrorMsg(err);
        return 1;
    }
    Pa_Terminate();

    return 0;
}
