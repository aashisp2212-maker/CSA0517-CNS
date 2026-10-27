#include <stdio.h>

int main() {
    printf("ECB MODE\n");
    printf("--------\n");
    printf("Error in C1 affects P1 only.\n");
    printf("P2, P3 and remaining blocks are unchanged.\n\n");

    printf("CBC MODE\n");
    printf("--------\n");
    printf("Error in transmitted C1 affects P1 and P2.\n");
    printf("P3 and remaining blocks are unchanged.\n\n");

    printf("SOURCE PLAINTEXT ERROR IN CBC\n");
    printf("-----------------------------\n");
    printf("Error in source P1 affects C1 and all");
    printf(" subsequent ciphertext blocks.\n");
    printf("At the receiver, P1 and subsequent");
    printf(" plaintext blocks are generally affected.\n");

    return 0;
}ECB MODE
--------
Error in C1 affects P1 only.
P2, P3 and remaining blocks are unchanged.

CBC MODE
--------
Error in transmitted C1 affects P1 and P2.
P3 and remaining blocks are unchanged.

SOURCE PLAINTEXT ERROR IN CBC
-----------------------------
Error in source P1 affects C1 and all subsequent ciphertext blocks.
At the receiver, P1 and subsequent plaintext blocks are generally affected.
