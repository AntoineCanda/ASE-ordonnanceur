#include "try.h"
#include <stdio.h>
#include <assert.h>

int try(struct ctx_s *p_ctx, func_t *f, int arg)
{
	// associe le nombre magic
	p_ctx->magic = CTX_MAGIC;
  
	// on enregistre les donnees des registres esp et ebp dans la structure
	asm("movl %%esp, %0"
		"\n\t"
		"movl %%ebp, %1"
		:"=r"(p_ctx->esp), "=r"(p_ctx->ebp));
	
	// on affiche le resultat
	printf("esp: %p\n", p_ctx->esp);
	printf("ebp: %p\n", p_ctx->ebp);

	// on retourne la fonction f utilisant en argument arg 
	return f(arg);
}

int throw(struct ctx_s *p_ctx, int r)
{
  static int res;
  res = r;

  // test magic
  assert(p_ctx->magic == CTX_MAGIC);
  
  // restaure le contexte
  asm("movl %0, %%esp"
      "\n\t"
      "movl %1, %%ebp"
      ::"r"(p_ctx->esp), "r"(p_ctx->ebp));
  
  // On retourne res
  return res;
}

