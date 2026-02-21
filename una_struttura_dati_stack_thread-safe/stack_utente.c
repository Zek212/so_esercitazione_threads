#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "stack.h"

void *Inserisci(void * s)
{

	int i;
	Elem v;


	for(i=0; i<4; i++) {

		v = rand() % 11;

		/* TBD: Effettuare un inserimento con StackPush() */
		
		StackPush(Stack*)s,v);

		int size =  StackSize(Stack*)s); /* TBD: Chiamare il metodo StackSize() */
		printf("Dimensione: %d\n", size);
	 
		sleep(1);
	}

	pthread_exit(NULL);
}


void *Preleva(void * s)
{

	int i;
	Elem v1, v2;


	for(i=0; i<10; i++) {

		/* TBD: Prelevare con StackPop() in v1 */

		v1=StackPop(Stack*)s);

		/* TBD: Prelevare con StackPop() in v2 */
		v2=StackPop(Stack*)s);
		printf("Somma: %d\n", v1+v2);

		int size = Stacksize(Stack*)s); /* TBD: Chiamare il metodo StackSize() */
		
		printf("Dimensione: %d\n", size);

		sleep(3);
	}

	pthread_exit(NULL);

}


int main(int argc, char *argv[])
{

	int rc;
	int i;

	srand(time(NULL));


	Stack * stack =(Stack*)malloc(sizeof(Stack));

	/* TBD: Inizializzare lo stack con StackInit(),
	 *      indicando "4" come dimensione massima */

	StackInit((Stack*)s, 4);

	pthread_t t[5];

	for(i=0; i<5; i++) {

		/* TBD: Creare 5 thread tramite pthread_create(), facendogli
		 *      eseguire la funzione Inserisci(), e passandogli
		 *      l'oggetto stack come parametro puntatore */

			pthread_create(&t[i], NULL, Inserisci(),( void *) stack);	
	}


	pthread_t preleva_t;

	/* TBD: Creare un thread, facendogli eseguire la funzione Preleva(),
	 *      e passandogli l'oggetto stack come parametro puntatore */

	pthread_create(&preleva_t, NULL, Preleva(), (void* stack);

	for(i=0; i<5; i++) {

		/* TBD: Effettuare la join con i thread figli
		 *      che hanno eseguito Inserisci() */

	pthread_join(t[i],NULL );
	}


	/* TBD: Effettuare la join con il thread figlio
	 *      che ha eseguito Preleva() */
	pthread_join(preleva_t, NULL);

	/* TBD: Disattivare l'oggetto stack con StackRemove(),
	 *      e deallocarlo dalla memoria */

		StackRemove(stack);
		free(stack);
}

