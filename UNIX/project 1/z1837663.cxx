/****************************************
NAME:		Ibrahim Khan
Assignment:	7
Due Date:	04/07/2019
z-ID:		z1837663
Class:		csci330
*****************************************
*/
//preprocessor directives
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

//calling standard libraries
using namespace std;

//declaring variables
int fd_File;
int fd;
char* text;
char* File_Name;
char* option;
struct stat buffer;


/*
FUNCTION: main()
ARGUMENTS: argc -> states the number of command line arguments
	   argv -> character array containing the text that goes in the log file
*/
int main(int argc, char * argv[])
{
//O_APPEND flag appends the text to file()
//O_WRONLY flag is used to use write only permissions
int flags = O_APPEND | O_WRONLY;

//if number of command line arguments is less than three then one of
//the required arguments is missing
//display error message and exit.
  if (argc <  3) 

  {

    cerr << "Usage:  seclog [-c] out_file message_string\n"
           "\twhere the message_string is appended to file out_file.\n"
           "\tThe -c option clears the file before the message is appended\n";
    exit(EXIT_FAILURE);

  }

//if "-c" option available then truncate the file
if (!strcmp(argv[1], "-c"))
 {

    flags |= O_TRUNC;
    File_Name = argv[2];
    text = argv[3];

 }

else
 {
    File_Name = argv[1];
    text  = argv[2];
 }
//checking if the log file has any permissions then displaying error message
//and exiting out without recording the text in the file.
  fd = stat(argv[1], &buffer);

  if(fd)
  {

      if (creat(argv[1], 0) < 0)
        cerr<<"Permission Denied..."<<endl;
  }
else
 {
   if(buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO))
   {
      cout << "log is not secure. Ignoring...\n";
      exit(EXIT_FAILURE);
   }
 }

//using chmod() method to change permissions of "File_Name" to give
//write access to user
chmod(File_Name, S_IWUSR);

//opening File_Name using file descriptor open()
fd_File = open(File_Name,  flags);

//writing text to File_name using the assigned buffer to File_Name(fd_File)
write(fd_File, text, strlen(text));
write(fd_File, "\n", 1);

//clearing the permissions 
chmod(File_Name, 00000);

//closing the file.
close(fd_File);
}


