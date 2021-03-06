CC=gcc
INCS=include
PORTAUDIOLIB=/home/kyle/workspace/audioTest/libs/
SRCTEXTAUDIO=src/main.c src/dsp.c src/tables.c src/random.c src/chords.c
SRCNOTETABLE=src/noteTableGen.c
OBJS=$(SRCTEXTAUDIO:.cpp=.o)
EXNM=SFMLtest
EXTEXTAUDIO=audioText
EXNOTETABLE=noteTable

all: audiotext

audiotext:
	$(CC) -L$(PORTAUDIOLIB) -I$(INCS) -o $(EXTEXTAUDIO) $(SRCTEXTAUDIO) -lportaudio

notetable:
	$(CC) -o $(EXNOTETABLE) $(SRCNOTETABLE)

wavetable:
	python wavetable.py

clean:
	rm $(EXTEXTAUDIO) $(EXNOTETABLE) 
