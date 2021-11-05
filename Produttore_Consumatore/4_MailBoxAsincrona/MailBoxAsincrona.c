/*.............MAILBOXASINCRONA_C.............*/

#include "MailBoxAsincrona.h"

void Set_Dati(MailBox m){
	
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori	
	m.intero=0;
	m.carattere='0';
	for(int i=0;i<DIM_INT;i++) m.array[i]=0;
	for(int i=0;i<DIM_INT;i++) m.stringa[i]='0';
	
}

void Remove_Dati(MailBox m,int ds_coda){

	m.intero=0;
	m.carattere='0';
	for(int i=0;i<DIM_INT;i++) m.array[i]=0;
	for(int i=0;i<DIM_INT;i++) m.stringa[i]='0';
	msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
	
}


void Produttore(MailBox m,int ds_coda,int count) {
	
	// costruzione del messaggio da trasmettere
	m.tipo=MESSAGGIO;
	srand(getpid()*time(NULL));// Serve a scegliere sempre un valore diverso a ogni compilazione
	printf("\tPRODUTTORE[%d]\n",count+1);
	
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
		
	// invio messaggio
	msgsnd(ds_coda,(void*)&m,sizeof(MailBox)-sizeof(long),IPC_NOWAIT);
	
	// Stampe
	printf("Messaggio Inviato(int intero) = [%d]\n",m.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Inviato(char carattere) = [%c]\n",m.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Inviato(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",m.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Inviato(char stringa) = [%s]\n",m.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	
}

void Consumatore(MailBox m,int ds_coda,int count) {

	printf("\tCONSUMATORE[%d]\n",count+1);
	
	// ricezione messaggio
	msgrcv(ds_coda,(void *) &m,sizeof(MailBox)-sizeof(long),MESSAGGIO,0);
	
	// Stampe
	printf("Messaggio Ricevuto(int intero) = [%d]\n",m.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Ricevuto(char carattere) = [%c]\n",m.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Ricevuto(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",m.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Ricevuto(char stringa) = [%s]\n",m.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM

}

/*.............END.............*/
