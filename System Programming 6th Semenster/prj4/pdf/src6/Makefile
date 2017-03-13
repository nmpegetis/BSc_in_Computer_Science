#
# Makefile 
#
# Type  make    to compile all the programs
# in the chapter 
#
all: inet_str_server inet_str_client inet_dgr_server inet_dgr_client rls rlsd prs prsref

clean: 
	rm -f inet_str_server \
	inet_str_client int_dgr_server inet_dgr_client rls rlsd prs prsref

inet_dgr_server: inet_dgr_server.c 
	gcc -o inet_dgr_server inet_dgr_server.c

inet_dgr_client: inet_dgr_client.c 
	gcc -o inet_dgr_client inet_dgr_client.c

inet_str_server: inet_str_server.c
	gcc -o inet_str_server inet_str_server.c

inet_str_client: inet_str_client.c
	gcc -o inet_str_client inet_str_client.c

rlsd: rlsd.c 
	gcc -o rlsd rlsd.c

rls: rls.c 
	gcc -o rls rls.c

rlsd: prsref.c 
	gcc -o prsref prsref.c

rlsd: prs.c 
	gcc -o prs prs.c
