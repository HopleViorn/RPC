/* add_server.cpp */
#include "blackjack.h"
#include <iostream>

int *add_1_svc(intpair *argp, struct svc_req *rqstp) {
    static int result;
    result = argp->a + argp->b;
    std::cout << "Received request to add " << argp->a << " and " << argp->b << std::endl;
    return &result;
}