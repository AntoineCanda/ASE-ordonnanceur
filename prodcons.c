#define N 100
#include "hardware.h"
#include "hw_config.h"
#include "contexte.h"
#include "sem.h"

struct sem_s mutex, vide, plein;



void producteur () {
	objet_t objet;
	
	while (1) {
		produire_objet(objet);
		sem_down(&vide);
		sem_down(&mutex);
		mettre_objet(objet);
		sem_up(&mutex);
		sem_up(&plein);
	}
}

void consommateur () {
	objet_t objet;
	sem_down(&plein);
	sem_down(&mutex);
	retirer_objet(&objet);
	sem_up(&mutex);
	sem_up(&vide);
	utiliser_objet(objet);
}

int main(int argc, char const *argv[]){
	/* init hardware */
    if (init_hardware(HARDWARE_INI) == 0) {
	fprintf(stderr, "Error in hardware initialization\n");
	exit(EXIT_FAILURE);
    }
    
    /* dummy interrupt handlers */
    for (i=0; i<16; i++)
	IRQVECTOR[i] = empty_it;

    /* program timer */
    IRQVECTOR[TIMER_IRQ] = timer_it;    
    _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
    _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */

   /* allows all IT */
    _mask(1);
	// Initialisation des contextes
	create_ctx(16384, producteur, NULL);
	create_ctx(16384, consommateur, NULL);
	
	// Initialisation des semaphores
	sem_init(&mutex, 1);
	sem_init(&vide, N);
	sem_init(&plein, 0);
	
	yeild();
	
	return 0;
		
}