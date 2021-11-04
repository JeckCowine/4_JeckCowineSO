all: VettoreDiStato

VettoreDiStato: VettorediStato.o semafori.o MainVettore.o
	gcc -o VettoreDiStato VettorediStato.o semafori.o MainVettore.o

MainVettore.o: MainVettore.c
	gcc -c MainVettore.c

VettorediStato.o: VettorediStato.h VettorediStato.c
	gcc -c VettorediStato.c

semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf VettoreDiStato
