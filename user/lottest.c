#include "kernel/types.h"
#include "user/user.h"

#define N 4

void waste_time(void){
  volatile unsigned long long i;
  for(i = 0; i < 300000000ULL; i++);   // ~curto p/ demo
}

int
main(void)
{
  for(int n = 0; n < N; n++){
    int cls = n;                 // 0,1,2,3
    if(fork(cls) == 0){
      printf("child %d (class %d) start\n", getpid(), cls);
      waste_time();
      printf("child %d (class %d) stop\n",  getpid(), cls);
      exit(0);
    }
  }
  while(wait(0) > 0);
  exit(0);
}
