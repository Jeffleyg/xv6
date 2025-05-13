#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void cpu_bound() {
  int i, k;
  for(i = 0; i < 100; i++) {
    for(k = 0; k < 1000000; k++);
  }
}

void io_bound() {
  int i;
  for(i = 0; i < 100; i++) {
    sleep(1);
  }
}

int main() {
  int pid;

  printf("Testando escalonador com classes de prioridade...\n");

  // Processo classe 0 (alta prioridade)
  pid = fork();
  if(pid == 0) {
    setpriority(0);
    printf("Processo classe 0 iniciado (PID: %d)\n", getpid());
    cpu_bound();
    exit(0);
  }

  // Processo classe 1
  pid = fork();
  if(pid == 0) {
    setpriority(1);
    printf("Processo classe 1 iniciado (PID: %d)\n", getpid());
    cpu_bound();
    exit(0);
  }

  // Processo classe 2
  pid = fork();
  if(pid == 0) {
    setpriority(2);
    printf("Processo classe 2 iniciado (PID: %d)\n", getpid());
    io_bound();
    exit(0);
  }

  // Processo classe 3 (baixa prioridade)
  pid = fork();
  if(pid == 0) {
    setpriority(3);
    printf("Processo classe 3 iniciado (PID: %d)\n", getpid());
    cpu_bound();
    exit(0);
  }

  // Espera todos os processos filhos terminarem
  for(int i = 0; i < 4; i++) {
    wait(0);
  }

  printf("Teste concluído\n");
  exit(0);
  return 0;
}
