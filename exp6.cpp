#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[1000];
    int i;

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    /* Assumption: B represents E and U represents T.
       This gives C = (3P + 1) mod 26.
       Inverse of 3 modulo 26 is 9. */
    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i]))
            text[i] = (9 * (text[i] - 'A' - 1 + 26)) % 26 + 'A';
        else if (islower((unsigned char)text[i]))
            text[i] = (9 * (text[i] - 'a' - 1 + 26)) % 26 + 'a';
    }

    printf("Possible plaintext: %s", text);
    return 0;
}
Enter ciphertext: B
Possible plaintext: E
