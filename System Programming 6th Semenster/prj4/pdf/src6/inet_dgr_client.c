/* inet_dgr_client.c: Internet datagram sockets client    */
#include <sys/types.h>                         /* sockets */
#include <sys/socket.h>                        /* sockets */
#include <netinet/in.h>               /* Internet sockets */
#include <netdb.h>                       /* gethostbyname */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   int sock; char buf[256]; struct hostent *rem;
   struct sockaddr_in server, client;
   unsigned int serverlen = sizeof(server);
   struct sockaddr *serverptr = (struct sockaddr *) &server;
   struct sockaddr *clientptr = (struct sockaddr *) &client;
   if (argc < 3) {
      printf("Please give host name and port\n"); exit(1);}
   /* Create socket */
   if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("socket"); exit(1); }
   /* Find server's IP address */
   if ((rem = gethostbyname(argv[1])) == NULL) {
      herror("gethostbyname"); exit(1); }
   /* Setup server's IP address and port */
   server.sin_family = AF_INET;        /* Internet domain */
   memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
   server.sin_port = htons(atoi(argv[2]));
   /* Setup my address */
   client.sin_family = AF_INET;        /* Internet domain */
   client.sin_addr.s_addr=htonl(INADDR_ANY); /*Any address*/
   client.sin_port = htons(0);         /* Autoselect port */
   /* Bind my socket to my address*/
   if (bind(sock, clientptr, sizeof(client)) < 0) {
      perror("bind"); exit(1); }
   /* Read continuously messages from stdin */
   while (fgets(buf, sizeof buf, stdin)) { 
      buf[strlen(buf)-1] = '\0';           /* Remove '\n' */
      if (sendto(sock, buf, strlen(buf)+1, 0, serverptr, serverlen) < 0) {
         perror("sendto"); exit(1); }     /* Send message */
      bzero(buf, sizeof buf);             /* Erase buffer */
      if (recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL) < 0) {
         perror("recvfrom"); exit(1); }/* Receive message */
      printf("%s\n", buf);
   }
   return(0);
}
