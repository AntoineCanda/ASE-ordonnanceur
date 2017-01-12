#define TIMER_IRQ 2

#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "hw_config.h"
#include "contexte.h"
#include "sem.h"

struc sem_s fourchette1, fourchette2, fourchette3, fourchette4, fourchette5;

static void
empty_it(void)
{
    return;
}

static void
timer_it() {
	
   printf("time up");
   _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */
	yield();

}

void philo1(){
	while(1){
		sem_down(&fourchette1);
		printf("Le philosophe 1 prend la fourchette à sa droite.\n");
		sem_down(&fourchette5);
		printf("Le philosophe 1 prend la fourchette à sa gauche.\n");
		sem_up(&fourchette1);
		sem_up(&fourchette5);
		printf("Le philosophe 1 a mange et repose les deux fourchettes.\n");
		printf("Le philosophe 1 pense a tout et n'importe quoi mais surtout n'importe quoi.\n");
	}		
}

void philo2(){
	while(1){
		sem_down(&fourchette5);
		printf("Le philosophe 2 prend la fourchette à sa droite.\n");
		sem_down(&fourchette4);
		printf("Le philosophe 2 prend la fourchette à sa gauche.\n");
		sem_up(&fourchette5);
		sem_up(&fourchette4);
		printf("Le philosophe 2 a mange et repose les deux fourchettes.\n");
		printf("Le philosophe 2 pense a tout et n'importe quoi mais surtout n'importe quoi.\n");
	}		
}

void philo3(){
	while(1){
		sem_down(&fourchette4);
		printf("Le philosophe 3 prend la fourchette à sa droite.\n");
		sem_down(&fourchette3);
		printf("Le philosophe 3 prend la fourchette à sa gauche.\n");
		sem_up(&fourchette4);
		sem_up(&fourchette3);
		printf("Le philosophe 3 a mange et repose les deux fourchettes.\n");
		printf("Le philosophe 3 pense a tout et n'importe quoi mais surtout n'importe quoi.\n");
	}		
}
void philo4(){
	while(1){
		sem_down(&fourchette3);
		printf("Le philosophe 4 prend la fourchette à sa droite.\n");
		sem_down(&fourchette2);
		printf("Le philosophe 4 prend la fourchette à sa gauche.\n");
		sem_up(&fourchette3);
		sem_up(&fourchette2);
		printf("Le philosophe 4 a mange et repose les deux fourchettes.\n");
		printf("Le philosophe 4 pense a tout et n'importe quoi mais surtout n'importe quoi.\n");
	}		
}

void philo5(){
	while(1){
		sem_down(&fourchette2);
		printf("Le philosophe 5 prend la fourchette à sa droite.\n");
		sem_down(&fourchette1);
		printf("Le philosophe 5 prend la fourchette à sa gauche.\n");
		sem_up(&fourchette2);
		sem_up(&fourchette1);
		printf("Le philosophe 5 a mange et repose les deux fourchettes.\n");
		printf("Le philosophe 5 pense a tout et n'importe quoi mais surtout n'importe quoi.\n");
	}		
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
	
	// Initialise les contextes
	create_ctx(16384, philo1, NULL);
	create_ctx(16384, philo2, NULL);
	create_ctx(16384, philo3, NULL);
	create_ctx(16384, philo4, NULL);
	create_ctx(16384, philo5, NULL);

	// Initialise les semaphores
	sem_init(&fourchette1,1);
	sem_init(&fourchette2,1);
	sem_init(&fourchette3,1);
	sem_init(&fourchette4,1);
	sem_init(&fourchette5,1);
	
	yield();
	
	return 0;
}