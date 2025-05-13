#include "kernel/types.h"
#include "user/user.h"

#define N 4
const int CLASSES[N] = {0, 1, 2, 3};  // Classes de prioridade

void waste_time() {
  volatile unsigned long long i;
  for (i = 0; i < 3000000000ULL; i++);
}

int main() {
  int pids[N];
  for (int i = 0; i < N; i++) {
    int pid = fork(CLASSES[i]);  // Processos em classes diferentes
    if (pid == 0) {
      printf("Processo filho %d (classe %d)\n", getpid(), CLASSES[i]);
      waste_time();
      exit(0);
    } else {
      pids[i] = pid;
    }
  }

  for (int i = 0; i < N; i++) {
    wait(0);
    printf("Processo %d (classe %d) finalizado\n", pids[i], CLASSES[i]);
  }
  exit(0);
}
