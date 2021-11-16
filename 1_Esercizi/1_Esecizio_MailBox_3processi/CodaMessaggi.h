/************* CODAMESSAGGI_H ****************/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>

#define MESSAGGIO 1
#define p1 1
#define p2 2
#define NUM_PROCESSI 3
#define DIM_MSG_p1 5
#define DIM_MSG_p2 5
#define DIM_INT 2
#define DIM_STRING 3

typedef struct {
	
	long tipo;
	
	float intero;
	char carattere;
	int array[DIM_INT];
	char stringa[DIM_STRING];
	
}Coda;

float GeneraValore (int,int);
char GeneraCarattere (char,int);

/****END****/
