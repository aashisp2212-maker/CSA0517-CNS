#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    int i, j = 0;

    printf("Plaintext: %s\n", text);
    printf("Ciphertext: ");

    for (i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            char c = tolower((unsigned char)text[i]);
            putchar((c - 'a' + key[j]) % 26 + 'A');
            j++;
        } else {
            putchar(text[i]);
        }
    }

    printf("\n");
    return 0;
}
Plaintext: send more money
Ciphertext: BEOK JDMS XZPMH
