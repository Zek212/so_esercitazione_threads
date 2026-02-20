#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void StackInit(Stack * s, int dim) {

	/* TBD: Inizializzare mutex e variabili condition */
	
	pthread_mutex_init(&s->mutex, NULL);
	pthread_cond_init(&s->vuoto, NULL);
	pthread_cond_init(&s->pieno, NULL);

	/* Il costruttore crea in memoria dinamica (heap)
	 * l'area di memoria per ospitare gli elementi dello stack.
	 * Il parametro "dim" indica il numero massimo di elementi.
	 */
	
	
	
	s->dati = (Elem *) malloc(sizeof(Elem)*dim);

	s->dim = dim;
	s->testa = 0;
}


void StackRemove(Stack * s) {

	/* TBD: Disattivare mutex e variabili condition */

	pthread_mutex_destroy(&s->mutex);
	pthread_cond_destroy(&s->pieno);
	pthread_cond_destroy(&s->vuoto);

	free(s->dati);
}

void StackPush(Stack * s, Elem e) {

	/* TBD: Aggiungere la sincronizzazione */
	pthread_mutex_lock(&s->mutex);
	
	while(s->testa==s->dim){
	pthread_cond_wait(&s->pieno, &s->mutex);
}
	s->dati[s->testa] = e;
	s->testa++;


	printf("Inserimento: %d\n", e);

	pthread_cond_signal(&s->vuoto);
	pthread_mutex_unlock(&s->mutex);

}


Elem StackPop(Stack * s) {

	int elemento;

	/* TBD: Aggiungere la sincronizzazione */

	pthread_mutex_lock(&s->mutex);
	while(s->testa==0){
	pthread_cond_wait(&s->vuoto, &s->mutex);
}

	s->testa--;
	elemento = s->dati[s->testa];

	printf("Prelievo: %d\n", elemento);

	pthread_cond_signal(&s->pieno);
	pthread_mutex_unlock(&s->mutex);
	return elemento;
}

int StackSize(Stack * s) {

	int size;

	/* TBD: Aggiungere la sincronizzazione */
	pthread_mutex_lock(&s->mutex);
	size = s->testa;
	pthread_mutex_unlock(&s->mutex);
	return size;
}
