//***********************************************************************
// AUTHOR: 	IBRAHIM KHAN                                            *
// INSTRUCTOR: 	PROFESSOR ZHOU                                          *
// ASSIGNMENT:	2                                                       *
// DUE DATE:	09-26-20
// COURSE:	CSCI 480                                                *
// PURPOSE: 	THE PURPOSE OF THIS ASSIGNMENT IS TO GET FAMILIARIZED   *
//	    	WITH FORK() PROCESSES AND PIPE().                       *
//                                                                      *
// FUNCTIONALITY: THIS PROGRAM WILL CALL FORK() TWICE TO CREATE         *
//                THE FOLLOWING:                                        *
//             => AN INITIAL PARENT PROCESS                             *
//             => AN INTERMEDIATE PARENT WHICH IS PARENT TO THE         *
//                GRAND CHILD                                           *
//             => AND ANOTHER CHILD FROM INITIAL PARENT                 *
// COMMUNICATION BETWEEN THE PROCESSES IS DONE BY USING PIPE().         *
//***********************************************************************

//PREPROCESSOR DIRECTIVES
#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>

//DEFINCE CONSTANT VALUES
#define BUFFER_SIZE 25		//BUFFER SIZE FOR MESSAGE WHICH WILL BE USED IN PIPE()
#define READ_END 0		//TO READ INTO PIPE()
#define WRITE_END 1		//WRITE END OF THE PIPE()

//USING STANDARD LIBRARY FUNCTIONS
using namespace std;

int main()
{
   int pipe_a[2];		//first pipe()
   int pipe_b[2];		//second pipe()
   if(pipe(pipe_a) == -1)	//if pipe() gets error code -1 pipe failed.
   {
      cout << "pipe A failed!" << endl;
      exit(-1);
   }
   if(pipe(pipe_b) == -1)
   {
      cout << "pipe B failed" << endl;
      exit(-1);
   }
      char write_msg[BUFFER_SIZE] = "Go do some chores"; //defining the write_msg to send through pipe()
      char read_msg[BUFFER_SIZE];			 //defining the read_msg to read from pipe()
      pid_t fork1 = fork();				 //first fork() call
      pid_t fork2 = fork();				 //seconds fork() call

//AFTER THE FORK SYSTEM CALLS WE NOW HAVE 4 PROCESSES RUNNING
//INTIAL PARENT,INTERMEDIATE PARENT, GRAND CHILD FROM INTERMEDIATE PARENT
//AND CHILD FROM INITIAL PARENT.

   if(fork1 < 0 || fork2 < 0)		//IF ANY OF THE FORK FAILS EXIT THE PROGRAM
   {
      cout << "FORK_FAILURE!!" << endl;
      exit(-1);
   }
   if(fork1 > 0 && fork2 > 0)						//GETTING THE PARENT PROCESS AND WRITING THE MESSAGE TO ITS LONE CHILD THROUGH PIPE_A()
   {
      close(pipe_a[READ_END]);						//THIS IS TO MAKE SURE THAT THE END OF THE PIPE IS CLOSED WHICH WE DO NOT NEED.
      write(pipe_a[WRITE_END], write_msg, strlen(write_msg)+1);		//WRITING MESSAGE 
      close(pipe_a[WRITE_END]);						//CLOSING PIPE AFTER WRITING
      cout << "\nPARENT: My Pid is: " << getpid() << ", My parent Pid is: " << getppid() << ", my children are: " << fork1 << ", " << fork2 << " I WRITE TO PIPE A: " << write_msg << "\n";
      string str = "/bin/ps -f --ppid " + to_string(getpid())  + "," + to_string(getppid()) + "," + to_string(fork1) + "," + to_string(fork2);
      cout << "\nPARENT: issuing command: " << str << "\n";
      int n = str.length();						//GETTING THE LENGTH OF THE MESSAGE
      char str_arr[n+1];
      strcpy(str_arr, str.c_str());					//CONVERTING STRING TO AN ARRAY OF CHARACTERS
      int return_code = system(str_arr);
      if(return_code == -1)
      {
      cout << "THE SYSTEM CALL FAILED!!" << endl;
      exit(-1);
      }							//CALLING SYSTEM() CALL TO LIST PROCESSES
      cout << endl;
      int status;
      if(waitpid(fork1,&status,0) != -1)				//WAITING TILL ALL THE CHILD PROCESSES HAVE FINISHED
      {
      if(WIFEXITED(status))						// 'WIFEXITED' ENSURES ALL CHILD PROCESSES HAVE FINISHED
      {
      cout << "Parent: Child process have finished." << endl;
      exit(-1);
      }
      }
   }
   else if(fork1 == 0 && fork2 > 0)					//GETTING THE INTERMEDIATE PARENT AND THE CHILD OF THE INITIAL PARENT
   {
      close(pipe_b[READ_END]);						//INTERMEDIATE PARENT WRITES TO THE GRAND CHILD THROUGH PIPE_B.
      write(pipe_b[WRITE_END], write_msg, strlen(write_msg)+1);         //WRITTING THE MESSAGE.
      close(pipe_b[WRITE_END]);						//CLOSE WRITING END OF THE PIPE
      cout << "INTERMEDIATE: My Pid is: " << getpid() << ", My parent Pid is: " << getppid() << ", my children are: " << fork2 << " I WRITE TO PIPE B: " << write_msg << "\n" << endl;
      sleep(1);								//MAKING THE INTERMEDIATE PARENT PROCESS SLEEP FOR ONE SECOND TO MAKE SURE SYSTEM() CALL FINISHES FIRST
      cout << "Intermediate parent: " << getpid() << ", is awake." << endl;

   }
   else if(fork1 > 0 && fork2 == 0)					//GETTING THE LONE CHILD OF THE PARENT PROCESS
   {
      close(pipe_a[WRITE_END]);						//CLOSING THE WRITE END OF THE PIPE
      read(pipe_a[READ_END], read_msg, BUFFER_SIZE);			//READING THE MESSAGE FROM THE PIPE_A
      close(pipe_a[READ_END]);						//CLOSING THE READING END OF THE PIPE_A
      cout << endl << "CHILD: My Pid is: " << getpid() << ", My parent Pid is: " << getppid() << " I READ FROM PIPE A: " << read_msg << "\n" << endl;
      sleep(1);								//PUTTING THIS CHILD PROCESS TO SLEEP FOR ONE SECOND TO MAKE SURE SYSTEM() CALL FINISHES FIRST
      cout << "Child: " << getpid() << ", is awake." << endl;
   }
   else									//IF BOTH FORK1 AND FORK2 ARE == 0 THEN ITS THE GRAND CHILD OF THE PARENT 
   {
      close(pipe_b[WRITE_END]);	
      read(pipe_b[READ_END], read_msg, BUFFER_SIZE);			//GRAND CHILD USES PIPE_B TO READ FROM THE INTERMEDIATE PARENT
      close(pipe_b[READ_END]);
      cout << "\nCHILD: My Pid is: " << getpid() << ", My parent Pid is: " << getppid() << " I READ FROM PIPE B: " << read_msg << "\n"  << endl;
      sleep(1);								//SLEEP FOR ONE SECOND TO ENSURE SYSTEM() CALL PROCESS FINISHES FIRST.
      cout << "Child: " << getpid() << ", is awake." << endl;
   }
   return 0;  								//RETURN 0 AFTER SUCCESSFUL COMPLETION OF THE MAIN()
}
