/* add.x: RPC Interface definition */
program ADD_PROG {
    version ADD_VERS {
        int ADD(intpair) = 1;
    } = 1;
} = 0x20000001;

struct intpair {
    int a;
    int b;
};
