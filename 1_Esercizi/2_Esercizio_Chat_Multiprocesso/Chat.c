/*.............CHAT_C.............*/

#include "Chat.h"

void Mittente(MailBox m,int coda_ricevente, int coda_invio){
	
	int check;

	while(1){

		// Prelevo il messaggio da inviare
		printf("Msg da inviare: ");				
		scanf("%s",m.stringa);

		// Setto il tipo
		m.tipo=MESSAGGIO;

		// Verifico se il messaggio è exit
		if(strcmp(m.stringa,"exit")==0){
			// Essendo exit, lo invio sulla seconda coda e termino
			check = msgsnd(coda_ricevente,&m, sizeof(MailBox)-sizeof(long),0);
			if(check<0) {perror("[Coda Mittente Eliminata]");_exit(1);}
			printf("[Invio Exit]: %s\n", m.stringa);
            _exit(1);
		}else{
			// Non essendo exit, lo invio sulla prima coda
			check = msgsnd(coda_invio,&m,sizeof(MailBox)-sizeof(long),0);
            if(check<0) {perror("[Coda Mittente Eliminata]");_exit(1);}
			printf("[Mittente]: %s\n",m.stringa);
			}
	}

}

void Ricevente(MailBox m,int coda_ricevente){

	int check;

	while(1){

		// Mi metto in attesa di un messaggio sulla seconda coda
		check = msgrcv(coda_ricevente,&m,sizeof(MailBox)-sizeof(long),MESSAGGIO,0);
		if(check<0) {perror("[Coda Ricevente Eliminata]");_exit(1);}
		
			// Se il messaggio ricevuto è exit termino
		if(strcmp(m.stringa,"exit")==0){printf("[Ricevuto Exit]: %s\n", m.stringa); _exit(1);}    
		else printf("[Ricevente]: %s\n",m.stringa);
				
	}

}


/*.............END.............*/
