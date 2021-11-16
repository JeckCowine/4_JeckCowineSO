/*.............MAINMAILBOXASINC_C.............*/

#include "MailBoxAsincrona.h"

int main(){

	pid_t pid;
	key_t Chiave_CODA = ftok ("./MailBoxAsinc",'M');	// chiave della coda messaggio

		//Inizializzazione MailBox

	// assegnazione coda di comunicazione	
	int ds_coda = msgget(Chiave_CODA,IPC_CREAT|0664);
	if(ds_coda<0) { perror("MailBox errore"); exit(1); }
	MailBox m; //Struct 
	// inizializzazione code di servizio
	Set_Dati(m);
	
	//FINE

	// generazione produttore e consumatore	
	for(int i=0;i<Num_Produttori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Produttore
			int count=i;
			sleep(2);
			Produttore(m,ds_coda,count);
			exit(1);
			}
	}
		
	for(int i=0;i<Num_Consumatori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Consumatore
			int count=i;
			sleep(2);
			Consumatore(m,ds_coda,count);
			exit(1);
			}
		}
	// attesa di terminazione
	for(int i=0;i<Num_Consumatori+Num_Produttori; i++){
		//fine produttori consumatori
		wait(NULL);
	}
    
    // deallocazione code
	Remove_Dati(m,ds_coda);
	
	return 0;
}

/*.............END.............*/
