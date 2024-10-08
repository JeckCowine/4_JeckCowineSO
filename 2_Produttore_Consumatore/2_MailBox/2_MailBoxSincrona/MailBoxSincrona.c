/*.............MAILBOXSINCRONA_C.............*/

#include "MailBoxSincrona.h"

void Set_Dati(MailBox m){
	
	key_t Chiave_CODA1 = ftok ("./MailBoxSincrona",'M');	// chiave della coda messaggio
	key_t Chiave_CODA2 = ftok ("./MailBoxSincrona",'M');	// chiave della coda messaggio
    ds_coda1=msgget(Chiave_CODA1,IPC_CREAT|0664);
    if(ds_coda1<0) { perror("MailBox1 errore"); exit(1); }
	ds_coda2=msgget(Chiave_CODA2,IPC_CREAT|0664);
	if(ds_coda2<0) { perror("MailBox2 errore"); exit(1); }
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori	
	m.intero=0;
	m.carattere='0';
	for(int i=0;i<DIM_INT;i++) m.array[i]=0;
	for(int i=0;i<DIM_STRING;i++) m.stringa[i]='0';
	
}

void Remove_Dati(MailBox m, int ds_coda){
	
	msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
	msgctl(ds_coda1,IPC_RMID,0);// rimozione chiave della MailBox
	msgctl(ds_coda2,IPC_RMID,0);// rimozione chiave della MailBox
	m.intero=0;
	m.carattere='0';
	for(int i=0;i<DIM_INT;i++) m.array[i]=0;
	for(int i=0;i<DIM_STRING;i++) m.stringa[i]='0';
	
}

void Produttore(MailBox m, int ds_coda,int count) {
	
	MailBox m1,m2;
	// costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	
	srand(getpid()*time(NULL));
			/* PER VALORE (int intero)*/
	m.intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
	/*.....................*/		
	
				/* PER VALORE (char carattere)*/
	m.carattere= 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
	/*.....................*/		
	
				/* PER VALORE (int array [DIM])*/	
	for(int i=0;i<DIM_INT;i++) {
		m.array[i] = 1 + rand() % 999; // Valore casuale da 1 a 1.000 per DIM volte
	}
	/*.....................*/			
	
				/* PER VALORE (char stringa [DIM])*/
	for(int i=0;i<DIM_STRING;i++) { 
		m.stringa[i]= 'A' + rand () % 26; // Valore casuale da 'A' a 'Z' per DIM volte
	}
	/*.....................*/		
	
	// Send Sincrona :
	m1.tipo=REQUEST_TO_SEND;
	// invio messaggio RTS
	msgsnd(ds_coda1,&m1,sizeof(MailBox)-sizeof(long),0);	
	// ricezione OTS
	msgrcv(ds_coda2,&m2,sizeof(MailBox)-sizeof(long),OK_TO_SEND,0);
	// invio messaggio
	msgsnd(ds_coda,&m,sizeof(MailBox)-sizeof(long),0);

	//stampa del messaggio inviato
	printf("\tPRODUTTORE[%d]\n",count+1);
	// Stampe
	printf("Messaggio Inviato(int intero) = [%d]\n",m.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Inviato(char carattere) = [%c]\n",m.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Inviato(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",m.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Inviato(char stringa) = [%s]\n",m.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	
}

void Consumatore(MailBox m, int ds_coda,int count) {
	
	MailBox m1,m2;
	
	// Receive Bloccante
	msgrcv(ds_coda1,&m1,sizeof(MailBox)-sizeof(long),REQUEST_TO_SEND,0);	// costruzione messaggio OTS
	m2.tipo=OK_TO_SEND;
	msgsnd(ds_coda2,&m2,sizeof(MailBox)-sizeof(long),0);
	// ricezione messaggio
	int tipomess= MESSAGGIO;
	msgrcv(ds_coda,&m,sizeof(MailBox)-sizeof(long),tipomess,0);
	
	//stampa del messaggio ricevuto
	printf("\tCONSUMATORE[%d]\n",count+1);
	// Stampe
	printf("Messaggio Ricevuto(int intero) = [%d]\n",m.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Ricevuto(char carattere) = [%c]\n",m.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Ricevuto(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",m.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Ricevuto(char stringa) = [%s]\n",m.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	
}

/*.............END.............*/

