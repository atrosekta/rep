#include "core.h"

bool NotEnoughArgs(int argn) {
  if (argn < 3) {
    PrintTooFewArgs();
    PrintUsage();
    return true;
  }
  return false;
}

int RepeatCountFromArgs(char*arg){
  if(arg[0] == '-')
    print=!print;
  if(arg[int(!print)] == '0')
    return -1;
  return abs( atoi(arg) );
}

char * CmdFromArgs(int argn, char *args[]) {
  int startindex = 2;

  if(argn-startindex == 1)
    return args[startindex];

  int totlen = -1;
  for (int i = startindex; i < argn; i++)
    totlen += strlen(args[i]) + 1;

  char *cmd = new char[totlen];
  for (int i = startindex; i < argn; i++) {
    strcat(cmd, args[i]);
    if (i < argn - 1)
      strcat(cmd, " ");
  }
  return cmd;
}

char envalbuff[12];
void SetEnvVar(int i){
  sprintf(envalbuff, "%d", i);
  setenv(envar, envalbuff, 1);
}

int PerformXtimes(int cnt,char*cmd){
  int i = 0;
  while (i != cnt){
    SetEnvVar(i + envVarOffset);
    int result = system(cmd);
    i++;
    if(WIFSIGNALED(result))
      break;
  }
  return i;
}

