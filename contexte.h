#define CTX_MAGIC 0xDEADBEEF
#define EXIT_SUCCESS 0

typedef void (*func_t)(void*);

struct ctx_s{
  void* esp;
  void* ebp;
  unsigned magic;
  func_t f;
  void* arg;
  void* stack;
  enum {INIT,ACTIVABLE,TERM, BLOCKED} etat;
  struct ctx_s* suivant;
  struct ctx_s* suivant_sem;
};

int init_ctx(struct ctx_s *p_ctx, int stack_size, func_t f, void *arg);
int create_ctx(int stack_size, func_t f, void *arg);
void switch_to_ctx(struct ctx_s *ctx);
void yield();
