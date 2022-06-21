#define PrintDone(cnt,cmd) \
  printf("\nRep Executed '%d' Times :\n\t%s\n\n",cnt,cmd)

#define PrintTooFewArgs() \
  printf("\n\t\033[1mNOT ENOUGH ARGUMENT...\033[0m\n");

#define PrintUsage()\
  printf("\n\
\"REP\" is a dead simple tool to\n\
 repeat a command X number of time\n\
\n\
\033[1mUsage :\033[0m\n\
\e[3mrep    RepeatCount    your command \e[0m\n\
  rep 16 echo Hello World\n\
\n\
\033[1mComplex commands (with pipes, semicolon or others),\n\
need to be enclosed in single or double quote  :\033[0m \n\
\e[3mrep    RepeatCount    \"your ; very | complex > command\" \e[0m\n\
  rep 32 \"head /dev/random | md5sum\"\n\
\n\
\033[1myou need to add backslash before each \n\
special character in your command\n\
or enclose it in single quote :\033[0m\n\
  rep 8 \"printf \\\"beep \\\\a \\\\n \\\" ; sleep 0.3\"\n\
  rep 8 \'printf \"beep \\a \\n\" ; sleep 0.3\'\n\
\n\
\033[1mif you dont want any output from Rep,\n\
only your command's output,set the\n\
ReapeatCount as negative : \033[0m\n\
\e[3mrep    -RepeatCount    your command \e[0m \n\
  rep -32 \"head /dev/random | md5sum\" | tee repRandom.txt\n\
\n\
\033[1mYou can access the current index via \n\
the environement variable $%1$s \033[0m\n\
  rep 16 echo Hello number \\$%1$s\n\
\n\
\033[1mthe RepeatCount 0 will repeat the command indefinitely\033[0m\n\
\n\
\033[1mif a command fail, it wont stop rep from continuing... \033[0m\n\
\n\033[1m\
rep wont stop on Ctrl+C if its your command's intended way to end\n\033[0m\
  commands that are normally terminated by the user\n\
  (vim, nano, htop, ...), would repeat when you\n\
  close them, so\033[1m only rep command that are terminated\n\
  automatically\033[0m (ls, cat, echo, ...), you could still \n\
  close rep by trying holding Ctrl+C, or closing\n\
  the terminal or by pid or htop or something\n\
\n\
\e[3mlook at the README.md in the installation folder\n\
or on github for more informations...\e[0m\n\n",envar)
