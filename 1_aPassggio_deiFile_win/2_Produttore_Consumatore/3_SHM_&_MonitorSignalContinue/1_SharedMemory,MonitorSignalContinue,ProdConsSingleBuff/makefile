all: SingleBuff

SingleBuff: MonitorSignalContinue.h Procedure.h
	gcc Main.c Procedure.c MonitorSignalContinue.c -o SingleBuff MonitorSignalContinue.h Procedure.h 

clean:
	rm -rf *.o
	rm -rf SingleBuff
