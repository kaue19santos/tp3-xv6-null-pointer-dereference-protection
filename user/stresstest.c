// Teste E: stress basico de criacao/encerramento de processos.
// Verifica que nao ha leak visivel apos muitos fork/exit/wait.
#include "kernel/types.h"
#include "user/user.h"

#define NROUNDS 50

int
main(int argc, char *argv[])
{
  int i;
  int pid;
  int status;

  printf("Teste E: stress de processos (%d rounds)\n", NROUNDS);

  for (i = 0; i < NROUNDS; i++) {
    pid = fork();
    if (pid < 0) {
      printf("  fork falhou no round %d\n", i);
      exit(1);
    }
    if (pid == 0) {
      // Filho: faz um pouco de trabalho e sai
      volatile int x = 0;
      for (int j = 0; j < 1000; j++)
        x += j;
      exit(0);
    }
    // Pai: espera filho terminar
    wait(&status);
    if (status != 0) {
      printf("  filho saiu com status %d no round %d\n", status, i);
      exit(1);
    }
  }

  // Agora testa criacao de varios filhos simultaneos
  printf("  criando 10 filhos simultaneos... ");
  for (i = 0; i < 10; i++) {
    pid = fork();
    if (pid < 0) {
      printf("fork falhou\n");
      exit(1);
    }
    if (pid == 0) {
      exit(0);
    }
  }
  // Coleta todos
  for (i = 0; i < 10; i++) {
    wait(&status);
  }
  printf("OK\n");

  printf("Teste E: PASSOU (%d rounds + 10 simultaneos sem leak visivel)\n",
         NROUNDS);
  exit(0);
}
