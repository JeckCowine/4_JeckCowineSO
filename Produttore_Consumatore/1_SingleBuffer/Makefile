all:SingleBuff

SingleBuff: MainSingleBuff.o SingleBuff.o semafori.o
	gcc -o SingleBuff MainSingleBuff.o SingleBuff.o semafori.o
	
MainSingleBuff.o: MainSingleBuff.c SingleBuff.h
	gcc -c MainSingleBuff.c
	
SingleBuff.o: SingleBuff.c SingleBuff.h
	gcc -c SingleBuff.c
		
semafori.o: semafori.c semafori.h
	gcc -c semafori.c

clean:
	rm -rf *.o
	rm -rf SingleBuff

