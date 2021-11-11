all: 1_start p1 p2 p3

1_start: CodaMessaggi.h
	gcc MainExec.c CodaMessaggi.c -o 1_start

p1: CodaMessaggi.h
	gcc Processo1.c CodaMessaggi.c -o p1
	
p2: CodaMessaggi.h
	gcc Processo2.c CodaMessaggi.c -o p2
	
p3: CodaMessaggi.h
	gcc Processo3.c CodaMessaggi.c -o p3 

clean:
	rm -rf *.o
	rm -rf 1_start p1 p2 p3
