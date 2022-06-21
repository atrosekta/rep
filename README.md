# REP is a dead simple tool to repeat a command a given number of times on linux

- your command have access to the current index via an environement variable.

- can disable its output to only output your commands (for piping or something).

- can repeat a command indefinitely.

- has a `make install` or `make symlink` command to compile it and make it available system wide.

- wrote in vanilla c++ with very minimal includes so it compile pretty much instantly without any special argument  : `g++ main.cpp`

---

## Table of content

- [Usage](#usage)

- [Customize](#customization)

- [Install](#installation)

- [Uninstall](#uninstall)

- [Worth Mentioning / Known Issue](#worth-mentioning-and-known-issues)

---

## Usage

rep is made to be as handy as possible so you just need to give it a number and a command : 

> *rep        repeatCount        your Command*  
>           `rep 10 echo Hello World`   
>             //print *Hello World* 10 times

but there is rules in some special cases :

- #### complex commands
  
  complex commands (that contain a pipe, a semiconon or something) need to be enclosed in quotes or double quotes :
  
  >           *rep        repeatCount        "your ; very | complex > command"*  
  >           `rep 16 "head /dev/random | md5sum"`  
  >               //print 16 random password

- #### special characters
  
  if your command contains special characters (`'`, `"`, `$`, `\`, ...) you 'll need to add a backslash just before it. **Or** if you enclose your command in single quotes (`'`) you don't need the backslash (exept for the single quotes inside your command) :
  
  >          `rep 8 "printf \" beep \\a \\n \" ; sleep 0.3"`
  >          `rep 8 'printf "beep \a \n"; sleep 0.3'` //those are the same,
  >              //make a beep noise and print *beep* 8 times (with a 0.3s pause)

- #### minimal output
  
  by default rep will print how many time it performed which command (and some empty line for better reading). if you don't want any output from rep, only the output from your commands, just put a dash/minus before the repeatCount :
  
  >            *rep        -repeatCount        your command*  
  >            `rep -16 "head /dev/random | md5sum" | tee -a randhash.txt`  
  >               //print 16 password on screen and in randhash.txt without
  >                any message from rep

- #### infinity mode
  
  the repeatCount 0 will repeat the command  indefinitely until stopped :
  
  >           `rep 0 echo infiniprint`  
  >              //print *infiniprint* indefinitly  
  
  something else than a number wont trigger this mode, it simply wont run.

- #### accessing index
  
  you can access the current index as rep store it in an environement variable before executing each command ( $REPINDEX , range [0 to repeatCount - 1]  ) :
  
  >          `rep 16 echo hello number \$REPINDEX`  
  >              //print *hello number [current index]* 16 times  
  >          `touch empty.txt; rep 12 'cp empty.txt empty$REPINDEX.txt'`  
  >             //create an empty file and copy it 12 times with a unique name  
  
  the name and range of the environement variable can be changed (see the [Customization](#customization) section for this).

- #### alternative input
  
  you cannot directly pipe into rep but you can use `xargs` to to it :
  
  >          `echo 8 echo hello | xargs rep`    //same as  
  >          `echo echo hello | xargs rep 8`
  
  similarly, if the command you need to repeat become too long you could create a script that do your command and `rep ./yourscript` but it may be more convinient to just create a file (of any extension) and write your command inside, you can do it in how many lines you want but you should use the same syntax as if were wroting it in one line (with semicolon to separate the commands, but you dont need to add a backslash at the end of each line). then you can run :
  
  >         `xargs rep 10 < yourCommandFile`  
  >            //or give the repeatCount at the beginning of the file
  
  rep will maybe handle this natively in future changes

---

## Customization

after every change you need to reinstall the program with `make clean install` 
(or customize it before install).
all the changes mentioned here are done in the ***core.h*** file in the *sources* folder.

- you can ***change the environement variable name*** ( *$REPINDE*X by default ) at the line *n. 10*.

- you can ***set the range of the environement variable*** via an offset at line *n. 15*.  
  $repindex = index + offset$ , so if you set this number at *10* the range of the environement variable would be from [10 to repeatCount-1+10] .  
  maybe in the future i'll add a way to change it via an argument or something

- you can ***invert the behaviour of a negative repeatCount*** ( set the default as minimal output and the negative number to have the rep output, instead of the reverse) by changing the value from *true* to *false* at line *n. 20* 

the whole program is not very complex so you may be able to modify it a bit more than this to make it do exactly what you want

---

## Installation

###### In short :

> `git clone https://github.com/atrosekta/rep.git`  
> 
> `cd rep/`  
> 
> `make symlink` or `make install`  

###### But in more detail :

you 'll need a c++ compiler like `g++`, and optionally but preferably `make`.
you can change the target path for the executable at the second line of the file *makefile* but i recommand leaving it as it is.

1. download the repo and go into the folder, manually or with  
   `git clone https://github.com/atrosekta/rep.git` and `cd rep`

2. then ensure that you dont have any command already called *rep* as this would overwrite it (just run `rep` in your terminal and look for something like *command not found* )

3. if no *rep* command already exist you can run `make symlink` (or `make install` if you want to delete this folder afterward) then go to step 5

4. otherwise you 'll need to do change the name in the file *makefile* at the first line : just replace *rep* by a name you want that doesnt already exist, manually or with `sed -i '1s/rep/repname/g' makefile` ( with the name you choosed instead of *repname* ) then go to step 3, but if you dont want to use `make` you'll need to do manually what what *make install* do :
   
   - choose a name for the command (we 'll use *repname* for now so replace all insances of *repname* by your choosen name) 
   
   - run `g++ -o bin/repname sources/main.cpp` (other c++ compiler than g++ should work too)
     then you can run it with `bin/repname` but i prefer to run it from anywhere with just `repname`
   
   - for that we'll run ``sudo ln -fs `pwd`/bin/repname /usr/local/bin`` 
     but you could also copy or move the executable into a directory thay is in your $PATH, or even add the rep's bin directory to your \$PATH  
     (`make install`would copy the executable into */usr/local/bin*)

5. `rep 10 echo Enjoy !` if this say something like *command not found* then something went wrong ... 

6. now you can delete the rep folder if you've run `make install` or copied the executable but i recommend keeping it

---

## Uninstall

if you don't have the *rep* folder anymore go to the *Alternative Uninstall* section

1. go into the rep folder you downloaded, ensure that the name at the first line of the file *makefile* is the right name, if you installed it as *rep* or with a `make` command it should be ok

2. then run `make clean` , this will delete the command and the executable

3. then you can delete the folder if you want

###### Alternative Uninstall

if you don't have anymore the folder to run `make clean` you need to remove the rep command manually with something like `sudo rm /usr/local/bin/rep` note that if you changed the name or the path while installing, you'll need to modify the previous command accordingly

--- 

## Worth Mentioning and Known Issues

- should work in any Unix environement but not tested in all of them

- rep dont run your command simultaneously but one after the other

- if a command fails , it wont stop rep from continuing.

- *rep* is made to repeat command that should end automatically, if you repeat a command that is terminated by the user as normal way to end (vim, nano, htop, ...) then rep will repeat the command when you exit it, (because if you stop ( with *ctrl-c* or something ) a program that should end automatically, rep will detect it as an unintended way to end and so will stop executing, but for programs that are normally closed by the user, rep will detect it as if the command had ended normally and so will run it again until the repeatCount is reached...)
  so if you run `rep 0 vim` ( dont do it )  you'll have a vim that indefinitly reopen itself when you have finaly exited it...
  
  > **fix :**
  > don't run those program via rep,
  > if you've still done it, hardly hold ctrl-c and hope,  
  > if it didnt work you can still close the terminal,
  > if you cant, kill rep by process id, or htop or something,  
  > if none of these work , restart your machine as a good vim user,
  > and dont rep your mistakes.
  > 
  > you can also propose a way to handle them

---
