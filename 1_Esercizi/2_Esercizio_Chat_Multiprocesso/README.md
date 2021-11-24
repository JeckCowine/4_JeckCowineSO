## Esercizio. Chat Multiprocesso

Scrivere un programma basato su code di messaggi UNIX per consentire la conversazione tra utenti del sistema. 

```c

[1]: Il programma deve essere un eseguibile che due utenti (su due terminali distinti) eseguono per poter conversare.
[2]: Il programma deve accettare in ingresso dalla linea di comando una coppia di caratteri da utilizzare
come identificativi delle code da usare per le conversazioni
es: "./chat a b" (Primo Terminale)  "./chat b a" (Secondo Terminale)
[3]: Il programma dovrà instanziare due processi figli, Mittente e Ricevente, dove:
"(MITTENTE)": esegue in loop in cui ad ogni iterazione si mette in attesa di una stringa dallo standart input
ed invia un messaggio con la stringa sulla prima coda. Quando l utente inserisce "exit"
il programma deve inviare un messaggio con una stringa "exit" sulla seconda coda e terminare

"(RICEVENTE)": esegue in loop in cui ad ogni iterazione si mette in attesa di un messaggio dalla seconda coda
e appena ricevuta stamperà sullo standart output la stringa ricevuta. In caso di ricezione della 
stringa "exit" dovrà terminare
```

![image](https://user-images.githubusercontent.com/93724872/143234187-26364783-5594-4445-8d3f-ae21bb58ab60.png)

1: Se un mittente ed un ricevente usano gli stessi caratteri di ingresso

es: **./chat a b (Primo Terminale)  ./chat a b (Secondo Terminale)**

essi devono poter comunicare tra loro usando le stesse code di messaggi condivise. 

Se invece un mittente e un ricevente usano caratteri di ingresso diversi,

es: **./chat a b (Primo Terminale)  ./chat b a (Secondo Terminale)**

essi useranno code diverse e non potranno comunicare tra loro. 
     
[2]: Si utilizzi la funzione scanf() per leggere una stringa dallo standard input.

```c
/*Chat.c*/
printf("Msg da inviare: ");	
scanf("%s",m.stringa); // Prelevo il messaggio da inviare		
```

La struttura struct contenente i tipi di messaggio da inviare:

```c
/*Chat.h*/
typedef struct {
	long tipo;		
	char stringa[20];	
}MailBox;
```

dove:

1: **long tipo** è il tipo del messaggio definito MESSAGGIO, dichiarata in Chat.h e richiamato in Chat.c

```c
/*Chat.h*/
#define MESSAGGIO 1
typedef struct {
	long tipo;
	
/*Chat.c*/
MailBox m; // Struct della Coda
m.tipo=MESSAGGIO;
}

```

2: **char stringa[20]**, un array di elementi di tipo ``char``contenente il messaggio da inviare e definito in Chat.c;

```c
/*Chat.c*/ 
MailBox m; // Struct della Coda
printf("Msg da inviare: ");				
scanf("%s",m.stringa);
```

La Coda di messaggi viene Creata all'interno del MainChat.c

```c
/*MainChat.c*/ 
int main(int argc, char *argv[]){
char PrimoArgomento = *argv[1];      // ./char (a) b
char SecondoArgomento = *argv[2]; // ./char a  (b)
key_t coda_invio  = ftok(".", PrimoArgomento);
int id_coda_invio = msgget(coda_invio, IPC_CREAT|0644);
if(id_coda_invio < 0) {perror("Msgget fallita");exit(1);}
key_t coda_ricevente = ftok(".", SecondoArgomento);
int id_coda_ricevente = msgget(coda_ricevente, IPC_CREAT|0644);
if(id_coda_ricevente < 0) {perror("Msgget fallita");exit(1);}
msgctl(id_coda_invio, IPC_RMID, 0);
msgctl(id_coda_ricevente, IPC_RMID, 0);
}
```

Le funzioni principali di funzionamento della Coda di messaggi sono:

```c
/*Chat.h*/
#define MESSAGGIO 1

/*Chat.c*/
void Mittente(MailBox m,int coda_ricevente, int coda_invio){
int check;
while(1){
m.tipo=MESSAGGIO;
// Verifico se il messaggio è exit
if(strcmp(m.stringa,"exit")==0){
	// Essendo exit, lo invio sulla seconda coda e termino
	check = msgsnd(coda_ricevente,&m, sizeof(MailBox)-sizeof(long),0);
	if(check<0) {perror("[Coda Mittente Eliminata]");_exit(1);}
	printf("[Invio Exit]: %s\n", m.stringa);
     _exit(1);
} else{
	// Non essendo exit, lo invio sulla prima coda
	check = msgsnd(coda_invio,&m,sizeof(MailBox)-sizeof(long),0);
    if(check<0) {perror("[Coda Mittente Eliminata]");_exit(1);}
	printf("[Mittente]: %s\n",m.stringa);
   }
 }
}

void Ricevente(MailBox m,int coda_ricevente){
int check;
while(1){
// Mi metto in attesa di un messaggio sulla seconda coda
	check = msgrcv(coda_ricevente,&m,sizeof(MailBox)-sizeof(long),MESSAGGIO,0);
	if(check<0) {perror("[Coda Ricevente Eliminata]");_exit(1);}
	// Se il messaggio ricevuto è exit termino
	if(strcmp(m.stringa,"exit")==0){printf("[Ricevuto Exit]: %s\n", m.stringa); _exit(1);}    
	else printf("[Ricevente]: %s\n",m.stringa);		
 }
}
```

Le stampe dell'invio del Messaggio sono fatte rispettivamenti in Chat.c

```c
/*Chat.c*/
//Mittente
if(strcmp(m.stringa,"exit")==0){
printf("[Invio Exit]: %s\n", m.stringa);
_exit(1);
}
if(strcmp(m.stringa,"exit")!=0){
printf("[Mittente]: %s\n",m.stringa);
}

//Ricevente
if(strcmp(m.stringa,"exit")==0){
printf("[Ricevuto Exit]: %s\n", m.stringa); 
_exit(1);}    
if(strcmp(m.stringa,"exit")!=0){
printf("[Ricevente]: %s\n",m.stringa);
}
```


Controllo dei valori inseriti nel terminale viene fatto nel MainChat.c

```c
/*MainChat.c*/
int main(int argc, char *argv[]){
// Controllo gli argomenti passati
if(argc< 2){
printf("Errore: Fornire come parametri di ingresso 2 caratteri separati da spazio\n");
printf("Esempio: %s a b\n", argv[0]);
_exit(1);
}
char PrimoArgomento = *argv[1];
char SecondoArgomento = *argv[2];
printf("I caratteri inseriti sono: %c %c\n", PrimoArgomento, SecondoArgomento);
}
```

Il Makefile è composto in questo modo: 

```Makefile
all: chat

chat: Chat.h
	gcc MainChat.c Chat.c -o chat 

clean:
	rm -f *.o
	rm -f ./chat
```

Per l'esecuzione del programma si usufruiscono di due terminali che parlano tra loro
[1]: ./chat a b

[2]: ./chat b a

Esecuzione Programma dai due terminali:
```[1] console                                                                [2] console
$ make                                                                            
gcc MainChat.c Chat.c -o chat                                       
$ ./chat a b                                                            $ ./chat b a 
I caratteri inseriti sono: a b                                          I caratteri inseriti sono: b a
Msg da inviare: Hi							Msg da inviare:
	[Mittente]: Hi							[Ricevente]: Hi
Msg da inviare: I'M															
	[Mittente]: I'M							[Ricevente]: I'M
Msg da inviare: Gianluca												
	[Mittente]: Gianluca						[Ricevente]: Gianluca
Msg da inviare: Covino													
	[Mittente]: Covino						[Ricevente]: Covino
Msg da inviare: I'M															
	[Mittente]: I'M							[Ricevente]: I'M		
Msg da inviare: Student												
	[Mittente]: Student						[Ricevente]: Student
Msg da inviare: of 															
	[Mittente]: of							[Ricevente]: of
Msg da inviare: the 
	[Mittente]: the							[Ricevente]: the	
Msg da inviare: Napoli
	[Mittente]: Napoli						[Ricevente]: Napoli
Msg da inviare: University
	[Mittente]: University						[Ricevente]: University
Msg da inviare: exit
[Invio Exit]: exit							[Coda Ricevente Eliminata]: Identifier removed
[Ricevuto Exit]: exit							exit
$ make clean								[Coda Mittente Eliminata]: Invalid argument
rm -f *.o
rm -f ./chat
```

