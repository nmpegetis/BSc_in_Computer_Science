#
# Makefile 
#
# Type  make    to compile all the programs
# in the chapter 
#
all: connect connectTest connector int_str_server \
	int_str_client int_dgr_server int_dgr_client whotofile \
	rls rlsd

clean:
	rm -f connect connectTest connector int_str_server \
	int_str_client int_dgr_server int_dgr_client whotofile rls rlsd

connectTest: connectTest.c 
	gcc -o connectTest connectTest.c

connect: connect.c 
	gcc -o connect connect.c

connector: connector.c 
	gcc -o connector connector.c

int_dgr_server: int_dgr_server.c 
	gcc -o int_dgr_server int_dgr_server.c

int_dgr_client: int_dgr_client.c 
	gcc -o int_dgr_client int_dgr_client.c

int_str_server: int_str_server.c 
	gcc -o int_str_server int_str_server.c

int_str_client: int_str_client.c 
	gcc -o int_str_client int_str_client.c

rlsd: rlsd.c 
	gcc -o rlsd rlsd.c

rls: rls.c 
	gcc -o rls rls.c

whotofile: whotofile.c 
	gcc -o whotofile whotofile.c

