/************* MAIN_C ****************/

#include "CodaMessaggi.h"

int main(){
	
	pid_t pid;
	
	pid = fork();
	
	if(pid==0){
		
			execl("./p1","./p1",NULL);
			perror("Exec Fallita");
			exit(1);
		
	} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
	pid = fork();
	
	if(pid==0){
		
			execl("./p2","./p2",NULL);
			perror("Exec Fallita");
			exit(1);
		
	} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
	pid = fork();

	if(pid==0){
		
			execl("./p3","./p3",NULL);
			perror("Exec Fallita");
			exit(1);
		
	} else if(pid<0) { perror ("Errore Fork"); exit(1); }
	
	for(int i=0;i<NUM_PROCESSI;i++){
			wait(NULL);
	}
		
	return 0;
	
}


/****END****/


