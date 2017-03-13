/* File: connector.c */
#include <stdio.h> /* For printf */
#include <stdlib.h> /* For exit */
#include <unistd.h> /* For execlp */
#include <sys/stat.h> /* for open */
#include <fcntl.h> /* for open */
#include <string.h>
int main(int argc, char *argv[])
{ 
  char message[]="HELLO WORLD";
  if (write(3, message, strlen(message) + 1) == -1) 
	perror("Write to 3-file");
  else printf("Write to file succeeded\n");
  if (write(5, message, strlen(message) + 1) == -1) 
	perror("Write to 5-pipe1");
  else printf("Write to pipe1 succeeded\n");
  if (write(7, message, strlen(message) + 1) == -1) 
	perror("Write to 7-pipe2");
  else printf("Write to pipe2 succeeded\n");
  if (write(11, message, strlen(message) + 1) == -1) 
	perror("Write to 11-dup2");
  else printf("Write to dup2 succeeded\n");
  if (write(13, message, strlen(message) + 1) == -1) 
	perror("Write to 13-Invalid");
  else printf("Write to invalid succeeded\n");
  return 1;
}
