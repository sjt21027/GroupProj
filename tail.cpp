//
//  main.cpp
//  P2
//
//  Created by this.p1.cpu(); on 10/30/17.
//  Copyright © 2017 this.p1.cpu();. All rights reserved.
//

/*
 This program replicates the tail unix head utility
 which copies its input to std output for a certain
 length from the end. The optional parameter [-n] indicates
 the number of liens to be printed while
 [file...] indicates one or more files to
 be printed.
*/
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cerrno>

using std::cout;
using std::endl;
using namespace std;

//print n number of lines from STDIN
//@param n num lines to be read
void printFromSTDIN(int n){
  int linesRead = 0;
  char buf[1];
  int z;
  //read 1 char at a time from STDIN
  while ((z = read(STDIN_FILENO, buf, 1)) > 0){

    //compare buff to newline "\n"
    //if newline, increment linesRead
    if ( buf[0]  == '\n' )
      linesRead++;
    
    if(write(STDOUT_FILENO, buf, z) != z)
      perror("write error in printFromSTDIN");

    if (z < 0)
      perror("read error in printFromSTDIN");

    if(linesRead == (n))
      return;
  }
}
//print n number of lines from a file
//@param n num lines to be read
//@param fileName file to be read from

void printFromFileC(int n, char* fileName){
  char buf[1];
  int z;
  int fileDescriptor;
  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in printFromFile");

  //read 1 char at a time from the file
  off_t pos = lseek(fileDescriptor, 0, SEEK_END);
  if(pos == -1) {
    perror("seek");
  }
  pos = lseek(fileDescriptor, (n-pos), SEEK_END);
  if(pos == -1){
    perror("seek2");
  }
  while ((z = read(fileDescriptor, buf, 1)) > 0){
    if(write(STDOUT_FILENO, buf, z) !=z)
      perror("write error in printFromFile");
    if (z<0)
      perror("read error in printFromFile");
  }
}

void printFromFileN(int n, char* fileName){
  int linesRead = 0;
  char buf[1];
  int z;
  int fileDescriptor;
  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in printFromFile");

  while ((z = read(fileDescriptor, buf, 1)) > 0){
    if (buf[0] == '\n')
      linesRead++;
    if(linesRead == n){
      while((z = read(fileDescriptor, buf, 1)) > 0){
        if(write(STDOUT_FILENO,buf,z) !=z)
          perror("write error in printFromFileN");
      }
    }
  }

}

int main(int argc, char* argv[]) {

  //default numLines is 10
  int n = 10;
  bool numLineParam = false;

  //check for -n parameter
  for (int i = 0; i < argc; i++){
    if (! strcmp(argv[i], "-n") | ! strcmp(argv[i], "-c")){
      numLineParam = true;
      n = atoi (argv[i + 1]);
      cout << "N value: " << n << endl;
      if (n < 0){
        cout<< "n must be non-negative";
        exit(EXIT_FAILURE);
      }
    }
  }

  //if numLineParam,
  if (numLineParam == true){
    if (argc < 4){
      printFromSTDIN(n);
    }else{
      for(int i = 2; i < argc; i++){
        if(! strcmp(argv[i], "-c")){
          cout << "Enter -c: " << endl;
          printFromFileC(n,argv[i]);
        }else if(! strcmp(argv[i], "-n")){
          cout << "Enter -n: " << endl;
          printFromFileC(n,argv[i]);
           }else if(! strcmp(argv[i], "-n")){
          cout << "Enter -n: " << endl;
          printFromFileC(n,argv[i]);
        }else{
          cout << "Enter STDIN: " << endl;
            printFromSTDIN(n);
        }
      }
    }
  }

  //if no  numLineParam
  else{
    if (argc < 2 )
      printFromSTDIN(n);
    else{
      for (int i = 1; i < argc; i++){
        if (! strcmp(argv[i], "-c"))
          printFromFileC(n, argv[i+1]);
        else if(! strcmp(argv[i], "-n"))
          printFromFileN(n,argv[i+1]);
        else
          printFromSTDIN(n);
      }
    }
  }

  return 0;
}  
    
