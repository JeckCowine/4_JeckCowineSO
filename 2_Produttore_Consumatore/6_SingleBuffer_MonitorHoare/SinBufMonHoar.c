/*.............SINBUFMONHOAR_H..............*/

#include "SinBufMonHoar.h"

void Set_Dati(SingleBuff* s){
	
	init_monitor(&(s->m), 2); //2= Varcond_Prod, Varcond_Cons
	s->intero=0;
	s->buffer_libero=1; // 1 se libero, 0 se pieno
	s->buffer_occupato=0; // 0 se libero, 1 se pieno
	
}
void Remove_Dati(SingleBuff* s){
	
	remove_monitor( & (s->m) );
	s->intero=0;
	s->buffer_libero=1; // 1 se libero, 0 se pieno
	s->buffer_occupato=0; // 0 se libero, 1 se pieno
	
	
}
void Produttore(SingleBuff* s){

	enter_monitor( & (s->m) );
	
	if(s->buffer_occupato==1){
		wait_condition( &(s->m), Varcond_Produttori);
	}
	
	srand(getpid()*time(NULL));
	
	s->intero = 1 + rand () % 100;
	s->buffer_occupato = 1;
	s->buffer_libero = 0;
	
	printf("\nValore Prodotto(int intero) = [%d]\n", s->intero);
	
	leave_monitor( & (s->m) );
	
}

void Consumatore(SingleBuff* s){
	
	enter_monitor( & (s->m) );
		
	if(s->buffer_libero ==1){
		wait_condition(&(s->m),Varcond_Consumatori);	
	}
	
	s->buffer_libero=1;
	s->buffer_occupato=0;
	
	printf("\nValore Consumato(int intero) = [%d]\n", s->intero);
	
	leave_monitor( & (s->m) );
	
}

/*.............END.............*/
