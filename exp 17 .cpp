#include <stdio.h>

/* DES encryption uses K1 to K16.
   DES decryption uses K16 to K1. */

int main(void) {
    int i;
    int key[16] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16
    };

    printf("DES decryption key order:\n");

    for (i = 15; i >= 0; i--)
        printf("K%d ", key[i]);

    printf("\n");
    return 0;
}
DES decryption key order:
K16 K15 K14 K13 K12 K11 K10 K9 K8 K7 K6 K5 K4 K3 K2 K1
