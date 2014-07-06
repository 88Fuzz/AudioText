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
chord g_third;
chord g_fourth;
chord g_fifth;
chord g_sixth;
chord g_seventh;
chord g_eighth;
chord *g_chord;

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

        notePlay(&(g_chord->base));
        notePlay(&(g_chord->third));
        notePlay(&(g_chord->fifth));

        data->lVal=0;
        data->rVal=0;

        data->lVal+=g_sawData.lVal+g_squData.lVal;
        data->rVal+=g_sawData.rVal+g_squData.rVal;

//        data->lVal+=/*g_first.base.lVal;*/+g_first.third.lVal;//+*/g_first.fifth.lVal;
//        data->rVal+=/*g_first.base.rVal;*/+g_first.third.rVal;//+*/g_first.fifth.rVal;

        data->lVal+=g_chord->base.lVal+g_chord->third.lVal+g_chord->fifth.lVal;
        data->rVal+=g_chord->base.rVal+g_chord->third.rVal+g_chord->fifth.rVal;

        data->lVal/=5;
        data->rVal/=5;
//        data->lVal/=3;
//        data->rVal/=3;
//        data->lVal/=2;
//        data->rVal/=2;
    }
    return 0;
}

