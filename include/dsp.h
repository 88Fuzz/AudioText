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
} note;

void getErrorMsg(int);
void noteIncrement(note *);
void noteInterpolate(note *);
void notePlay(note *);
int generateAudio(const void *,
                    void *,
                    unsigned long,
                    const PaStreamCallbackTimeInfo *,
                    PaStreamCallbackFlags,
                    void *);

extern int g_count;
extern note g_data;
extern float g_noteTable[];
extern float g_sawWave[];

#endif
