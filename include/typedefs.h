#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__
typedef enum
{
    ROOTPOS,
    FIRSTINV,
    SECONDINV
} inversionType;

typedef struct
{
    float n_base;
    float n_third;
    float n_fifth;
} chordNotes;

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
    note third;
    note fifth;
    chordNotes rootPos;
    chordNotes firstInv;
    chordNotes secondInv;
    inversionType inversion;
} chord;

#endif
