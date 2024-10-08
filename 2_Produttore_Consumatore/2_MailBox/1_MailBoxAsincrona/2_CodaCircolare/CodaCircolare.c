/*.............CODACIRCOLARE_C.............*/

#include "CodaCircolare.h"

void Set_Dati(Coda c) {

	//Inizializzazione testa e coda  
	c->testa=0;
	c->coda=0;
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	
}

void Remove_Dati(Coda c, int ds_coda){

	//Inizializzazione testa e coda  	
	c->testa=0;
	c->coda=0;
	//Inizializzazione dei valori da passare tra i Produttori e Consumatori
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	msgctl(ds_coda,IPC_RMID,0);// rimozione chiave della MailBox
	
}   

void Produttore(Coda c, int ds_coda, int count) {
    
	// costruzione del messaggio da trasmettere
	c.tipo=MESSAGGIO;
	srand(getpid()*time(NULL));// Serve a scegliere sempre un valore diverso a ogni compilazione
	printf("\tPRODUTTORE[%d]\n",count+1);
        //PRODUZIONE IN TESTA DELLA CODA
	
				/* PER VALORE (int buffer [DIM])*/
	c.buffer[c.testa]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	c.buffer2[c.testa]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'

	/*.....................*/	
		
	c.testa = (c.testa+1) % DIM;
	
		// invio messaggio
	msgsnd(ds_coda,(void*)&c,sizeof(Coda)-sizeof(long),IPC_NOWAIT);

	// Stampe

	printf("Messaggio Inviato(int buffer[DIM])= [%d]\n",c.buffer[c.testa]); //ELEMENTO SINGOLO int
	printf("Messaggio Inviato(char buffer2[DIM])= [%c]\n",c.buffer2[c.testa]); //ELEMENTO SINGOLO char
    
}

void Consumatore(Coda c,int ds_coda,int count) {
        
	printf("\tCONSUMATORE[%d]\n",count+1);
	
            //CONSUMAZIONE IN CODA
	// ricezione messaggio
	msgrcv(ds_coda,(void *) &c,sizeof(Coda)-sizeof(long),MESSAGGIO,0);
	
				/* PER VALORE (int buffer [DIM])*/
	printf("Messaggio Ricevuto(int buffer[DIM])= [%d]\n",c.buffer[c.coda]);
	/*.....................*/	
	
			/* PER VALORE (char buffer2 [DIM])*/	
	printf("Messaggio Ricevuto(char buffer2[DIM])= [%c]\n",c.buffer2[c.coda]);
 	/*.....................*/	      		
 	      		
	c.coda = (c.coda + 1) % DIM;
	
}

/*.............END.............*/


