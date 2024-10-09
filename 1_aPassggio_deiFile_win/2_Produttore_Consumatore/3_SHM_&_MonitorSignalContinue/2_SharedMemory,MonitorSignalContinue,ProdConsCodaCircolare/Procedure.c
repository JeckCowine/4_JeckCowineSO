/*.............CODACIRCOLARE_C.............*/

#include "Procedure.h"

void Set_Dati(Coda* c) {

	init_monitor(&(c->m), 2); //2= Varcond_Prod, Varcond_Cons
   //Inizializzazione testa e coda  
	c->testa=0;
	c->coda=0;
	 //Inizializzazione dei valori da passare tra i Produttori e Consumatori
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	c->buffer_libero=1; // 1 se libero, 0 se pieno
	c->buffer_occupato=0; // 1 se libero, 0 se pieno
	
}

void Remove_Dati(Coda* c){
	
	remove_monitor( & (c->m) );
	c->testa=0;
	c->coda=0;
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	c->buffer_libero=1; // 1 se libero, 0 se pieno
	c->buffer_occupato=0; // 0 se libero, 1 se pieno
	
}   

void Produttore(Coda * c) {
    
	enter_monitor( & (c->m) );
	
	while(c->buffer_occupato==1){
		wait_condition( &(c->m), Varcond_Produttori);
	}
	
	c->buffer_libero = 0;
	c->buffer_occupato = 1;

    printf("\n");
	srand(getpid()*time(NULL));
        //PRODUZIONE IN TESTA DELLA CODA
	
				/* PER VALORE (int buffer [DIM])*/
	c->buffer[c->testa]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",c->buffer[c->testa]); //ELEMENTO SINGOLO int
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	c->buffer2[c->testa]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
	printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",c->buffer2[c->testa]); //ELEMENTO SINGOLO char
	/*.....................*/	
		
	c->testa = (c->testa+1) % DIM;
	  
	signal_condition( & (c->m), Varcond_Consumatori);
	
	leave_monitor( & (c->m) );
	
}

void Consumatore(Coda * c) {
    
	enter_monitor( & (c->m) );
	
	while(c->buffer_libero==1){
		wait_condition( &(c->m), Varcond_Consumatori);
	}
	
	c->buffer_libero = 1;
    c->buffer_occupato = 0;
	
    printf("\n");
            //CONSUMAZIONE IN CODA
            
				/* PER VALORE (int buffer [DIM])*/
	printf("Il valore Consumato(int buffer[DIM])= [%d]\n",c->buffer[c->coda]);
	/*.....................*/	
	
			/* PER VALORE (char buffer2 [DIM])*/	
	printf("Il valore Consumato(char buffer2[DIM])= [%c]\n",c->buffer2[c->coda]);
 	/*.....................*/	      		
 	      		
	c->coda = (c->coda + 1) % DIM;

	signal_condition( & (c->m), Varcond_Produttori);
		
	leave_monitor( & (c->m) );
		    
}

/*.............END.............*/
