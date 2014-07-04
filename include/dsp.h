#ifndef __DSP_H__
#define __DSP_H__
#include "portaudio.h"

#define SAMPLE_RATE 48000
#define SAMPLE_RATE_DIV (1.0/SAMPLE_RATE)
#define LOOKUP_TABLE_SIZE 2048

typedef struct
{
    float lVal;               //left sample value
    float rVal;               //right sample value
    float baseFreq;
    float increment;          //amount to increment sample in wave table
    float pos;               //position in wavetable
    float *waveTable;
} note;

typedef struct
{
    note base;
    note mid;
    note high;
//    float *waveTable1;
//    float *waveTable2;
} chord;

void getErrorMsg(int);
void noteIncrement(note *);
void noteInterpolate(note *);
void initNote(note *, float *, float);
void initChords();
void setFreq(note *, float);
void notePlay(note *);
int generateAudio(const void *,
                    void *,
                    unsigned long,
                    const PaStreamCallbackTimeInfo *,
                    PaStreamCallbackFlags,
                    void *);

extern int g_count;
extern note g_sawData;
extern note g_squData;
extern note g_outData;
extern chord g_first;
extern chord g_second;
extern chord g_thrid;
extern chord g_fourth;
extern chord g_fifth;
extern chord g_sixth;
extern chord g_seventh;
extern chord g_eighth;
extern float g_noteTable[];
extern float g_sawWave[];
extern float g_squWave[];
extern float g_sineWave[];

#endif
