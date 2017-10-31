#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

/*
This utility prints the final line of a text file.
*/

//parse file and get number of newline chars
//@param fileName the file to be scanned
//@return the numbe of newline chars in the file
int countLines(char * fileName){
  
  int numLines = 0;
  char buf[1];
  int fileDescriptor;

  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in countLines");

  int z;
  //read 1 char at a time from the file
  while ((z = read(fileDescriptor, buf, 1)) > 0){
    //compare buff to newline "\n"
    //if newline, increment numLines
    if(buf[0] == '\n')
      numLines++;

    if (z<0)
      perror("read error in countLines)");
  }

  return numLines;
}

//generalized function that, given a number of lines
//from the end of a file, prints the rest of the file
//@param n the number of lines in the file
//@param q the number of lines to read from the end
//@param fileName the name of the file to print from
void printLines(int n, int q, char* fileName){

  char buf[1];
  int z;
  int fileDescriptor;
  int linesRead = 0;

  if((fileDescriptor = open(fileName, O_RDONLY)) < 2)
    perror("open error in printLines");

  //read 1 char at a time from the file
  while ((z = read(fileDescriptor,buf,1)) > 0){

    if(linesRead > (n-q)){
      if(write(STDOUT_FILENO,buf,z) != z)
	perror("write error in printLines");
    }

    //compare buff to newlne "\n"
    //if newline, increment linesRead
    if(buf[0] == '\n')
      linesRead++;
    if (z<0)
      perror("read error in printLines");
    
 }

}

int main(int argc, char* argv[]){

  int numLines = countLines(argv[1]);
  printLines(numLines,1,argv[1]);

  return 0;
}
