#ifndef __CHORDS_H__
#define __CHORDS_H__
#include "typedefs.h"

int getNextChord(int);
void updateNexts(int *, int*, int*); 
void initInversionNotes(chord *, inversionType, float, float, float);
void setChordInversion(chord *, inversionType);
void initNote(note *, float *);
void initChords();

#endif
