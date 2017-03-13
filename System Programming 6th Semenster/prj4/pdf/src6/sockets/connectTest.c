/* File: connectTest.c */
#include <stdio.h> /* For printf */
#include <stdlib.h> /* For exit */
#include <unistd.h> /* For execlp */
#include <sys/stat.h> /* for open */
#include <fcntl.h> /* for open */
#define READ 0 /* Read end of pipe */
#define WRITE 1 /* Write end of pipe */
main(int argc, char *argv[]) { 
  int fd[2], pid, fd2[2], filefd;
  if ((filefd = 
        open("testFile", O_WRONLY | O_CREAT, 0666)) == -1) {
    perror("file"); exit(1); }
  if (pipe(fd) == -1) { /* Create a pipe */
    perror("pipe"); exit(1); }
  if (pipe(fd2) == -1) { /* Create a second pipe */
    perror("pipe2"); exit(1); }
  if ((pid = fork()) == -1) { /* Fork a child */
    perror("fork"); exit(1); }
  if (pid != 0) { /* Parent, writer */
    close(filefd); close(fd[READ]); close(fd[WRITE]);
    close(fd2[READ]); close(fd2[WRITE]);
    if (wait(NULL) != pid) {
	perror("Waiting for child completion:"); exit(-1); } }
  else { /* Child, reader */
    printf("Filefd = %d, fd[WRITE] = %d, fd2[WRITE] = %d\n", 
		filefd, fd[WRITE], fd2[WRITE]);
    dup2(fd2[WRITE], 11); /* Duplicate write end to stdout */
    execlp(argv[1], argv[1], "11", NULL); /* Execute argv[1] */
    perror("execlp"); } }
