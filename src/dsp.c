#include <stdlib.h>
#include <stdio.h>
#include "dsp.h"
#include "portaudio.h"

int g_count;
note g_sawData;
note g_squData;
note g_outData;

chord g_first;
chord g_second;
chord g_thrid;
chord g_fourth;
chord g_fifth;
chord g_sixth;
chord g_seventh;
chord g_eighth;

void initChords()
{
    initNote(&(g_first.base), g_sineWave, 51.9130871985); 
    initNote(&(g_first.mid), g_sineWave, 61.7354126570); 
    initNote(&(g_first.high), g_sineWave, 77.7817459305);
}

void initNote(note *data, float *type, float freq)
{
    data->lVal=0;
    data->rVal=0;
    setFreq(data, freq);
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

        notePlay(&(g_first.base));
        notePlay(&(g_first.mid));
        notePlay(&(g_first.high));

        data->lVal=0;
        data->rVal=0;

//        data->lVal+=g_sawData.lVal+g_squData.lVal;
//        data->rVal+=g_sawData.rVal+g_squData.rVal;

        data->lVal+=/*g_first.base.lVal;+g_first.mid.lVal+*/g_first.high.lVal;
        data->rVal+=/*g_first.base.rVal;+g_first.mid.rVal+*/g_first.high.rVal;

//        data->lVal/=5;
//        data->rVal/=5;
//        data->lVal/=2;
//        data->rVal/=2;
    }
    return 0;
}

