/*.............MAINMAILBOXASINC_C.............*/

#include "MailBoxAsincrona.h"

int main(){

	pid_t pid;
	key_t Chiave_CODA = ftok ("./Start",'S');	// chiave della coda messaggio

		//Inizializzazione MailBox
	
	int ds_coda =msgget(Chiave_CODA,IPC_CREAT|0664);
	if(ds_coda<0) { perror("MailBox errore"); exit(1); }
	MailBox m; //Struct 

	//FINE
	
	Set_Dati(m);
	
	for(int i=0;i<Num_Produttori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Produttore
			printf("\tPRODUTTORE[%d]",i+1);
			Produttore(m, ds_coda);
			exit(1);
			}
	}
		
	for(int i=0;i<Num_Consumatori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Consumatore
			printf("\tCONSUMATORE[%d]",i+1);
			Consumatore(m, ds_coda);
			exit(1);
			}
		}


	for(int i=0;i<Num_Consumatori+Num_Produttori; i++){
		//fine produttori consumatori
		wait(NULL);
	}
    
	Remove_Dati(m,ds_coda);
	
	return 0;
}

/*.............END.............*/
