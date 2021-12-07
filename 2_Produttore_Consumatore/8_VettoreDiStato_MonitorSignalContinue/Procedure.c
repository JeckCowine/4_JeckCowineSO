/*.............VETTORESIGNALCONTINUE_C..............*/

#include "Procedure.h"

void Set_Dati(Vettore* v){
	
	init_monitor(&(v->m), 2); //2= Varcond_Prod, Varcond_Cons
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';	
	v->stato[DIM]=0;
	v->Spazio_Disponibile=DIM; //Se 0 è pieno, Se 1 è libero
	v->Messaggio_Disponibile=0; //Se 0 non c'è Messaggio, Se 1 si
	
}
void Remove_Dati(Vettore* v){
	
	remove_monitor( & (v->m) );
	v->buffer[DIM]=0;	
	v->buffer2[DIM]='0';	
	v->stato[DIM]=0;

}
void Produttore(Vettore* v){

	enter_monitor( & (v->m) );
	
	while(v->Spazio_Disponibile==0){
		wait_condition( &(v->m), MUTEX_P);
	}
	
    int indice = 0;
  
    while(indice <= DIM && v->stato[indice] != BUFFER_VUOTO) {
        indice++;
    }
    
    v->stato[indice] = BUFFER_INUSO;
    v->Spazio_Disponibile--;
    
    leave_monitor( & (v->m) );

	printf("\n");
	srand(getpid()*time(NULL));
				
			/* PER VALORE (int buffer [DIM])*/
	v->buffer[indice]= 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Il valore Prodotto(int buffer[DIM])= [%d]\n",v->buffer[indice]); //ELEMENTO SINGOLO int
	/*.....................*/		
	
			/* PER VALORE (char buffer2 [DIM])*/
	v->buffer2[indice]='A' + (rand () % 26); // Valore casuale da 'A' a 'Z'
	printf("Il valore Prodotto(char buffer2[DIM])= [%c]\n",v->buffer2[indice]); //ELEMENTO SINGOLO char
	/*.....................*/	
	
	enter_monitor( & (v->m) );
	
	v->stato[indice] = BUFFER_PIENO;
	v->Messaggio_Disponibile++;
	
	signal_condition( &(v->m), MUTEX_C);
	
	leave_monitor( & (v->m) );
	
}

void Consumatore(Vettore* v){
	
	enter_monitor( & (v->m) );
		
	while(v->Messaggio_Disponibile ==0){
		wait_condition(&(v->m),MUTEX_C);	
	}

    int indice = 0;
    	
    while(indice <= DIM && v->stato[indice] != BUFFER_PIENO) {
        indice++;
    }
    
    v->stato[indice] = BUFFER_INUSO;
    v->Messaggio_Disponibile--;

    leave_monitor( & (v->m) );

    printf("\n");
            
		/* PER VALORE (int buffer [DIM])*/
	printf("Il valore Consumato(int buffer[DIM])= [%d]\n",v->buffer[indice]);
	/*.....................*/	
	
		/* PER VALORE (char buffer2 [DIM])*/	
	printf("Il valore Consumato(char buffer2[DIM])= [%c]\n",v->buffer2[indice]);
 	/*.....................*/	      

	enter_monitor( & (v->m) );
	 	      		
    v->stato[indice] = BUFFER_VUOTO;
    v->Spazio_Disponibile++;

	signal_condition( &(v->m),MUTEX_P);
	
	leave_monitor( & (v->m) );
	
}

/*.............END.............*/
