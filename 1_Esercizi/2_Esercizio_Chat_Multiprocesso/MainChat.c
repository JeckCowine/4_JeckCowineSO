/*.............MAINCHAT_C.............*/

#include "Chat.h"

int main(int argc, char *argv[]) {

	pid_t pid;
	int i;
	
	// Controllo gli argomenti passati
	if(argc< 2){
		printf("Errore: Fornire come parametri di ingresso 2 caratteri separati da spazio\n");
        printf("Esempio: %s a b\n", argv[0]);
		_exit(1);
	}

	char PrimoArgomento = *argv[1];
	char SecondoArgomento = *argv[2];

	printf("I caratteri inseriti sono: %c %c\n", PrimoArgomento, SecondoArgomento);

	// Creo le chiavi per le due code di messaggi
	key_t coda_invio  = ftok(".", PrimoArgomento);
	key_t coda_ricevente = ftok(".", SecondoArgomento);

	// Creo le due code	
	int id_coda_invio = msgget(coda_invio, IPC_CREAT|0644);
    int id_coda_ricevente = msgget(coda_ricevente, IPC_CREAT|0644);
	if(id_coda_invio < 0) {perror("Msgget fallita");exit(1);}
	if(id_coda_ricevente < 0) {perror("Msgget fallita");exit(1);}

	MailBox m;
	
	// Genero i due figli, mittente e destinatario
	for(i=0; i<2; i++){
		pid = fork();
			if(pid==0){	// Processo figlio
				if(i==0) Mittente(m,id_coda_ricevente, id_coda_invio); //i=0 Mittente
				else Ricevente(m,id_coda_ricevente);                             //i=1 Ricevente
			}else if (pid <0){perror("Fork fallita");exit(1);}       
	}

	// Attendo che i figli, mittente e destinatario, siano terminati
	for(i=0; i<2; i++) {
		wait(NULL);
	}

	// Rimuovo le code
	msgctl(id_coda_invio, IPC_RMID, 0);
	msgctl(id_coda_ricevente, IPC_RMID, 0);

}

/*.............END.............*/
