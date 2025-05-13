#include "user.h"

int
main(int argc, char *argv[])
{
  setpriority(0);   // classe 0 = mais alta prioridade
  for(;;)           // carga infinita só p/ ver o escalonamento
    ;
  return 0;
}
