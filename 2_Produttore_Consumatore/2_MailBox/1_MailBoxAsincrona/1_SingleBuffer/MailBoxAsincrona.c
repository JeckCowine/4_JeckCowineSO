/*.............MAILBOXASINCRONA_C.............*/

#include "MailBoxAsincrona.h"

void Set_Dati(SingleBuff s){
	
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori	
	s.intero=0;
	s.carattere='0';
	s.array[DIM_INT]=0;
	s.stringa[DIM_STRING]='0';
	
}

void Remove_Dati(SingleBuff s,int ds_coda){

	s.intero=0;
	s.carattere='0';
	s.array[DIM_INT]=0;
	s.stringa[DIM_STRING]='0';
	msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
	
}


void Produttore(SingleBuff s,int ds_coda,int count) {
	
	// costruzione del messaggio da trasmettere
	s.tipo=MESSAGGIO;
	srand(getpid()*time(NULL));// Serve a scegliere sempre un valore diverso a ogni compilazione
	printf("\tPRODUTTORE[%d]\n",count+1);
	
			/* PER VALORE (int intero)*/
	s.intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
	/*.....................*/		
	
				/* PER VALORE (char carattere)*/
	s.carattere= 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
	/*.....................*/		
	
				/* PER VALORE (int array [DIM])*/	
	for(int i=0;i<DIM_INT;i++) {
		s.array[i] = 1 + rand() % 999; // Valore casuale da 1 a 1.000 per DIM volte
	}
	/*.....................*/			
	
				/* PER VALORE (char stringa [DIM])*/
	for(int i=0;i<DIM_STRING;i++) { 
		s.stringa[i]= 'A' + rand () % 26; // Valore casuale da 'A' a 'Z' per DIM volte
	}
	/*.....................*/		
		
	// invio messaggio
	msgsnd(ds_coda,(void*)&s,sizeof(SingleBuff)-sizeof(long),IPC_NOWAIT);
	
	// Stampe
	printf("Messaggio Inviato(int intero) = [%d]\n",s.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Inviato(char carattere) = [%c]\n",s.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Inviato(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",s.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Inviato(char stringa) = [%s]\n",s.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	
}

void Consumatore(SingleBuff s,int ds_coda,int count) {

	printf("\tCONSUMATORE[%d]\n",count+1);
	
	// ricezione messaggio
	msgrcv(ds_coda,(void *) &s,sizeof(SingleBuff)-sizeof(long),MESSAGGIO,0);
	
	// Stampe
	printf("Messaggio Ricevuto(int intero) = [%d]\n",s.intero);//ELEMENTO SINGOLO int
	printf("Messaggio Ricevuto(char carattere) = [%c]\n",s.carattere);//ELEMENTO SINGOLO char
	printf("Messaggio Ricevuto(int array[DIM]) = ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]",s.array[i]);//ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	printf("Messaggio Ricevuto(char stringa) = [%s]\n",s.stringa);//STRINGA(CHAR) DI DIMENSIONE DIM

}

/*.............END.............*/
