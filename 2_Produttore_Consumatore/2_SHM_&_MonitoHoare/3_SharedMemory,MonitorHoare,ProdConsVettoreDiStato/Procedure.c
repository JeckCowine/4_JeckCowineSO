/*.............VETTORE_C.............*/

#include "Procedure.h"

void Set_Dati(Vettore* v) {

	init_monitor(&(v->m), 2); //2= Varcond_Prod, Varcond_Cons
   //Inizializzazione stato
	v->stato[DIM]=0;
	 //Inizializzazione dei valori da passare tra i Produttori e Consumatori
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';
	v->buffer_libero=1; // 1 se libero, 0 se pieno
	v->buffer_occupato=0; // 1 se libero, 0 se pieno
	
}

void Remove_Dati(Vettore* v){
	
	remove_monitor( & (v->m) );
	v->stato[DIM]=0;
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';
	v->buffer_libero=1; // 1 se libero, 0 se pieno
	v->buffer_occupato=0; // 0 se libero, 1 se pieno
	
}   

void Produttore(Vettore* v) {
    
	enter_monitor( & (v->m) );
	
	if(v->buffer_occupato==1){
		wait_condition( &(v->m), Varcond_Produttori);
	}
	
	v->buffer_libero = 0;
	v->buffer_occupato = 1;

    printf("\n");
	srand(getpid()*time(NULL));
	
    int indice = 0;

    while(indice <= DIM && v->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    v->stato[indice] = BUFFER_INUSO;
    	
				/* PER VALORE (int buffer [DIM])*/
	v->buffer[indice]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",v->buffer[indice]); //ELEMENTO SINGOLO int
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	v->buffer2[indice]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
	printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",v->buffer2[indice]); //ELEMENTO SINGOLO char
	/*.....................*/	
		
	v->stato[indice] = BUFFER_PIENO;
	  
	signal_condition( & (v->m), Varcond_Consumatori);
	
	leave_monitor( & (v->m) );
	
}

void Consumatore(Vettore* v) {
    
	enter_monitor( & (v->m) );
	
	if(v->buffer_libero==1){
		wait_condition( &(v->m), Varcond_Consumatori);
	}
	
	v->buffer_libero = 1;
    v->buffer_occupato = 0;
	
    printf("\n");
    
	int indice =0;
	
    while(indice <= DIM && v->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    v->stato[indice] = BUFFER_INUSO;	
            
				/* PER VALORE (int buffer [DIM])*/
	printf("Il valore Consumato(int buffer[DIM])= [%d]\n",v->buffer[indice]);
	/*.....................*/	
	
			/* PER VALORE (char buffer2 [DIM])*/	
	printf("Il valore Consumato(char buffer2[DIM])= [%c]\n",v->buffer2[indice]);
 	/*.....................*/	      		
 	      		
    v->stato[indice] = BUFFER_VUOTO;

	signal_condition( & (v->m), Varcond_Produttori);
		
	leave_monitor( & (v->m) );
		    
}

/*.............END.............*/
