all: CodaCircolare

CodaCircolare: CodaCircolare.o MainCoda.o semafori.o
	gcc -o CodaCircolare CodaCircolare.o MainCoda.o semafori.o

MainCoda.o: MainCoda.c CodaCircolare.h 
	gcc -c MainCoda.c

CodaCircolare.o: CodaCircolare.c CodaCircolare.h
	gcc -c CodaCircolare.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf CodaCircolare
