#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>		/* For bcopy */ 
#include <unistd.h>
#include <sys/wait.h>		/* For wait */
#include <sys/types.h>		/* For sockets */
#include <sys/socket.h>		/* For sockets */
#include <netinet/in.h>		/* For Internet sockets */
#include <netdb.h>		/* For gethostbyname */

int read_data (int fd, char *buffer);
int write_data (int fd, char* message);

int main (int argc, char *argv[])
{
	int i, port, sock, option;
	char opt[3], buf[60], *message[] = { "PAPER", "ROCK", "SCISSORS" };
	unsigned int serverlen;
	struct sockaddr_in server;
	struct sockaddr *serverptr;
	struct hostent *rem;
	if (argc < 3){	/* At least 2 arguments */
		fprintf(stderr, "usage: %s <domain> <port>\n", argv[0]);
		exit(-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(-1);
	}
	if ((rem = gethostbyname(argv[1])) == NULL){	/* Find server address */
		perror("gethostbyname");
		exit(-1);
	}
	port = atoi(argv[2]);
	server.sin_family = AF_INET;
	bcopy((char *) rem -> h_addr, (char *) &server.sin_addr, rem -> h_length);
	server.sin_port = htons(port);
	serverptr = (struct sockaddr *) &server;
	serverlen = sizeof server;
	if (connect(sock, serverptr, serverlen) < 0){
		perror("connect");exit(-1);
	}

	read_data (sock, buf); /* Read player's ID (1 or 2) */
	printf("I am player %d with PID %d\n", buf[0]-'0', (int) getpid());
	for ( i = 1; ; i++ ){/* While read "READY" */
		read_data (sock, buf);	/* Read "READY" or "STOP" */
		if ( strcmp("STOP", buf) ){ /* If != "STOP" */
			printf("Give round %d play: ", i);
			scanf("%s", opt);
			switch (*opt){	/* First letter of opt */
			/* Note: The other 2 are \n and \0 */
				case 'p':option = 0; break;
				case 'r':option = 1; break;
				case 's':option = 2; break;
				default: fprintf(stderr, "Wrong option %c\n", *opt);
					option = ((int)*opt)%3; break;
			}
			write_data (sock, message[option]);
			read_data (sock, buf);
			printf ("%s", buf);
		}else break;
	}
	read_data (sock, buf);	/* Read final score */
	printf("%s", buf);
	close(sock);
	return 0;
}

int read_data (int fd, char *buffer){/* Read formated data */
	char temp; int i = 0, length = 0;
	if ( read ( fd, &temp, 1 ) < 0 )/* Get length of string */
		exit (-3);
	length = temp;
	while ( i < length )	/* Read $length chars */
		if ( i < ( i+= read (fd, &buffer[i], length - i) ) )
			exit (-3);
	return i;	/* Return size of string */
}
int write_data ( int fd, char* message ){/* Write formated data */
	char temp; int length = 0;
	length = strlen(message) + 1;	/* Find length of string */
	temp = length;
	if ( write (fd, &temp, 1) < 0 )	/* Send length first */
		exit (-2);
	if ( write (fd, message, length) < 0 )	/* Send string */
		exit (-2);
	return length;				/* Return size of string */
}
