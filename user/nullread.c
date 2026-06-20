#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  volatile int *p = 0;
  printf("Tentando ler de ponteiro nulo...\n");
  int v = *p;   // null dereference (leitura)
  printf("Leitura em NULL retornou: %d (0x%x)\n", v, v);
  exit(0);
}