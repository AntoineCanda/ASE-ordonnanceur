#define SEMAGIC 0xDEADBEEF

struct sem_s {
	int compteur;
	struct ctx_s* ctxs_attente;
	int magic;
};

void sem_init(struct sem_s *sem, unsigned int val);
void sem_down(struct sem_s *sem);
void sem_up(struct sem_s *sem);