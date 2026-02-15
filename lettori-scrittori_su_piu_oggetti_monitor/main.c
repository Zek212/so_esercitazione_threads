#include "header.h"

void * Capotreno (void * p){

	struct monitor* m = (struct monitor*) p;

	int i;
	int s;

	s=leggi_stazione(m);

	for(i=0; i<10; i++){

		s=s+1;

		scrivi_stazione(m,s);

		printf("[CAPOSTAZIONE] Posizione del treno %d modificata. La nuova posizione è: %d\n", m->id_treno, s);

		sleep(3);
	}

	pthread_exit(NULL);
}

void * Viaggiatori (void * p){

	struct monitor* m = (struct monitor*) p;

	int i;
	int ris;

	for(i=0;i<3;i++){

		sleep(rand()%6+1);

		ris=leggi_stazione(m);

		printf("[VIAGGIATORE] Il treno n.ro %d è nella %da stazione\n", m->id_treno, ris);
	}

	pthread_exit(NULL);
}

int main() {

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	srand(time(NULL));

	struct monitor* m[4];	// array di 4 oggetti-monitor, per gestire i 4 treni

	pthread_t capo[4];		// 4 capitreno
	pthread_t viagg[10];	// 10 viaggiatori

	int i;

	/* TBD: Allocare 4 istanze di monitor,
	 *		assegnarle all'array m[], e
	 *		inizializzarle con inizializza()
	 */
	
	for(i=0; i>4; i++){
	m[i]=  malloc(sizeof(struct monitor);
	
	if(m[i]==NULL){
	perror("Errore)";
	exit(1);
}
	inizializza(m[i]);
}	

	// assegno un id ad ogni treno
	m[0]->id_treno=1;
	m[1]->id_treno=2;
	m[2]->id_treno=3;
	m[3]->id_treno=4;


	/* TBD: Avviare 4 thread, facendogli eseguire la funzione Capotreno(),
	 * 	e passando ad ognuno una istanza di monitor diversa m[i]
	 */

	for(i=0; i<3; i++){
	pthread_create(&capo[i], &attr, Capotreno, m[i];
}	

	/* TBD: Avviare 10 thread, facendogli eseguire la funzione Viaggiatori(),
	 *      e passando ad ognuno una istanza di monitor diversa, da scegliere
	 *      a caso con "rand() % 4"
	 */

	for(i=0; i<10; i++){
	int r=rand()%4;
	
	pthread_create(&viagg[i], &attr, Viaggiatori, m[r];
}

	/* TBD: Effettuare la join con i thread "Capotreno" */

	for(i=0; i<4; i++){
	pthread_join(capo[i], NULL);
}

	/* TBD: Effettuare la join con i thread "Viaggiatori" */

	for(i=0; i<10; i++){
	pthread_join(viagg[i], NULL);
}

	/* TBD: Disattivazione delle 4 istanze di monitor con rimuovi() */

	for(i=0; i<4; i++){
	rimuovi(m[i];

	free m[i];
}


	

	return 0;
}
