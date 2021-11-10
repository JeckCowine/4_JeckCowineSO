all:SingleBuff

SingleBuff: SingleBuff.h semafori.o
	gcc MainSingleBuff.c SingleBuff.c -o SingleBuff semafori.o
			
semafori.o: semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf SingleBuff
