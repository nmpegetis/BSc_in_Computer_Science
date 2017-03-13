/* File: int_dgr_server.c */
#include <sys/types.h>                                   /* For sockets */
#include <sys/socket.h>                                  /* For sockets */
#include <netinet/in.h>                         /* For Internet sockets */
#include <netdb.h>                                 /* For gethostbyaddr */
#include <stdio.h>                                           /* For I/O */
#include <stdlib.h>                                         /* For exit */
#include <string.h>                                        /* For bzero */
main(int argc, char *argv[])   /* Server with Internet datagram sockets */
{  int n, port, sock; char buf[256]; unsigned int serverlen, clientlen;
   struct sockaddr_in server, client;
   struct sockaddr *serverptr, *clientptr; struct hostent *rem;
   if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {  /* Create socket */
      perror("socket"); exit(1); }
   server.sin_family = PF_INET;                      /* Internet domain */
   server.sin_addr.s_addr = htonl(INADDR_ANY);   /* My Internet address */
   server.sin_port = htons(0);                       /* Select any port */
   serverptr = (struct sockaddr *) &server;
   serverlen = sizeof server;
   if (bind(sock, serverptr, serverlen) < 0) {/* Bind socket to address */
      perror("bind"); exit(1); }
   if (getsockname(sock, serverptr, &serverlen) < 0) { /* Selected port */
      perror("getsockname"); exit(1); }
   printf("Socket port: %d\n", ntohs(server.sin_port));
   clientptr = (struct sockaddr *) &client;
   clientlen = sizeof client;
   while(1) {
      bzero(buf, sizeof buf);                      /* Initialize buffer */
      if ((n = recvfrom(sock, buf, sizeof buf, 0, clientptr,
                        &clientlen)) < 0) {
         perror("recvfrom"); exit(1); }              /* Receive message */
      if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr,
            sizeof client.sin_addr.s_addr, client.sin_family)) == NULL) {
         perror("gethostbyaddr"); exit(1); }   /* Find client's address */
      printf("Received from %s: %s\n", rem -> h_name, buf);
      if (sendto(sock, buf, n, 0, clientptr, clientlen) < 0) {
         perror("sendto"); exit(1); } } }               /* Send message */
