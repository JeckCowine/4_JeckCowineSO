/*.............MAILBOXASINCRONA_H.............*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>

#define MESSAGGIO 1

#define Num_Consumatori 2 // Numero Consumatori
#define Num_Produttori 2     // Numero Produttori 

#define DIM_INT 3 // Dimensione Array
#define DIM_STRING 6 // Dimensione Stringa

typedef struct {
	
	long tipo;
	//VALORE DA PASSARE			
	int intero; //PER PASSARE VALORE INT
			    /*---oppure---*/
	int array[DIM_INT];//PER PASSARE VALORE INT
			    /*---oppure---*/
	char carattere;//PER PASSARE VALORE CHAR
			    /*---oppure---*/
	char stringa[DIM_STRING];//PER PASSARE VALORE CHAR
	
} MailBox;

void Set_Dati(MailBox);
void Remove_Dati(MailBox,int);
void Produttore(MailBox,int);
void Consumatore(MailBox,int);

/*.............END.............*/
