
#include "Header.h"


void Prova(int mess) {
	
	message m;
	
	int ret = msgrcv(mess,&m,sizeof(message) - sizeof(long),0,0);
    if (ret<0){ perror("Error msgsnd"); exit(-1);}

	printf("Receiver [%d]= [%d]--[%d,%d]--[%c]--[%s]\n",getpid(),m.intero,m.array[0],m.array[1],m.carattere,m.stringa);

}

