
#include "Header.h"

void Set_Dati(Struct* c) {

	printf("\n\t<INIT MONITOR>\n\n");
	
	init_monitor(&(c->m), 2); //2= Varcond_Prod, Varcond_Cons
	
	printf("\t<AVVIO COMPILAZIONE>\n\n");
	printf("\t\t\tArray   Stringa\n");
	
	c->testa=0;
	c->coda=0;
	c->buffer[DIM]=0;	
	c->buffer2[DIM]='0';
	c->numero_elementi=0;
	
}

void Remove_Dati(Struct* c,int ds_shm){
	
	shmctl(ds_shm,0,IPC_RMID);
	remove_monitor( & (c->m) );
    
    printf("\n\t\t<FINE>\n");
	
}   

void Produzione(Struct* c) {
    
	if(c->numero_elementi==DIM){
		enter_monitor( & (c->m) );
		wait_condition( &(c->m), Varcond_Produttori);
	}
	
       //PRODUZIONE IN TESTA DELLA CODA
	
	Array val_1={0}; Stringa val_2="0";
	
    val_1[0] = 100 + rand () % 899; 
	c->buffer[c->testa]= val_1[0]; 
		
	val_2[0] = 'A' + (rand () % 26); 
	c->buffer2[c->testa]= val_2[0]; 
		
	c->testa = (c->testa+1) % DIM;
	c->numero_elementi= c->numero_elementi+1;
	
	printf("Prodottuttore [%d] = [%d]--[%s]\n",getpid(), val_1[0],val_2);	
			  
	if(c->numero_elementi>1){
	signal_condition( & (c->m), Varcond_Consumatori);
	leave_monitor( & (c->m) );
	}
	
}

void Consumazione(Struct* c) {
    
    if(c->numero_elementi<2){
		enter_monitor( & (c->m) );
		wait_condition( &(c->m), Varcond_Consumatori);
	}
		
        //CONSUMAZIONE IN CODA
	
	Array val_1={0},val_3={0};
	Stringa val_2="0",val_4="0";
		
	val_1[0]=c->buffer[c->coda];
	val_2[0]=c->buffer2[c->coda];
 	      		
	c->coda = (c->coda + 1) % DIM;

	val_3[0]=c->buffer[c->coda];
	val_4[0]=c->buffer2[c->coda];
 	      		
	c->coda = (c->coda + 1) % DIM;
	c->numero_elementi=c->numero_elementi - 2;
	
	printf("Consumatore   [%d] = [%d]--[%s]\n\t\t\t [%d]--[%s]\n",getpid(), val_1[0],val_2,val_3[0],val_4);	

	signal_condition( & (c->m), Varcond_Produttori);
	leave_monitor( & (c->m) );
		    
}

