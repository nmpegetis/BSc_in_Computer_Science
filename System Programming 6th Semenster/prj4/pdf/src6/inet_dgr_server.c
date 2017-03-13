/* inet_dgr_server.c: Internet datagram sockets server */
#include <sys/types.h>                         /* sockets */
#include <sys/socket.h>                        /* sockets */
#include <netinet/in.h>               /* Internet sockets */
#include <netdb.h>                       /* gethostbyaddr */
#include <arpa/inet.h>                       /* inet_ntoa */
#include <stdio.h>
#include <stdlib.h>

void perror_exit(char *message);

char *name_from_address(struct in_addr addr) {
    struct hostent *rem; int asize = sizeof(addr.s_addr);
    if((rem = gethostbyaddr(&addr.s_addr, asize, AF_INET)))
        return rem->h_name;  /* reverse lookup success */
    return inet_ntoa(addr); /* fallback to a.b.c.d form */
}

int main() {
    int n, sock; unsigned int serverlen, clientlen;
    char buf[256], *clientname;
    struct sockaddr_in server, client;
    struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct sockaddr *clientptr = (struct sockaddr*)&client;
    /* Create datagram socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        perror_exit("socket");
    /* Bind socket to address */
    server.sin_family = AF_INET;       /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(0);      /* Autoselect a port */
    serverlen = sizeof(server);
    if (bind(sock, serverptr, serverlen) < 0)
        perror_exit("bind");
    /* Discover selected port */
    if (getsockname(sock, serverptr, &serverlen) < 0)
        perror_exit("getsockname");
    printf("Socket port: %d\n", ntohs(server.sin_port));
    while(1) { clientlen = sizeof(client);
        /* Receive message */
        if ((n = recvfrom(sock, buf, sizeof(buf), 0, clientptr, &clientlen)) < 0)
            perror("recvfrom");
        buf[sizeof(buf)-1]='\0'; /* force str termination */
        /* Try to discover client's name */
	printf("calling 'name_from_address' with arg: %s\n"addr.s_addr);
        clientname = name_from_address(client.sin_addr);
        printf("Received from %s: %s\n", clientname, buf);
        /* Send message */
        if (sendto(sock, buf, n, 0, clientptr, clientlen)<0)
            perror_exit("sendto");
    }
    return(0);
}

void perror_exit(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
