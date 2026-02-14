#include "header.h"


void inizializza(struct monitor* m){

	m->stazione=0;
	m->id_treno=0;

	/* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
	m->num_scrittori = 0;
	m->num_cv_scrittori = 0;
	m->num_lettori = 0;
	m->num_cv_lettori = 0;

	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->cv_scrittori, NULL);
	pthread_cond_init(&m->cv_lettori, NULL);
}

void rimuovi (struct monitor* m){

	/* TBD: Disattivare mutex e variabili condition */
	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->cv_scrittori);
	pthread_cond_destroy(&m->cv_lettori);
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_stazione(struct monitor* m, int stazione){

	/* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
	 *
	 * 		Utilizzare una variabile "num_cv_scrittori" per contare il numero
	 * 		di scrittori in attesa sulla variabile condition (da affiancare in aggiunta
	 * 		alla variabile "num_scrittori" dell'algoritmo).
	 *
	 * 		La variabile "num_cv_scrittori" deve essere incrementata subito prima
	 * 		di wait_cond(), e decrementata subito dopo di wait_cond().
	 */
	pthread_mutex_lock(&m->mutex);
	
	while (m->num_lettori >0 || m->num_scrittori >0){
	m->num_cv_scrittori++;

	pthread_cond_wait(&m->cv_scrittori, &m->mutex);

	m->num_cv_scrittori--;
}	
	m->num_scrittori=1;
	pthread_mutex_unlock(&m->mutex);

	// SCRITTURA
	m->stazione=stazione;
	printf("Scrittura: stazione=%d\n", stazione);

	pthread_mutex_lock(&m->mutex);
	
	m->num_scrittori=0;

	if(m->num_cv_scrittori>0){
	pthread_cond_signal(&m->cv_scrittori);	
}	else{
	pthread_cond_broadcast(&m->cv_lettori);
}
	pthread_mutex_unlock(&m->mutex);

}


//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_stazione(struct monitor* m){

	/* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
	 *
	 * 		Utilizzare una variabile "num_cv_lettori" per contare il numero
	 * 		di lettori in attesa sulla variabile condition (da affiancare in aggiunta
	 * 		alla variabile "num_lettori" dell'algoritmo).
	 *
	 * 		La variabile "num_cv_lettori" deve essere incrementata subito prima
	 * 		di wait_cond(), e decrementata subito dopo di wait_cond().
	 */

	pthread_mutex_lock(&m->mutex);

	while(m->num_scrittori>0){
	m->num_cv_lettori++;

	pthread_cond_wait(&m->cv_lettori, &m->mutex);

	m->num_cv_lettori--;
}
	m->num_lettori++;

	pthread_mutex_unlock(&m->mutex);

	// LETTURA
	int ris=m->stazione;
	printf("Lettura: stazione=%d\n", ris);

	pthread_mutex_lock(&m->mutex);

	m->num_lettori--;

	if(m->num_lettori==0  && m->num_cv_scrittori>0){
	pthread_cond_signal(&m->cv_scrittori);
}	

	pthread_mutex_unlock(&m->mutex);
	return ris;
}

