#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>			/* For wait */
#include <sys/types.h>			/* For sockets */
#include <sys/socket.h>			/* For sockets */
#include <netinet/in.h>			/* For Internet sockets */
#include <netdb.h>			/* For gethostbyname */

#define READ	0
#define WRITE	1

int read_data (int fd, char *buffer);
int write_data (int fd, char* message);
void prs (int *score1, int *score2, int len1, int len2);

int main(int argc, char *argv[])
{
	int n, port, sock, newsock;
	int i, pid, fd1[2], fd2[2], option, status;
	int  score1=0, score2=0;		/* Score variables */
	char buf[60], buf2[60], buf3[60];	/* Buffers */
	char *message[] = { "ROCK", "PAPER", "SCISSORS" };	/* prs options */

	unsigned int serverlen, clientlen;	/* Server - client variables */
	struct sockaddr_in server, client;
	struct sockaddr *serverptr, *clientptr;
	struct hostent *rem;

	if ( argc < 3 ){			/* At least 2 arguments */
		fprintf(stderr, "usage: %s <n> <port>\n", argv[0]);
		exit(0);
	}

	n = atoi(argv[1]);			/* Number of games */
	port = atoi(argv[2]);			/* Port */

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1){	/* Create socket */
		perror("socket");
		exit(-1);
	}
	server.sin_family = AF_INET;	/* Internet domain */
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(port);	/* The given port */
	serverptr = (struct sockaddr *) &server;
	serverlen = sizeof server;
	if (bind(sock, serverptr, serverlen) < 0){
		perror("bind");	exit(-1);
	}
	if (listen(sock, 5) < 0){
		perror("listen");exit(-1);
	}

	printf("I am the referee with PID %d waiting for game request at port %d\n", (int) getpid(), port);

	if (pipe (fd1) == -1){	/* First pipe: parent -> child */
		perror("pipe");exit(-1);
	}
	if (pipe (fd2) == -1){	/* Second pipe: child -> parent */
		perror("pipe");exit(-1);
	}

	if ((pid = fork()) == -1)	 /* Create child for player 1 */
	{
		perror("fork");exit(-1);
	}

	if ( !pid ){		/* Child process */
		close(fd1[WRITE]);close(fd2[READ]);	/* Close unused*/
		srand (getppid());
		printf("I am player 1 with PID %d\n", (int) getpid());
		for(;;)			/* While read "READY" */
		{
			read_data (fd1[READ], buf);	/* Read "READY" or "STOP" */
			option = rand()%3;
			if ( strcmp("STOP", buf)){	/* If != "STOP" */
				write_data (fd2[WRITE], message[option]);	/* Send random option */
				read_data (fd1[READ], buf);	/* Read result of this game */
				printf ("%s", buf);		/* Print result */
			}else
				break;
		}
		read_data (fd1[READ], buf);	/* Read final result */
		printf("%s", buf);	/* Print final result */
		close(fd1[READ]); close(fd2[WRITE]);
	}
	else{		/* Parent process */
		clientptr = (struct sockaddr *) &client;
		clientlen = sizeof client;
		close(fd1[READ]); close(fd2[WRITE]);
		printf("Player 1 is child of the referee\n");
		if ((newsock = accept(sock, clientptr, &clientlen)) < 0){
			perror("accept"); exit(-1);
		}
		if ((rem = gethostbyaddr((char *) &client.sin_addr.s_addr, sizeof client.sin_addr.s_addr, client.sin_family)) == NULL) {
			perror("gethostbyaddr");exit(-1);
		}

		printf("Player 2 connected %s\n",rem->h_name);
		write_data (newsock, "2"); /* Send player's ID (2) */
		for(i = 1; i <= n; i++){
			write_data (fd1[WRITE], "READY");
			write_data (newsock, "READY");
			read_data (fd2[READ], buf);
			read_data (newsock, buf2);
			/* Create result string */
			sprintf (buf3, "Player 1:%10s\tPlayer 2:%10s\n", buf, buf2);
			write_data (fd1[WRITE], buf3);
			write_data (newsock, buf3);
			prs(&score1,&score2,strlen(buf),strlen(buf2));
		}

		/* Calculate final results for each player */
		if ( score1 == score2 ){
			sprintf(buf, "Score = %d - %d (draw)\n", score1, score2);
			sprintf(buf2, "Score = %d - %d (draw)\n", score1, score2);
		}else if (score1 > score2 ){
			sprintf(buf, "Score = %d - %d (you won)\n", score1, score2);
			sprintf(buf2, "Score = %d - %d (player 1 won)\n", score1, score2);
		}else{
			sprintf(buf, "Score = %d - %d (player 2 won)\n", score1, score2);
			sprintf(buf2, "Score = %d - %d (you won)\n", score1, score2);
		}
		write_data (fd1[WRITE], "STOP");
		write_data (fd1[WRITE], buf);
		close(fd1[WRITE]); close(fd2[READ]);
		wait(&status);	/* Wait child */
		write_data (newsock, "STOP");
		write_data (newsock, buf2);
		close(newsock);	/* Close socket */
	}
	return 0;
}

int read_data (int fd, char *buffer){/* Read formated data */
	char temp;int i = 0, length = 0;
	if ( read ( fd, &temp, 1 ) < 0 )	/* Get length of string */
		exit (-3);
	length = temp;
	while ( i < length )	/* Read $length chars */
		if ( i < ( i+= read (fd, &buffer[i], length - i)))
			exit (-3);
	return i;	/* Return size of string */
}
int write_data ( int fd, char* message ){/* Write formated data */
	char temp; int length = 0;
	length = strlen(message) + 1;	/* Find length of string */
	temp = length;
	if( write (fd, &temp, 1) < 0 )	/* Send length first */
		exit (-2);
	if( write (fd, message, length) < 0 )	/* Send string */
		exit (-2);
	return length;		/* Return size of string */
}

/* void prs(int *score1, int *score2, int len1, int len2):
*	Each option (PAPER, ROCK, SCISSORS) has a number of letters (5, 4, 8).
*	PAPER wins ROCK, ROCK wins SCISSORS and SCISSORS win PAPER.
*	This means, for the 1st player to be the winner the difference in the
*	number of letters must be equal to 3 (SCISSORS-PAPER) or 1 (PAPER-ROCK)
*	or -4 (ROCK-SCISSORS). If not, then the 2nd player wins!
*	(If we have a zero, then we call it a draw and nobody get points)
*/
void prs(int *score1, int *score2, int len1, int len2)	/* Calculate score */
{
	int result = len1 - len2; /* len1 = buf1 length, len2 = buf2 length */
	if (result == 3 || result == 1 || result == -4)	/* 1st player wins */
		(*score1)++;
	else if (result)	/* 2nd player wins */
		(*score2)++;
	return;
}
