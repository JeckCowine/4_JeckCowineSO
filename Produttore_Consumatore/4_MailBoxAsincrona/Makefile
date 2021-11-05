all: MailBoxAsinc

MailBoxAsinc:MainMailBoxAsinc.o MailBoxAsincrona.o
	gcc -o MailBoxAsinc MainMailBoxAsinc.o MailBoxAsincrona.o

MainMailBoxAsinc.o:MainMailBoxAsinc.c MailBoxAsincrona.h
	gcc -c MainMailBoxAsinc.c

MailBoxAsincrona.o:MailBoxAsincrona.c MailBoxAsincrona.h
	gcc -c MailBoxAsincrona.c

clean:
	rm -f *.o
	rm -f ./MailBoxAsinc
