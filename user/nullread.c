// Teste A: leitura de ponteiro nulo deve matar o processo.
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  volatile int *p = 0;
  printf("Teste A: lendo de ponteiro nulo...\n");
  int v = *p;   // null dereference (leitura)
  printf("ERRO: leitura em NULL retornou %d (nao deveria chegar aqui)\n", v);
  exit(0);
}