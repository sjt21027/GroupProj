/*
 * head.cpp 
 *	
 * This program replicates the head unix head utility
 * which copies its input to std output for a certain
 * length. The optional parameter [-n] indicates
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

using namespace std;

/*
 * This function prints from the standard input and print the "n" lines from
 * the start of the file
 *
 * @param n the integer amount of lines that will be printed from the top
 */
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

/*
 * This function prints from the "fileName" file and print the "n" lines from
 * the start of the file
 *
 * @param n the integer amount of lines that will be printed from the top
 * @param fileName the file in which to use for this function.
 */
void printFromFile(int n, char* fileName){
  int linesRead = 0;
  char buf[1];
  int z;
  int fileDescriptor;
  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in printFromFile");
  
  //read 1 char at a time from the file
  while ((z = read(fileDescriptor, buf, 1)) > 0){
    //compare buff to newline "\n"
    //if newline, increment linesRead
    if (buf[0] == '\n')
      linesRead++;
    if(write(STDOUT_FILENO, buf, z) !=z)
      perror("write error in printFromFile");
    if (z<0)
      perror("read error in printFromFile");
    if(linesRead == n)
      return;
  }

}

/*
 * Main functin -- 
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
	  printFromFile(n,argv[i]);
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
	printFromFile(n,argv[i]);
      }
    }
  }

return 0;
}
