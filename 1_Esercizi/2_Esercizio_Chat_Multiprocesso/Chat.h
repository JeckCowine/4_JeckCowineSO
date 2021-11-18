/*.............CHAT_H.............*/

#ifndef __CHAT__
#define __CHAT__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo per il messaggio
#define MESSAGGIO 1

// Struct raltiva ai messaggi
typedef struct{
	
	long tipo;		// tipo messaggio
	char stringa[20];	// messaggio effettivo
	
}MailBox;

void Mittente(MailBox,int, int);
void Ricevente(MailBox,int);

#endif 

/*.............END.............*/
