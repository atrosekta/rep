#include "core.cpp"

int main(int argn, char *args[]) {

  if (NotEnoughArgs(argn)) return 0;
  
  int cnt = RepeatCountFromArgs(args[1]);
  char * cmd = CmdFromArgs(argn, args);

  if(print) printf("\n");
  int timesdone = PerformXtimes(cnt,cmd);
  if(print) PrintDone(timesdone,cmd);
  
  return 0;
}
