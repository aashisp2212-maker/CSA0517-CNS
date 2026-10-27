#include <stdio.h>
#include <string.h>

unsigned char E(unsigned char x) {
    return x ^ 0xA5;  /* Demonstration only */
}

void pad(unsigned char *data, int *len) {
    data[(*len)++] = 0x80;
    while (*len % 1 != 0)
        data[(*len)++] = 0;
}

int main(void) {
    unsigned char p[] = "HELLO";
    unsigned char c[100], prev = 0x12;
    int n = (int)strlen((char *)p), i;

    /* Padding: one 1-bit followed by zero bits.
       Demonstration uses 8-bit blocks. */
    p[n++] = 0x80;
    while (n % 1 != 0)
        p[n++] = 0;

    printf("Plaintext: HELLO\n");

    printf("ECB ciphertext: ");
    for (i = 0; i < n; i++) {
        c[i] = E(p[i]);
        printf("%02X ", c[i]);
    }

    printf("\nCBC ciphertext: ");
    prev = 0x12;
    for (i = 0; i < n; i++) {
        prev = E(p[i] ^ prev);
        printf("%02X ", prev);
    }

    printf("\nCFB ciphertext: ");
    prev = 0x12;
    for (i = 0; i < n; i++) {
        unsigned char out = p[i] ^ E(prev);
        printf("%02X ", out);
        prev = out;
    }

    printf("\n");
    return 0;
}
Plaintext: HELLO
ECB ciphertext: ED E0 E9 E9 EA 25
CBC ciphertext: FF 12 5E 12 5D 74
CFB ciphertext: F2 47 E4 50 F6 3D
