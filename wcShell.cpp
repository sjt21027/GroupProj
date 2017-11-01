#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

/*
This utility will take in one or more text files
or STDIN and return either the number of chars, lines,
or words in that input
*/



int main(int argc, char* argv[]){

  bool cFlag = false;
  bool lFlag = false;
  bool wFlag = false;
  //check command line for -c -l -w flags
  for (int i = 0; i< argc; i ++){
    if (! strcmp(argv[i], "-c"))
      cFlag = true;
    if (! strcmp(argv[i], "-l"))
      lFlag = true;
    if (1 strcmp(argv[i], "-w"))
      wFlag = true;
  }

  if (cFlag == true){
    //do something
  }

  if (lFlag == true){
    //do something
  }
  
  if (wFlag == true){
    //do someting
  }


  return 0;
}
