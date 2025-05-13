#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"

extern uint64 sys_exit(void);

// uint64
// sys_exit(void)
// {
//   int n;
//   argint(0, &n);
//   exit(n);
//   return 0;  // not reached
// }
uint64
sys_setpriority(void)
{
  int class;
  argint(0, &class);
  if(class < 0 || class >= PRIORITY_CLASSES)
    return -1;

  struct proc *p = myproc();
  p->priority_class = class;

  switch(class) {
    case 0: p->tickets = CLASS0_TICKETS; break;
    case 1: p->tickets = CLASS1_TICKETS; break;
    case 2: p->tickets = CLASS2_TICKETS; break;
    case 3: p->tickets = CLASS3_TICKETS; break;
  }

  return 0;
}
uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  int x;
  argint(0, &x);
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
