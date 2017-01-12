#include "contexte.h"
#include <stdio.h>
#include <stdlib.h>

//struct ctx_s ctx_ping;
//struct ctx_s ctx_pong;

void f_ping(void *arg);
void f_pong(void *arg);

int main()
{
	//init_ctx(&ctx_ping, 16384, f_ping, NULL);
	//init_ctx(&ctx_pong, 16384, f_pong, NULL);
	//switch_to_ctx(&ctx_ping);
	
	create_ctx(16384, f_ping, NULL);
	create_ctx(16384, f_pong, NULL);
	yield();
	
	exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
	int i = 100;
	while (i>0) {
		printf("A");
		yield();
		printf("B");
		yield();
		printf("C");
		yield();
		i--;
	}
}

void f_pong(void *args)
{
	int i=50;
	while (i>0) {
		printf("1");
		yield();
		printf("2");
		yield();
		i--;
	}
}
