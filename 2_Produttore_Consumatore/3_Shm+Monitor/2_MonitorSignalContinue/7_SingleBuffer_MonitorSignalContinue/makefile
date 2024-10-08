all: SingleBuffSignalContinue

SingleBuffSignalContinue: MonitorSignalContinue.h SinBufSignalContinue.h
	gcc MainSignalContinue.c SinBufSignalContinue.c MonitorSignalContinue.c -o SingleBuffSignalContinue MonitorSignalContinue.h SinBufSignalContinue.h

clean:
	rm -rf *.o
	rm -rf SingleBuffSignalContinue
