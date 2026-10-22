#include <stdio.h>

int mod26(int x) {
    x %= 26;
    return x < 0 ? x + 26 : x;
}

int main(void) {
    int K[2][2] = {{3, 3}, {2, 5}};
    char plain[] = "HIBY";
    int i, x, y;

    printf("Known plaintext: %s\n", plain);
    printf("Corresponding ciphertext: ");

    for (i = 0; i < 4; i += 2) {
        x = plain[i] - 'A';
        y = plain[i+1] - 'A';

        putchar('A' + mod26(K[0][0]*x + K[0][1]*y));
        putchar('A' + mod26(K[1][0]*x + K[1][1]*y));
    }

    printf("\nDemonstration key matrix:\n");
    printf("%d %d\n", K[0][0], K[0][1]);
    printf("%d %d\n", K[1][0], K[1][1]);

    printf("The key can be recovered from suitable known pairs.\n");
    return 0;
}
Known plaintext: HIBY
Corresponding ciphertext: TCXS
Demonstration key matrix:
3 3
2 5
The key can be recovered from suitable known pairs.
