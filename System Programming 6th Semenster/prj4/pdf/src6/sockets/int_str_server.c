/* File: int_str_server.c */
#include <sys/types.h>                                   /* For sockets */
#include <sys/socket.h>                                  /* For sockets */
#include <netinet/in.h>                         /* For Internet sockets */
#include <netdb.h>                                 /* For gethostbyaddr */
#include <stdio.h>                                           /* For I/O */
#include <stdlib.h>                                         /* For exit */
#include <string.h>                                /* For strlen, bzero */

void reverse(char *);

main(int argc, char *argv[])     /* Server with Internet stream sockets */
{  int port, sock, newsock; char buf[256];
   unsigned int serverlen, clientlen;
   struct sockaddr_in server, client;
   struct sockaddr *serverptr, *clientptr;
   struct hostent *rem;
   if (argc < 2) {            /* Check if server's port number is given */
      printf("Please give the port number\n");
      exit(1); }
   if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { /* Create socket */
      perror("socket"); exit(1); }
   port = atoi(argv[1]);              /* Convert port number to integer */
   server.sin_family = PF_INET;                      /* Internet domain */
   server.sin_addr.s_addr = htonl(INADDR_ANY);   /* My Internet address */
   server.sin_port = htons(port);                     /* The given port */
   serverptr = (struct sockaddr *) &server;
   serverlen = sizeof server;
   if (bind(sock, serverptr, serverlen) < 0) {/* Bind socket to address */
      perror("bind"); exit(1); }
   if (listen(sock, 5) < 0) {                 /* Listen for connections */
      perror("listen"); exit(1); }
   printf("Listening for connections to port %d\n", port);
   while(1) {
      clientptr = (struct sockaddr *) &client;
      clientlen = sizeof client;
      if ((newsock = accept(sock, clientptr, &clientlen)) < 0) {
         perror("accept"); exit(1); }              /* Accept connection */
      if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,
            sizeof client.sin_addr.s_addr,     /* Find client's address */
            client.sin_family)) == NULL) {
         perror("gethostbyaddr"); exit(1); }
      printf("Accepted connection from %s\n", rem -> h_name);
      switch (fork()) {          /* Create child for serving the client */
         case -1:
            perror("fork"); exit(1);
         case 0:                                       /* Child process */
            do {
               bzero(buf, sizeof buf);             /* Initialize buffer */
               if (read(newsock, buf, sizeof buf) < 0) { /* Get message */
                  perror("read"); exit(1); }
               printf("Read string: %s\n", buf);
               reverse(buf);                         /* Reverse message */
               if (write(newsock, buf, sizeof buf) < 0){/* Send message */
                  perror("write"); exit(1); }
            } while (strcmp(buf, "dne") != 0);       /* Finish on "end" */
            close(newsock);                             /* Close socket */
            exit(0); } } }

void reverse(char *s)                /* Function for reversing a string */
{  int c, i, j;
   for (i = 0, j = strlen(s) - 1 ; i < j ; i++, j--) {
      c = s[i];
      s[i] = s[j];
      s[j] = c; } }
