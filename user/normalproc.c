// Teste D: processo com comportamento normal (sem null deref) deve funcionar.
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;
  int status;

  printf("Teste D: operacoes normais\n");

  // Teste de alocacao de memoria
  printf("  sbrk/malloc... ");
  char *mem = sbrk(4096);
  if (mem == (char *)-1) {
    printf("FALHOU\n");
    exit(1);
  }
  // Escrever e ler da memoria alocada
  mem[0] = 'O';
  mem[1] = 'K';
  mem[2] = '\0';
  printf("%s\n", mem);

  // Teste de fork/wait
  printf("  fork/wait... ");
  pid = fork();
  if (pid < 0) {
    printf("FALHOU\n");
    exit(1);
  }
  if (pid == 0) {
    // Processo filho
    printf("filho OK (pid=%d)\n", getpid());
    exit(0);
  }
  // Processo pai
  wait(&status);
  printf("  pai coletou filho (status=%d)\n", status);

  // Teste de I/O com pipe
  printf("  pipe... ");
  int fds[2];
  if (pipe(fds) < 0) {
    printf("FALHOU\n");
    exit(1);
  }
  char buf[4];
  write(fds[1], "OK\n", 3);
  close(fds[1]);
  read(fds[0], buf, 3);
  buf[3] = '\0';
  close(fds[0]);
  printf("%s", buf);

  printf("Teste D: PASSOU (operacoes normais funcionam)\n");
  exit(0);
}
