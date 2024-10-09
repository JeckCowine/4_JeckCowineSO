/*.............PROCEDURE_C..............*/

#include "Procedure.h"

void Set_Dati(SingleBuff* s){
	
	init_monitor(&(s->m), 2); //2= Varcond_Prod, Varcond_Cons
	s->intero=0;
	s->carattere='0';
	s->array[DIM_INT]=0;
	s->stringa[DIM_STRING]='0';
	s->buffer_libero=1; // 1 se libero, 0 se pieno
	s->buffer_occupato=0; // 0 se libero, 1 se pieno
	
}
void Remove_Dati(SingleBuff* s){
	
	remove_monitor( & (s->m) );
	s->intero=0;
	s->carattere='0';
	s->array[DIM_INT]=0;
	s->stringa[DIM_STRING]='0';
	s->buffer_libero=1; // 1 se libero, 0 se pieno
	s->buffer_occupato=0; // 0 se libero, 1 se pieno
	
	
}
void Produttore(SingleBuff* s){

	enter_monitor( & (s->m) );
	
	while(s->buffer_occupato==1){
		wait_condition( &(s->m), Varcond_Produttori);
	}
	
	printf("\n");
	srand(getpid()*time(NULL));
	
			/* PER VALORE (int intero)*/
	s->intero = 1 + rand () % 999; // Valore casuale da 1 a 1.000
	printf("Valore Prodotto(int intero) = [%d]\n", s->intero); //ELEMENTO SINGOLO int
				/* PER VALORE (char carattere)*/
	s->carattere= 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z'
	printf("Valore Prodotto(char carattere)= [%c]\n", s->carattere); //ELEMENTO SINGOLO char
	/*.....................*/	
	
			/* PER VALORE (int array [DIM])*/
	for(int i=0;i<DIM_INT;i++){
		s->array[i] = 1 + rand() %999; // Valore casuale da 1 a 1.000 per DIM volte
	}
	printf("Valore Prodotto(int array[DIM])= ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]", s->array[i]); //ARRAY(INT) DI DIMENSIONE DIM
	printf("\n");
	/*.....................*/	
	
			/* PER VALORE (char stringa [DIM])*/
	for(int i=0;i<DIM_STRING;i++){
		s->stringa[i] = 'A' + (rand () % 26) ; // Valore casuale da 'A' a 'Z' per DIM volte
	}
	printf("Valore Prodotto(char stringa[DIM])= [%s]\n", s->stringa);//STRINGA(CHAR) DI DIMENSIONE DIM
	/*.....................*/	
	
	s->buffer_occupato = 1;
	s->buffer_libero = 0;

	signal_condition( & (s->m), Varcond_Consumatori);
	
	leave_monitor( & (s->m) );
	
}

void Consumatore(SingleBuff* s){
	
	enter_monitor( & (s->m) );
		
	while(s->buffer_libero ==1){
		wait_condition(&(s->m),Varcond_Consumatori);	
	}
	
	s->buffer_libero=1;
	s->buffer_occupato=0;
	
	printf("\n");	
			/* PER VALORE (int intero)*/	
	printf("Valore Consumato(int intero) = [%d]\n", s->intero);
	/*.....................*/	

			/* PER VALORE (char carattere)*/	
	printf("Valore Consumato(char carattere)= [%c]\n", s->carattere);
	/*.....................*/	
	
			/* PER VALORE (int array [DIM])*/	
	printf("Valore Consumato(int array[DIM])= ");
	for(int i=0;i<DIM_INT;i++) printf("[%d]", s->array[i]); 
	printf("\n");
	/*.....................*/	

			/* PER VALORE (char Stringa [DIM])*/	
	printf("Valore Consumato(char stringa[DIM])= [%s]\n", s->stringa);
	/*.....................*/		

	signal_condition( & (s->m), Varcond_Produttori);
			
	leave_monitor( & (s->m) );
	
}

/*.............END.............*/
