#include <stdio.h>
#include <string.h>

int main(void) {
    const char *plain = "HELLO";
    const int key[] = {3, 19, 5, 12, 7}; /* demo only */
    char cipher[sizeof("HELLO")];

    for (size_t i = 0; i < strlen(plain); ++i) {
        int p = plain[i] - 'A';
        cipher[i] = (char)('A' + (p + key[i]) % 26);
    }
    cipher[strlen(plain)] = '\0';

    printf("Ciphertext: %s\n", cipher);
    return 0;
}
