all: CodaCircolare

CodaCircolare: CodaCircolare.h semafori.o
	gcc MainCoda.c CodaCircolare.c -o CodaCircolare semafori.o

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf CodaCircolare
