#include <stdio.h>
#include "try.h"
#include <assert.h>

static struct ctx_s p_ctx;

static int mul(int depth) { 
    	int i;    
	switch (scanf("%d", &i)) 
	{         
		case EOF : 
	            return 1; /* neutral element */         
		case 0 :            
	          	return mul(depth+1); /* erroneous read */         
		case 1 : 
			if (i) {
	                return i * mul(depth+1);
		        } else {
	                 	throw (&p_ctx, 0);             
			}     
	}
	assert(0);
	return(0);
}

int main()
{
    int product;

    printf("A list of int, please\n"); 
    product = try(&p_ctx, mul, 0);
    printf("product = %d\n", product); 
	
    return 0;
}
