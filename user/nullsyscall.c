// Teste C: passar ponteiro nulo para syscall que le memoria de usuario.
// A syscall deve falhar corretamente (retornar -1); kernel nao crasha.
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fd;

  printf("Teste C: ponteiro nulo em syscalls\n");

  // Tentar write() com buffer nulo
  printf("  write(1, NULL, 10)... ");
  int r = write(1, (void *)0, 10);
  printf("retornou %d (esperado -1)\n", r);

  // Tentar read() com buffer nulo
  printf("  read(0, NULL, 10)... ");
  // Abrir /README para ter algo para ler
  fd = open("README", 0);
  if (fd < 0) {
    printf("ERRO: nao conseguiu abrir README\n");
    exit(1);
  }
  r = read(fd, (void *)0, 10);
  printf("retornou %d (esperado -1)\n", r);
  close(fd);

  // Tentar exec() com path nulo
  printf("  exec(NULL, argv)... ");
  r = exec((char *)0, argv);
  printf("retornou %d (esperado -1)\n", r);

  // Tentar open() com path nulo
  printf("  open(NULL, 0)... ");
  r = open((char *)0, 0);
  printf("retornou %d (esperado -1)\n", r);

  printf("Teste C: PASSOU (kernel estavel, syscalls falharam corretamente)\n");
  exit(0);
}
