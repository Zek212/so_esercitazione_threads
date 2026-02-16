#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"


void inizializza_prod_cons(PriorityProdCons* p){

    /* TBD: Inizializzare tutte le variabili del monitor */

	p->testa=0;
	p->coda=0;
	p->contatore=0;
	p->threads_prio1=0;
	p->threads_pio2=0;	

	pthread_mutex_init(&p->mutex, NULL);
	pthread_cond_init(&p->not_empty, NULL);
	pthread_cond_init(&p->not_full, NULL);
	pthread_cond_init(&p->ok_prio2, NULL);
}

void rimuovi_prod_cons(PriorityProdCons* p){

    /* TBD: Disattivare mutex e variabili condition */
	pthread_mutex_destroy(&p->mutex);
	pthread_cond_destroy(&p->not_empty);
	pthread_cond_destroy(&p->not_full);
	pthread_cond_destroy(&p->ok_prio2);
}

void produci_alta_prio(PriorityProdCons* p, int value) {

	printf("Produttore tipo 1 accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     *
     *      Si introduca nel monitor una variabile "threads_prio_1"
     *      per contare il numero di produttori sospesi ad alta priorità.
     *p->*/

	pthread_mutex_lock(&p->mutex);
	
	while(p->count==DIM){
	p->threads_prio1++;
	pthread_cond_wait(&p->not_full, &p->mutex);
	p->threads_prio1--;
}	
	/* Produzione */

	p->buffer[p->coda] = value;
	p->coda=(p->coda+1)%DIM;
	p->count++;

	printf("Produttore tipo 1 ha prodotto %d\n", value);

	pthread_cond_signal(&p->not_empty);
	pthread_mutex_unlock(p->&mutex);


}




void produci_bassa_prio(PriorityProdCons* p, int value) {

	
	pthread_mutex_lock(&p->mutex);
	printf("Produttore tipo 2 accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
	 *
	 *      I produttori a bassa priorità devono sospendersi sia nel caso di vettore
	 *      di buffer già pieno, sia nel caso vi siano produttori ad alta priorità già
	 *      in attesa.
     *
     *      Si introduca nel monitor una variabile "threads_prio_2"
     *      per contare il numero di produttori sospesi a bassa priorità.
     */

	
	while(p->count==DIM || p->threads_prio1){
	p->threads_prio2++;
	pthread_cond_wait(&p->ok_prio2, &p->mutex);
	p->threads_prio2--;	

}	

	/* Produzione */
	value = 13 + (rand() % 12);
	p->buffer[p->coda] = value;
        p->coda = (p->coda+1)%DIM;
        p->count++;
	printf("Produttore tipo 2 ha prodotto %d\n", value);

	pthread_cond_signal(p->&not_empty);
	pthread_mutex_unlock(p->&mutex);
}




int consuma(PriorityProdCons* p){

	
	int value;
	pthread_mutex_lock(&p->mutex);
	printf("Consumatore accede al monitor\n");


    /* TBD: Implementare la sincronizzazione secondo lo schema del
     *      produttore-consumatore con vettore di buffer circolare.
     */


	

	/* Consumazione */

	while(p->count==0){
	pthread_cond_wait(&p->not_empty,&p->mutex);
}

	p->buffer[p->testa] =value;
	p->testa = (p->testa+1)%DIM;
	p->count++;	
	printf("Consumatore ha consumato %d\n", value);
	
	if(threads_prio1>0){
	pthreads_cond_signal(&p->not_full);
}else if{
	pthreads_cond_signal(&p->ok_prio2);
}
	pthread_mutex_unlock(&p->mutex);
	


	return value;
}

