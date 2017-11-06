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
  int count = 0, masterCount = 0;
  int nl = 0,masterNL = 0;
  int words = 0, masterWords = 0;
  int fileDescriptor;

    
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

   if(cCMD == true){

     for(int i = 2; i < argc; i++){
       if((fileDescriptor = open(argv[i],O_RDONLY))< 2)
	 perror("open error");

       while((z = read(fileDescriptor, buf, 1)) > 0){
	 if(z == -1)
	   perror("read error");
	 count++;
       }
       cout << count << " " << argv[i] << endl;
       masterCount += count;
       count = 0;
     }
     if(argc > 3)
       cout << masterCount << " total" << endl;
   }


  z = lseek(fileDescriptor, 0, SEEK_SET);

  if(lCMD == true){

    for(int i = 2; i < argc; i++){
      
      if((fileDescriptor = open(argv[i], O_RDONLY)) < 2)
	perror("open error");

      while((z = read(fileDescriptor, buf, 1)) > 0){
	if(z==-1)
	  perror("read error");
	if(buf[0] == '\n')
	  nl++;
      }
      cout << nl << " " << argv[i] << endl;
      masterNL += nl;
      nl = 0;
    }
    if(argc > 3)
       cout << masterNL << " total" << endl;
  }
  z = lseek(fileDescriptor, 0, SEEK_SET);

   if(wCMD == true){

     for(int i = 2; i < argc; i++){
       
       if((fileDescriptor = open(argv[i], O_RDONLY)) < 2)
	 perror("open error");
       
       int charCounter = 0;
       while((z = read(fileDescriptor, buf, 1)) > 0){
	 if(!isspace(buf[0])){
	   charCounter++;
//          cout << "Character number: " << charCounter << " ---> " <<  buf[0] <<  endl;
	 }
	 if(charCounter > 0 && z <= 0)
	   words++;
	 if(charCounter > 0 && (isspace(buf[0])     ) ){
	   words++;
	   charCounter = 0;
	 }
       
       }

       cout << words << " " << argv[i] << endl;
       masterWords += words;
       words = 0;
     }
     if (argc > 3)
       cout << masterWords << " total" << endl;
  }

 
  
return 0;
}
