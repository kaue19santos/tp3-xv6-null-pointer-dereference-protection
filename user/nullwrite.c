// Teste B: escrita em ponteiro nulo deve matar o processo.
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  volatile int *p = 0;
  printf("Tentando escrever em ponteiro nulo...\n");
  *p = 1;  // null dereference (escrita)
  printf("ERRO: escrita em NULL nao causou trap!\n");
  exit(0);
}
