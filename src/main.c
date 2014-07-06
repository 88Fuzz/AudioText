#include <stdlib.h>
#include <stdio.h>
#include "portaudio.h"
#include "dsp.h"



int main(int argc, char *argv[])
{
    PaStream *stream;
    PaError err;
    int count=0;
    int delay;
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

    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c",c);
        fflush(stdout);
        if(isalpha(c))
        {
            setFreq(&g_sawData,g_noteTable[toupper(c)-'A']);
            setFreq(&g_squData,g_noteTable[toupper(c)-'A']);
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
