#ifndef __DSP_H__
#define __DSP_H__
#include "portaudio.h"
#include "typedefs.h"

#define SAMPLE_RATE 48000
#define SAMPLE_RATE_DIV (1.0/SAMPLE_RATE)
#define LOOKUP_TABLE_SIZE 2048
#define Bb0 (Bb1/2)
#define C0  (C1/2)
#define D0  (D1/2)
#define Eb0 (Eb1/2)
#define F0  (F1/2)
#define G0  (G1/2)
#define A0  (A1/2)
#define Bb1 (58.2704701898*2)
#define C1  (65.4063913251*2)
#define D1  (73.4161919794*2)
#define Eb1 (77.7817459305*2)
#define F1  (87.3070578583*2)
#define G1  (97.9988589954*2)
#define A1  (110.000000000*2)
#define Bb2 (Bb1*2)
#define C2  (C1*2)
#define D2  (D1*2)
#define Eb2 (Eb1*2)
#define F2  (F1*2)
#define G2  (G1*2)


void getErrorMsg(int);
void noteIncrement(note *);
void noteInterpolate(note *);
void setFreq(note *, float);
void notePlay(note *);
int generateAudio(const void *,
                    void *,
                    unsigned long,
                    const PaStreamCallbackTimeInfo *,
                    PaStreamCallbackFlags,
                    void *);

extern note g_sawData;
extern note g_squData;
extern note g_outData;
extern chord g_first;
extern chord g_second;
extern chord g_third;
extern chord g_fourth;
extern chord g_fifth;
extern chord g_sixth;
extern chord g_seventh;
extern chord g_eighth;
extern chord *g_chord;
extern float g_noteTable[];
extern float g_sawWave[];
extern float g_squWave[];
extern float g_sineWave[];
extern float g_triWave[];

#endif
