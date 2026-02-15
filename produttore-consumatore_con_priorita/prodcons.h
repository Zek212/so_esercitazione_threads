#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include <pthread.h>

#define DIM 3

typedef struct{

	int buffer[DIM];

	/* TBD: Aggiungere ulteriori variabili per la sincronizzazione */
	
	int testa;
	int coda;
	int contatore;
	
	pthread_mutex_t mutex;

	pthread_cond_t not_empty;
	pthread_cond_t not_full;

	pthread_cond_t ok_prio2; 

	int threads_prio1; //prod alta priorità sospesi
	int threads_prio2; //prod basa priorità sospesi   
} PriorityProdCons;


void inizializza_prod_cons(PriorityProdCons * p);
void produci_alta_prio(PriorityProdCons * p, int value);
void produci_bassa_prio(PriorityProdCons * p, int value);
int consuma(PriorityProdCons * p);
void rimuovi_prod_cons(PriorityProdCons * p);

#endif
