#include <cstdlib>
#include <iostream>

using namespace std;

/*
This utility prints all of the currently set environmental
variables
*/

int main(int argc, char * argv[], char * envp[]){

  //for loop that enumerates and prints out each
  //environmental variable
  for(int i = 0; envp[i] != 0; i++){
    cout << envp[i] << endl;
  }

  return 0;
}
