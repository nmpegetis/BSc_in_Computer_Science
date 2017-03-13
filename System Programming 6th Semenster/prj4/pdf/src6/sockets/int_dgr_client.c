/* File: int_dgr_client.c */
#include <sys/types.h>                                   /* For sockets */
#include <sys/socket.h>                                  /* For sockets */
#include <netinet/in.h>                         /* For Internet sockets */
#include <netdb.h>                                 /* For gethostbyname */
#include <stdio.h>                                           /* For I/O */
#include <stdlib.h>                                         /* For exit */
#include <string.h>                         /* For strlen, bzero, bcopy */
main(int argc, char *argv[])   /* Client with Internet datagram sockets */
{  int port, sock; char buf[256];
   unsigned int serverlen, clientlen;
   struct sockaddr_in server, client;
   struct sockaddr *serverptr, *clientptr; struct hostent *rem;
   if (argc < 3) {     /* Are server's host name and port number given? */
      printf("Please give host name and port number\n"); exit(1); }
   if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {  /* Create socket */
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
   client.sin_family = PF_INET;                      /* Internet domain */
   client.sin_addr.s_addr = htonl(INADDR_ANY);   /* My Internet address */
   client.sin_port = htons(0);                       /* Select any port */
   clientptr = (struct sockaddr *) &client;
   clientlen = sizeof client;
   if (bind(sock, clientptr, clientlen) < 0) {/* Bind socket to address */
      perror("bind"); exit(1); }
   while (fgets(buf, sizeof buf, stdin) != NULL) { /* Read continuously
                                                    messages from stdin */
      buf[strlen(buf)-1] = '\0';            /* Remove newline character */
      if (sendto(sock, buf, strlen(buf)+1, 0, serverptr, serverlen) < 0) {
         perror("sendto"); exit(1); }                   /* Send message */
      bzero(buf, sizeof buf);                      /* Initialize buffer */
      if (recvfrom(sock, buf, sizeof buf, 0, serverptr, &serverlen) < 0) {
         perror("recvfrom"); exit(1); }              /* Receive message */
      printf("%s\n", buf); } }
