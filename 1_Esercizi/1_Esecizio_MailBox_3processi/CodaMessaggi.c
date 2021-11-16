/************* CODAMESSAGGI_H ****************/

#include "CodaMessaggi.h"

float GeneraValore(int MIN, int MAX){
		
		//GENERA VALORE DA UN MIN E UN MAX
		float x = (int) (int) (rand () + MIN) / (RAND_MAX / MAX);
		return x;

}

char GeneraCarattere(char CARATTERE,int MAX){
	
		//GENERA UN CARATTERE CASUALE
		char string = (char) (int) CARATTERE + (rand () % MAX);
		return string;

}

/****END****/
