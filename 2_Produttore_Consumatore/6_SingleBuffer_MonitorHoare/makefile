all: SingleBuffMonitorHoare

SingleBuffMonitorHoare: MonitorHoare.h SinBufMonHoar.h
	gcc MainMonitorHoare.c SinBufMonHoar.c MonitorHoare.c -o SingleBuffMonitorHoare MonitorHoare.h SinBufMonHoar.h 

clean:
	rm -rf *.o
	rm -rf SingleBuffMonitorHoare
