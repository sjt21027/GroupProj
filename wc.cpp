//
//  wc.cpp
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

int main(int argc, char* argv[]) {
  char buf[1];
  int z;
  int count = 0;
  int nl = 0;
  int words = 0;
  int fileDescriptor;

  if((fileDescriptor = open(argv[2], O_RDONLY)) < 2)
    perror("open error");
    
    
  bool cCMD = false;
  bool lCMD = false;
  bool wCMD = false;
  
   for (int i = 0; i < argc; i++){

    if (! strcmp(argv[i], "-c"))
      cCMD = true;

    if (! strcmp(argv[i], "-l"))
      lCMD = true;

    if (! strcmp(argv[i], "-w"))
      wCMD = true;
  }

  if(cCMD == true)
    while((z = read(fileDescriptor, buf, 1)) > 0)
      count++;


  z = lseek(fileDescriptor, 0, SEEK_SET);

  if(lCMD == true)
    while((z = read(fileDescriptor, buf, 1)) > 0)
      if(buf[0] == '\n')
        nl++;

  z = lseek(fileDescriptor, 0, SEEK_SET);

  if(wCMD == true){
    int charCounter = 0;
    while((z = read(fileDescriptor, buf, 1)) > 0){
      if(buf[0] != ' ' || buf[0] != '\n' || buf[0] != '\t'){
          charCounter++;
          cout << "Character number: " << charCounter << " ---> " <<  buf[0] <<  endl;
      }
      if(charCounter > 1 && (buf[0] == ' ' || buf[0] == '\n' || buf[0] == '\t')){
        words++;
        charCounter = 0;
      }
    }
  }

  cout << "Bytes: " << count << "\tNewLines: " << nl << "\tWord Count: " << words << endl;
  
  
return 0;
}
