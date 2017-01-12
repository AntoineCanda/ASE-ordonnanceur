#include "contexte.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "hw_config.h"
#define TIMER_IRQ 2


void f_ping(void *arg);
void f_pong(void *arg);

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

int main()
{
	 unsigned int i;
    
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

	create_ctx(16384, f_ping, NULL);
	create_ctx(16384, f_pong, NULL);
	yield();
	
	exit(EXIT_SUCCESS);
}



void f_ping(void *args)
{
	while (1) {
		printf("A");
		printf("B");
		printf("C");
	}
}

void f_pong(void *args)
{
	while (1) {
		printf("1");
		printf("2");
	}
}
