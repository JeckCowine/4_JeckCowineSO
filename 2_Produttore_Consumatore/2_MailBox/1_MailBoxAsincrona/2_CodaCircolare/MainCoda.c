/*.............MAIN_C.............*/

#include "CodaCircolare.h"

int main(){
	
	printf("Esercizio Produttore Consumatore Coda Circolare con Mailbox Asincrona\n\n");
	
	pid_t pid;
	key_t Chiave_CODA = ftok ("./CodaCircolare",'c');	// chiave della coda messaggio

		//Inizializzazione MailBox

	// assegnazione coda di comunicazione	
	int ds_coda = msgget(Chiave_CODA,IPC_CREAT|0664);
	if(ds_coda<0) { perror("MailBox errore"); exit(1); }
	Coda c; //Struct 
	// inizializzazione code di servizio
	Set_Dati(c);
	
	//FINE

	// generazione produttore e consumatore	
	for(int i=0;i<Num_Produttori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Produttore
			int count=i;
			sleep(2);
			Produttore(c,ds_coda,count);
			exit(1);
			}else if(pid<0){perror("Fork Error:"); exit(1);}
	}
		
	for(int i=0;i<Num_Consumatori;i++){
			pid = fork();
			if(pid==0) {
				//figlio Consumatore
			int count=i;
			sleep(2);
			Consumatore(c,ds_coda,count);
			exit(1);
			}else if(pid<0){perror("Fork Error:"); exit(1);}
		}
	// attesa di terminazione
	for(int i=0;i<Num_Consumatori+Num_Produttori; i++){
		//fine produttori consumatori
		wait(NULL);
	}
    
    // deallocazione code
	Remove_Dati(c,ds_coda);
	
    return 0;
}

/*.............END.............*/
