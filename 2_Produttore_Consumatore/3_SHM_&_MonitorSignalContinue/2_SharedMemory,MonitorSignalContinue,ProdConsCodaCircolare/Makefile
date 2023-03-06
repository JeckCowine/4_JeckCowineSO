all: Coda

Coda: MonitorSignalContinue.h Procedure.h
	gcc Main.c Procedure.c MonitorSignalContinue.c -o Coda MonitorSignalContinue.h Procedure.h 

clean:
	rm -rf *.o
	rm -rf Coda
