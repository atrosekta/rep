#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "print.h"



//this is the environement variable name
  const char * envar = "REPINDEX";


//this is the offset for the value of the environement variable  \
  (to change from range [0 to repeatCount -1] to [1 to repeatCount] set as 1)
  int envVarOffset = 0; 


//this say if rep print its output or not,  \
  (this value is inverted when you give a negative repeatCount)
  bool print = true;



