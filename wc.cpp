/*
 * wc.cpp 
 *	
 * This program replicates the wc unix word count utility
 * which copies its input to std output for a certain
 * length from the end. The optional parameter [-c] indicates
 * the number of characters to be printed while
 * [-l] indicates the count of lines in a file, and [-w] 
 * indicates the amount of words in a file. Otherwise,
 * standard input in executed and printed.
 * 
 * Owner: Steven Thompson - Gray Dunagan
 * 
 * Version: 11.6.17
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

/*
 * Main function -- 
 *
 * This function wil determine which argument to execute
 * and allow the program to determine the outcome
 * based off of that argument.
 *
 * @param argc the amount of arguments from the command line
 * @param argv[] the file in which to interpret as a argument
 */
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

    if(argc < 3){
       while (( z = read(STDIN_FILENO, buf,1)) > 0){
	 if(z==-1)
	   perror("read error");
	 count++;
       }
       cout << count << " "  << endl;
     }

     else{

     for(int i = 2; i < argc; i++){

       if((! strcmp(argv[i], "-"))){
	 while ((z = read(STDIN_FILENO, buf, 1)) > 0){
	     if(z==-1)
	       perror("read error");
	     count++;
	   }
	   cout << count << " " << "-" << endl;
	   masterCount += count;
	   count = 0;
       }

       else{
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
     }
     }
     if(argc > 3)
       cout << masterCount << " total" << endl;
   }


  z = lseek(fileDescriptor, 0, SEEK_SET);

  if(lCMD == true){

    if(argc < 3){
      while (( z = read(STDIN_FILENO, buf, 1)) > 0){
	if(z==-1)
	   perror("read error");
	if(buf[0] == '\n')
	  nl++;
      }
      cout << nl << " " << endl;
    }

    else{
    for(int i = 2; i < argc; i++){

      if((! strcmp(argv[i], "-"))){
	while ((z = read(STDIN_FILENO, buf, 1)) > 0){
	  if (z==-1)
	    perror("read error");
	  if(buf[0] == '\n')
	    nl++;
	}
	cout << nl << " "  << endl;
	masterNL += nl;
	nl = 0;
      }
      
      else{


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
    }
    }

    if(argc > 3)
       cout << masterNL << " total" << endl;
  }
  z = lseek(fileDescriptor, 0, SEEK_SET);
  int storageDescriptor;
  int charCounter = 0;
   if(wCMD == true){

     if(argc < 3){
       storageDescriptor = open("./temp", O_RDWR|O_CREAT, S_IRWXU);
       if(storageDescriptor == -1)
	 perror("open/create error");
       //write from stdin to temp fle
       while (( z = read(STDIN_FILENO,buf,1)) > 0){
	 if(write(storageDescriptor,buf,z) !=z)
	   perror("write error");
	 if(z<0)
	   perror("read error");
       }
       close(storageDescriptor);
       storageDescriptor = open("./temp", O_RDONLY);
       if(storageDescriptor == -1)
	 perror("open error");

       while (( z = read(storageDescriptor,buf,1)) > 0){
	 if(!isspace(buf[0]))
	   charCounter++;
	 if(charCounter > 0 && (isspace(buf[0]))){
	   words++;
	   charCounter = 0;
         }
       }
       cout << words << endl;
       if(remove("./temp") != 0)
	 perror("failure to delete file");
     }
     
     else{
     for(int i = 2; i < argc; i++){
       
       if((! strcmp(argv[i], "-"))) {
	 //create temp file
	 storageDescriptor = open("./temp", O_RDWR|O_CREAT, S_IRWXU);
         if(storageDescriptor == -1)
	   perror("open/create error");
	 //write from stdin to temp 
	 while (( z = read(STDIN_FILENO, buf, 1 )) > 0){
	     if(write(storageDescriptor, buf, z) != z)
	       perror("write error");
	     if(z<0)
	       perror("read error");
	   }
	   
	 close(storageDescriptor);
	 storageDescriptor = open("./temp", O_RDONLY);
	 if(storageDescriptor == -1)
	   perror("open error");
	 
	 while ((z = read(storageDescriptor,buf,1)) > 0){
	   if(!isspace(buf[0]))
	     charCounter++;
	   if(charCounter > 0 && (isspace(buf[0]))){
	     words++;
	     charCounter = 0;
	   }
	 }
	 cout << words << " " << "-" <<  endl;
	 masterWords += words;
	 words = 0;
	 if(remove("./temp") != 0)
	   perror("failure to delete file");
       }

      else{

	  if((fileDescriptor = open(argv[i], O_RDONLY)) < 2)
	    perror("open error");
            
	  while((z = read(fileDescriptor, buf, 1)) > 0){
	    if(!isspace(buf[0]))
	      charCounter++;
	  }

	  if(charCounter > 0 && (isspace(buf[0]))){
	    words++;
	    charCounter = 0;
	  }
      }

	cout << words << " " << argv[i] << endl;
	masterWords += words;
	words = 0;
     
     }
     }

     if (argc > 3)
       cout << masterWords << " total" << endl;
   }



 
  
return 0;
}
