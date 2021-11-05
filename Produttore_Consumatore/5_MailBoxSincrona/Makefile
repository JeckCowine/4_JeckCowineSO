all: MailBoxSinc

MailBoxSinc:MainMailBoxSinc.o MailBoxSincrona.o
	gcc -o MailBoxSinc MainMailBoxSinc.o MailBoxSincrona.o

MainMailBoxSinc.o:MainMailBoxSinc.c MailBoxSincrona.h
	gcc -c MainMailBoxSinc.c

MailBoxSincrona.o:MailBoxSincrona.c MailBoxSincrona.h
	gcc -c MailBoxSincrona.c

clean:
	rm -f *.o
	rm -f ./MailBoxSinc
