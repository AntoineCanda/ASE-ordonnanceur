 #include <assert.h>
#include <stdio.h>
#include "contexte.h"
#include <malloc.h>
#include "hardware.h"
#include "hw_config.h"

struct ctx_s * ctx_courant=NULL;
struct ctx_s* ctxs=NULL;

int init_ctx(struct ctx_s *p_ctx, int stack_size, func_t f, void *arg)
{
  p_ctx->magic = CTX_MAGIC;
  p_ctx->f = f;
  p_ctx->arg = arg;
  p_ctx->stack = malloc(stack_size) ;
  assert(p_ctx->stack != NULL);
  p_ctx->esp = p_ctx->stack + stack_size - sizeof(void*);
  p_ctx->ebp = p_ctx->stack + stack_size - sizeof(void*);
  p_ctx->etat = INIT;

  return 0;
}

int create_ctx(int stack_size, func_t f, void *arg)
{
  struct ctx_s* nouveau_ctx;
  nouveau_ctx = (struct ctx_s*)malloc(sizeof(struct ctx_s));
  assert(nouveau_ctx!=NULL);
  if(ctx_courant != NULL) ctxs = ctx_courant;
  if (ctxs==NULL) {
	ctxs = nouveau_ctx;
	ctxs->suivant = ctxs;
  } else {
	/* insertion la plus simple possible */
	nouveau_ctx->suivant = ctxs->suivant;
	ctxs->suivant = nouveau_ctx;
  }
 
  nouveau_ctx->magic = CTX_MAGIC;
  nouveau_ctx->f = f;
  nouveau_ctx->arg = arg;
  nouveau_ctx->stack = malloc(stack_size) ;
  assert(nouveau_ctx->stack != NULL);
  nouveau_ctx->esp = nouveau_ctx->stack + stack_size - sizeof(void*);
  nouveau_ctx->ebp = nouveau_ctx->stack + stack_size - sizeof(void*);
  nouveau_ctx->etat = INIT; 

  return 0;
}


void switch_to_ctx(struct ctx_s *ctx) {
	if (ctx_courant != NULL) {
		asm("movl %%esp, %0"
		"\n\t"
		"movl %%ebp, %1"
		:"=r"(ctx_courant->esp), "=r"(ctx_courant->ebp));
	}
	ctx_courant = ctx;
	assert(ctx->magic == CTX_MAGIC);
	asm("movl %0, %%esp"
		"\n\t"
		"movl %1, %%ebp"
		::"r"(ctx->esp), "r"(ctx->ebp));
	if (ctx_courant->etat == INIT) {
		ctx_courant->etat=ACTIVABLE;
		_out(TIMER_ALARM,0xFFFFFFFE); 
		_mask(1);
		ctx_courant->f(ctx_courant->arg);
		ctx_courant->etat=TERM;
		yield();
	} else if (ctx_courant->etat == ACTIVABLE) {
		_out(TIMER_ALARM,0xFFFFFFFE); 
		_mask(1);
		return;
	} else {
		assert(0);
	}
}

void yield() {
	_mask(3);
	struct ctx_s* ctx_term;
	struct ctx_s* prochain;
	if (ctx_courant != NULL) {
		prochain = ctx_courant->suivant;
		while (prochain->etat==TERM || prochain->etat==BLOCKED) {
			if (prochain->etat==TERM) {
				assert(ctx_courant != prochain);
				ctx_term = prochain;
				prochain = prochain->suivant;
				free(ctx_term->stack);
				free(ctx_term);
			} else {
				prochain = prochain->suivant;
			}
		} 
		switch_to_ctx(ctx_courant->suivant);
	} else {
		assert(ctxs != NULL);
		switch_to_ctx(ctxs);
	}
	_mask(1);
}


