/*
 * tail.cpp 
 *	
 * This program replicates the tail unix head utility
 * which copies its input to std output for a certain
 * length from the end. The optional parameter [-n] indicates
 * the number of liens to be printed while
 * [file...] indicates one or more files to
 * be printed.
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
 * This function prints from the standard input and print the "n" lines from
 * the end of the file
 *
 * @param n the integer amount of lines that will be printed from the bottom
 */
void printFromSTDIN(int n){
  int linesFromSTDIN = 0;
  char buf[1];
  int z;
  int storageDescriptor;
  
  // create temp file to store and read later	
  storageDescriptor = open("./temp", O_RDWR|O_CREAT, S_IRWXU);
  if(storageDescriptor ==-1)
    perror("open/create error in printFromSTDIN");

  //read 1 char at a time from STDIN
  while ((z = read(STDIN_FILENO, buf, 1)) > 0){

    //compare buff to newline "\n"
    //if newline, increment linesRead
    if ( buf[0]  == '\n' )
      linesFromSTDIN++;    
    if(write(storageDescriptor, buf, z) != z)
      perror("write error in printFromSTDIN");
    if (z < 0)
      perror("read error in printFromSTDIN");
  }

  close (storageDescriptor);

  if(linesFromSTDIN <=n){
    storageDescriptor = open("./temp", O_RDONLY);
    if(storageDescriptor == -1)
      perror("open error");
    while ((z = read(storageDescriptor, buf, 1)) > 0){
      if(write(STDOUT_FILENO, buf, z) != z)
	 perror("write error in printFromStdin");
      if(z<0)
	 perror("read error in printFromSTDIN");
    }
  }

  int linesRead = 0;

  if(linesFromSTDIN > n){
    storageDescriptor = open("./temp", O_RDONLY);
    if(storageDescriptor == -1)
      perror("open error");
    while ((z = read(storageDescriptor,buf,1)) >0){
      if(linesRead >= (linesFromSTDIN-n)){
	
	if(write(STDOUT_FILENO,buf,z)!=z)
	  perror("write error");
      } 
      if(buf[0] == '\n')
	linesRead++;
      if(z<0)
	perror("read error");
    }
  }
     
  if( remove("./temp") != 0)
    perror("failure to delete file");

}

/*
 * This function prints from the "fileName" file and print the "n" lines from
 * the end of the file
 *
 * @param n the integer amount of lines that will be printed from the bottom
 * @param fileName the file in which to use for this function.
 */
void printFromFileN(int n, char* fileName){
  int linesRead = 0;
  char buf[1];
  int y = 0;
  int z;
  int count = 0;
  int fileDescriptor;
  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in printFromFile");

  while ((z = read(fileDescriptor, buf, 1)) > 0){
    if (buf[0] == '\n')
      linesRead++;
  }

  lseek(fileDescriptor, 0, SEEK_SET);

  if (linesRead <= n){
    while ((y = read(fileDescriptor, buf, 1)) > 0 ){
      if(write(STDOUT_FILENO, buf, y) != y)
	perror("write error in printFromFileN");
       if(y<0)
         perror("read error in PrintFromFileN");
    }
  }

  else{
    z = lseek(fileDescriptor, 0, SEEK_SET);
    while ((z = read(fileDescriptor, buf, 1)) > 0){
      if (buf[0] == '\n')
	count++;

      if(count == (linesRead-n)){
	z = lseek(fileDescriptor, 0, SEEK_CUR);
	while((z = read(fileDescriptor, buf, 1)) > 0){
	  if(write(STDOUT_FILENO,buf,z) !=z)
	    perror("write error in printFileFromN");
	}
      }
    }
  }
}

/*
 * This is the main function
 *
 * @param argc the amount of arguments from the command line
 * @param argv[] the file in which to interpret as a argument
 */
int main(int argc, char* argv[]) {

  //default numLines is 10
  int n = 10;
  bool numLineParam = false;


  //check for -n parameter                                                                                 
  for (int i = 0; i < argc; i++){
    if (! strcmp(argv[i], "-n")){
      numLineParam = true;
      n = atoi (argv[i + 1]);
      if (n < 0){
        cout<< "n must be non-negative";
        exit(EXIT_FAILURE);
      }
    }
  }

 //if numLineParam,                                                                                       
  if (numLineParam == true){
    if (argc < 4)
      printFromSTDIN(n);
    else{
      for(int i = 3; i < argc; i++){
        if(! strcmp(argv[i], "-"))
          printFromSTDIN(n);
        else
          printFromFileN(n,argv[i]);
      }
    }
  }

  //if no  numLineParam                                                                                    
  else{
    if (argc < 2 )
      printFromSTDIN(n);
    else{
      for (int i = 1; i < argc; i++){
        if (! strcmp(argv[i], "-"))
          printFromSTDIN(n);
        else
          printFromFileN(n,argv[i]);
      }
    }
  }

  return 0;
}  
    
