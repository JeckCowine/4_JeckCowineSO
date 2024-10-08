/*.............MAINMAILBOXASINC_C.............*/

#include "MailBoxAsincrona.h"

int main(){

	printf("Esercizio Produttore Consumatore Single Buffer con Mailbox Asincrona\n\n");
	
	pid_t pid;
	key_t Chiave_CODA = ftok ("./SingleBuff",'s');	// chiave della coda messaggio

		//Inizializzazione MailBox

	// assegnazione coda di comunicazione	
	int ds_coda = msgget(Chiave_CODA,IPC_CREAT|0664);
	if(ds_coda<0) { perror("MailBox errore"); exit(1); }
	SingleBuff s; //Struct 
	// inizializzazione code di servizio
	Set_Dati(s);
	
	//FINE

	// generazione produttore e consumatore	
	for(int i=0;i<Num_Produttori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Produttore
			int count=i;
			Produttore(s,ds_coda,count);
			exit(1);
			}else if(pid<0){perror("Fork Error:"); exit(1);}
	}
		
	for(int i=0;i<Num_Consumatori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Consumatore
			int count=i;
			Consumatore(s,ds_coda,count);
			exit(1);
			}else if(pid<0){perror("Fork Error:"); exit(1);}
		}
	// attesa di terminazione
	for(int i=0;i<Num_Consumatori+Num_Produttori; i++){
		//fine produttori consumatori
		wait(NULL);
	}
    
    // deallocazione code
	Remove_Dati(s,ds_coda);
	
	return 0;
}

/*.............END.............*/
