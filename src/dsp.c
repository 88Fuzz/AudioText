#include <stdlib.h>
#include <stdio.h>
#include "dsp.h"
#include "portaudio.h"

int g_count;
note g_sawData;
note g_squData;
note g_outData;

void initNote(note *data, float *type)
{
    data->lVal=0;
    data->rVal=0;
    setFreq(data, 440.0);
    data->pos=0;
    data->waveTable=type;
}

void setFreq(note *data, float freq)
{
    data->baseFreq=freq;
    data->increment=(float)LOOKUP_TABLE_SIZE * freq * SAMPLE_RATE_DIV;
}

void getErrorMsg(int err)
{
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
}

void noteIncrement(note *data)
{
    data->pos += data->increment;
    if(data->pos > LOOKUP_TABLE_SIZE)
        data->pos=0.0;
}

void noteInterpolate(note *data)
{
    int max, min;
    float  diffMax, diffMin;

    max = (int) (data->pos +1.0);
    min = (int) data->pos;
  
    if(max>LOOKUP_TABLE_SIZE)
        max=0;

    diffMin = max-data->pos;
    diffMax= data->pos-min;

    data->lVal= data->waveTable[max]*diffMax;//g_sawWave[max]*diffMax;
    data->lVal += data->waveTable[min]*diffMin;//g_sawWave[min]*diffMin;

    data->rVal= data->waveTable[max]*diffMax;//g_sawWave[max]*diffMax;
    data->rVal += data->waveTable[min]*diffMin;//g_sawWave[min]*diffMin;

    data->lVal *= 0.82;
    data->rVal *= 0.82;
}

void notePlay(note *data)
{
    noteIncrement(data);
    noteInterpolate(data);
}

int generateAudio( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    note *data= (note *) userData;
    float *out= (float *) outputBuffer;
    int i;

    for(i=0; i<framesPerBuffer; i++)
    {
        *out++ = data->lVal;
        *out++ = data->rVal;

        notePlay(&g_sawData);
        notePlay(&g_squData);

        data->lVal=(g_sawData.lVal+g_squData.lVal)*0.5;
        data->rVal=(g_sawData.rVal+g_squData.rVal)*0.5;
    }
    return 0;
}

