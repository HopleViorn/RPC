
servers:
	g++ blackjack_server.c blackjack_svc.c blackjack_xdr.c -o server -ltirpc -I/usr/include/tirpc
clients:
	g++ blackjack_client.c blackjack_clnt.c blackjack_xdr.c -o client -ltirpc -I/usr/include/tirpc

all: servers clients
