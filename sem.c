#include "contexte.h"
#include "sem.h"
#include <stdio.h>
#include <stdlib.h>

struct ctx_s *ctx_courant=NULL;

void sem_init(struct sem_s *sem, unsigned int val) {
	sem->compteur = val;
	sem->ctxs_attente = NULL;
	sem->magic = SEMAGIC;
}

void sem_down(struct sem_s *sem) {
	_mask(15);
	sem->compteur --;
	if (sem->compteur < 0) {
		ctx_courant->etat = BLOCKED;
		ctx_courant->suivant_sem = sem->ctxs_attente;
		sem->ctxs_attente = ctx_courant;
		yield();
	}
	_mask(1);
}

void sem_up(struct sem_s *sem) {
	_mask(15);
	sem->compteur ++;
	if (sem->compteur <= 0) {
		sem->ctxs_attente->etat = ACTIVABLE;
		sem->ctxs_attente = sem->ctxs_attente->suivant_sem;
	}
	_mask(1);
}