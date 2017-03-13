/* File: int_str_client.c */
#include <sys/types.h>                                   /* For sockets */
#include <sys/socket.h>                                  /* For sockets */
#include <netinet/in.h>                         /* For Internet sockets */
#include <netdb.h>                                 /* For gethostbyname */
#include <stdio.h>                                           /* For I/O */
#include <stdlib.h>                                         /* For exit */
#include <string.h>                         /* For strlen, bzero, bcopy */
main(int argc, char *argv[])     /* Client with Internet stream sockets */
{  int port, sock; char buf[256]; unsigned int serverlen;
   struct sockaddr_in server;
   struct sockaddr *serverptr;
   struct hostent *rem;
   if (argc < 3) {     /* Are server's host name and port number given? */
      printf("Please give host name and port number\n"); exit(1); }
   if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { /* Create socket */
      perror("socket"); exit(1); }
   if ((rem = gethostbyname(argv[1])) == NULL) { /* Find server address */
      perror("gethostbyname"); exit(1); }
   port = atoi(argv[2]);              /* Convert port number to integer */
   server.sin_family = PF_INET;                      /* Internet domain */
   bcopy((char *) rem -> h_addr, (char *) &server.sin_addr,
         rem -> h_length);
   server.sin_port = htons(port); /* Server's Internet address and port */
   serverptr = (struct sockaddr *) &server;
   serverlen = sizeof server;
   if (connect(sock, serverptr, serverlen) < 0) { /* Request connection */
      perror("connect"); exit(1); }
   printf("Requested connection to host %s port %d\n", argv[1], port);
   do {
      bzero(buf, sizeof buf);                      /* Initialize buffer */
      printf("Give input string: ");
      fgets(buf, sizeof buf, stdin);         /* Read message from stdin */
      buf[strlen(buf)-1] = '\0';            /* Remove newline character */
      if (write(sock, buf, sizeof buf) < 0) {           /* Send message */
         perror("write"); exit(1); }
      bzero(buf, sizeof buf);                      /* Initialize buffer */
      if (read(sock, buf, sizeof buf) < 0) {         /* Receive message */
         perror("read"); exit(1); }
      printf("Read string:       %s\n", buf);
   } while (strcmp(buf, "dne") != 0);                /* Finish on "end" */
   close(sock); exit(0); }                     /* Close socket and exit */
