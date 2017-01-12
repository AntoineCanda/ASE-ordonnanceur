#include <stdio.h>


int display_stack()
{
	void *esp;
	void *ebp;
	
	// code assembleur pour acceder aux registres %bsp et %esp.
	asm("movl %%esp, %0"	
		"\n\t"
		"movl %%ebp, %1"
		:"=r"(esp), "=r"(ebp));
	
	//affichage des valeurs des registres esp et ebp
	printf("valeur de esp = %p\n", esp);
	printf("valeur de ebp = %p\n", ebp);


	return 0;
}

int multiplie (int a, int b)
{
	// affichage des adresses des variables a et b 
	printf("adresse de a dans multiplie = %p\n", &a);
	printf("adresse de b dans multiplie = %p\n", &b);
	
	display_stack();
	
	return a*b;
}

int multiplie_trois (int a, int b, int c)
{
	
	// affichage des adresses des variables a et b 
	printf("adresse de a dans multiplie_trois = %p\n", &a);
	printf("adresse de b dans multiplie_trois = %p\n", &b);
	printf("adresse de c dans multiplie_trois = %p\n", &c);
	
	display_stack();
	
	return multiplie(a,b)*c;
}

int main()
{
	display_stack();
	
	multiplie_trois(2,3,4);
	return 0;
}

  
