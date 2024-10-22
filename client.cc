/* add_client.cpp */
#include "blackjack.h"
#include <iostream>

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    intpair args;
    int *result;

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <host> <num1> <num2>" << std::endl;
        exit(1);
    }

    args.a = std::atoi(argv[2]);
    args.b = std::atoi(argv[3]);

    clnt = clnt_create(argv[1], ADD_PROG, ADD_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    result = add_1(args, clnt);
    if (result == NULL) {
        clnt_perror(clnt, "call failed");
    } else {
        std::cout << "Result of addition: " << *result << std::endl;
    }

    clnt_destroy(clnt);
    return 0;
}
