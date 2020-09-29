/*
**********************************
NAME:		Ibrahim khan
ZID:		z1837663
ASSIGNMENT:	8
CLASS:		CSCI330
DUE DATE:	04/21/2019
**********************************.
*/


//Preprocessor directives.
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/wait.h>
#include <iostream>
#include <iomanip>

//calling standard library functions
using std::cout;
using std::cin;
using std::cerr;
using std::endl;


int main()
{  //variable declarations
   char arr[80];
   int num;
   int result = 0;
   int verify;

while(true)
{  //prompting for a command
   cout << "Enter a command: ";

   //reading the complete line through getline method
   cin.getline(arr, 80);

   //if command is not exit then continue
   if (!strcmp(arr, "exit"))
   {
      break;
   }

   //using fork for verify
   verify = fork();

   //if fork does not work display this error message
   if (verify == -1)
   {
      cout << "Fork did not work!!";
      exit(-1);
   }

   //check for number of arguments
   if (verify == 0)
   {

      //initializing argv[] array to hold command line arguments
      char *argv[] = {(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(char*)0};


      //storing arguments one by one using a for loop in "arg" variable
      for ( char* arg = strtok( arr, " ");arg; arg = strtok(NULL, " "))
      {

      //arguments are  stored in argv[count] array with every iteration of the loop
      argv[num] = arg;
      num++;

      //limiting arguments to less than 5.
         if(num > 5)
         {
            cout << "Arguments limit exceeded... \n";
            exit(-1);
         }

      }
       result = execvp(argv[0], argv);
       if (result == -1)
       {
           cerr << argv[0] << ": " << "No such file or directory" << endl;
           exit(-1);
       }
   }
       else
       {
       wait(NULL);
       }
   }
}


