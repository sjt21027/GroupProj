/*
 * env.cpp 
 *	
 * The env utility prints all of the currently set
 * environmental variables to standard output.
 * 
 * Owner: Steven Thompson - Gray Dunagan
 * 
 * Version: 11.6.17
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * This utility prints all of the currently set environmental
 * variables
 * Main function---
 *
 * @param argc the amount of arguments
 * @param envp the amount of environment variables
 */
int main(int argc, char * argv[], char * envp[]){

  //for loop that enumerates and prints out each
  //environmental variable
  for(int i = 0; envp[i] != 0; i++){
    cout << envp[i] << endl;
  }

  return 0;
}
