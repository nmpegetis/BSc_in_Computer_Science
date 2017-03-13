/* File: connect.c */
#include <stdio.h> /* For printf */
#include <stdlib.h> /* For exit */
#include <unistd.h> /* For execlp */
#define READ 0 /* Read end of pipe */
#define WRITE 1 /* Write end of pipe */
main(int argc, char *argv[])
{ 
  int fd[2], pid;
  if (pipe(fd) == -1) { /* Create a pipe */
    perror("pipe");
    exit(1); 
  }

  if ((pid = fork()) == -1) { /* Fork a child */
    perror("fork");
    exit(1); 
  }

  if (pid != 0) { /* Parent, writer */
    close(fd[READ]); /* Close unused end */
    dup2(fd[WRITE], 1); /* Duplicate write end to stdout */
    close(fd[WRITE]); /* Close write end */
    execlp(argv[1], argv[1], NULL); /* Execute argv[1] */
    perror("execlp"); 
  }
  else { /* Child, reader */
    close(fd[WRITE]); /* Close unused end */
    dup2(fd[READ], 0); /* Duplicate read end to stdin */
    close(fd[READ]); /* Close read end */
    execlp(argv[2], argv[2], NULL); /* Execute argv[2] */
    perror("execlp"); 
  } 
}
