CC=gcc
INCS=/home/kyle/SFML/include
PORTAUDIOLIB=/home/kyle/workspace/audioTest/libs/
LIBS=/home/kyle/SFML/lib
SRCTEXTAUDIO=main.c dsp.c
SRCNOTETABLE=noteTableGen.c
OBJS=$(SRCTEXTAUDIO:.cpp=.o)
EXNM=SFMLtest
EXTEXTAUDIO=audioText
EXNOTETABLE=noteTable

all: audiotext

audiotext:
	$(CC) -L$(PORTAUDIOLIB) -o $(EXTEXTAUDIO) $(SRCTEXTAUDIO) -lportaudio

notetable:
	$(CC) -o $(EXNOTETABLE) $(SRCNOTETABLE)

wavetable:
	python wavetable.py

clean:
	rm *.o $(EXTEXTAUDIO) $(EXNOTETABLE) 
