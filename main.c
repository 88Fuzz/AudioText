#include <stdlib.h>
#include <stdio.h>
#include "include/portaudio.h"
#include "include/notetable.h"
#include "include/dsp.h"



int main(int argc, char *argv[])
{
    PaStream *stream;
    PaError err;
    int count=0;
    int delay;
    char c;

    g_data.lVal=0;
    g_data.rVal=0;
    g_data.baseFreq=440.0;

    if(argc!=3)
    {
        printf("Usage: %s <input file> <amount of time a note is played>\n",argv[0]);
        return 1;
    }

    delay=atoi(argv[2]);

    FILE *fp=fopen(argv[1],"r");
    if(fp==NULL)
        return 0;


    g_data.increment=(float)LOOKUP_TABLE_SIZE * g_data.baseFreq * SAMPLE_RATE_DIV;
    g_data.pos=0;

    if((err=Pa_Initialize()) != paNoError)
    {
        getErrorMsg(err);
        return 1;
    } 

    err=Pa_OpenDefaultStream( &stream,
                            0,
                            2,
                            paFloat32,
                            SAMPLE_RATE,
                            256,
                            generateAudio,
                            &g_data);
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

    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c",c);
        fflush(stdout);
        if(isalpha(c))
        {
            g_data.baseFreq=g_noteTable[toupper(c)-'A'];
            g_data.increment=(float)LOOKUP_TABLE_SIZE * g_data.baseFreq * SAMPLE_RATE_DIV;
            Pa_Sleep(delay);
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
