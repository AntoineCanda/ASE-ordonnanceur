#define CTX_MAGIC 0XDEADBEEF
#define EXIT_SUCCES 0
#include<stdio.h>

typedef int (func_t)(int);
struct ctx_s
{
	void* esp;
	void* ebp;
	unsigned magic;
};
int try(struct ctx_s *p_ctx, func_t *f, int arg);
int throw(struct ctx_s *p_ctx, int r);
