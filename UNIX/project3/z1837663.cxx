#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<iomanip>
#include<iostream>
using namespace std;

void error(char *msg)
{
perror(msg);
exit(1);
}

int main(int argc, char *argv[])
{

int sockfd, newsockfd, portno, clilen, n;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
struct sockaddr_in
{
  short   sin_family; /* must be AF_INET */
  u_short sin_port;
  struct  in_addr sin_addr;
  char    sin_zero[8]; /* Not used, must be zero */
};
if (argc < 2)
{
   fprintf(stderr,"ERROR, no port provided");
   exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0);

if (sockfd < 0)
{
  error("ERROR opening socket");
}

bzero((char *) &serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
{
  error("ERROR on binding");
}

listen(sockfd,5);
clilen = sizeof(cli_addr);
while (1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             dostuff(newsockfd);
             exit(0);
         }
         else close(newsockfd);
     } /* end of while */
     close(sockfd);
     return 0; /* we never get here */
}
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if (newsockfd < 0)
{
  error("ERROR on accept");
}
bzero(buffer,256);
n = read(newsockfd,buffer,255);
if (n < 0)
{
 error("ERROR reading from socket");
}
printf("Here is the message: %s",buffer);
n = write(newsockfd,"I got your message",18);
if (n < 0) error("ERROR writing to socket");

return 0;


}