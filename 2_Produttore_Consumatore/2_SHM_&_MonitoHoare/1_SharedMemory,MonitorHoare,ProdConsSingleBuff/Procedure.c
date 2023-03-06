
#include "Header.h"

void Set_Dati(Struct* s){
	
	init_monitor(&(s->m), 2); //2= Varcond_Prod, Varcond_Cons
	
	s->intero=0;
	s->carattere='0';
	s->array[DIM]=0;
	s->stringa[DIM]='0';
	s->buffer_libero=1; // 1 se libero, 0 se pieno
	s->buffer_occupato=0; // 0 se libero, 1 se pieno
	
}

void Remove_Dati(Struct* s,  int ds_shm){
	
	shmctl(ds_shm, IPC_RMID, NULL); 
	remove_monitor( & (s->m) );
    
    printf("\n\t\t<FINE>\n");
	
}
void Produzione(Struct* s){

	enter_monitor( & (s->m) );
		
	if(s->buffer_occupato==1){
		wait_condition( &(s->m), Varcond_Produttori);
	}

	int val_1=0; char val_2='0'; Array val_3={0}; Stringa val_4="0";
		
	val_1 = 10 + rand () % 88; 
	s->intero = val_1;
	
	val_2 = 'A' + (rand () % 26) ; 
	s->carattere= val_2;
	
	val_3[0]= 10 + rand() % 88; 
	s->array[0] = val_3[0];
	val_3[1]= 10 + rand() % 88; 
	s->array[1] = val_3[1];
	
	for(int i=0;i<DIM;i++){ 
		val_4[i] = 'A' + (rand () % 26) ; 
		s->stringa[i] = val_4[i]; }
	
	printf("Prodottuttore [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(), val_1,val_3[0],val_3[1],val_2,val_4);
	
	s->buffer_occupato = 1;
	s->buffer_libero = 0;

	signal_condition( & (s->m), Varcond_Consumatori);
	
	leave_monitor( & (s->m) );
	
}

void Consumazione(Struct* s){
	
	enter_monitor( & (s->m) );
		
	if(s->buffer_libero ==1){
		wait_condition(&(s->m),Varcond_Consumatori);	
	}
	
	s->buffer_libero=1;
	s->buffer_occupato=0;
	
	int val_1=0; char val_2='0'; Array val_3={0}; Stringa val_4="0";
	
	val_1 = s->intero;
	val_2 = s->carattere;
	val_3[0] = s->array[0];
	val_3[1] = s->array[1];
	for(int i=0;i<DIM;i++) val_4[i] = s->stringa[i];
			
	printf("Consumatore   [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(), val_1,val_3[0],val_3[1],val_2,val_4);

	signal_condition( & (s->m), Varcond_Produttori);
			
	leave_monitor( & (s->m) );
	
}

/*.............END.............*/
