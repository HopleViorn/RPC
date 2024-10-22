rpc:
	rpcgen blackjack.x
servers:
	g++ server.cc blackjack_svc.c blackjack_xdr.c -o server -ltirpc -I/usr/include/tirpc -w
clients:
	g++ client.cc blackjack_clnt.c blackjack_xdr.c -o client -ltirpc -I/usr/include/tirpc -w

all: rpc servers clients
