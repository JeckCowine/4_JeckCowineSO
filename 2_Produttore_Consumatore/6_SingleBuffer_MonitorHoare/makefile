all: start

start: MonitorHoare.h SinBufMonHoar.h
	gcc MainMonitorHoare.c SinBufMonHoar.c MonitorHoare.c -o start MonitorHoare.h SinBufMonHoar.h 

clean:
	rm -rf *.o
	rm -rf start
