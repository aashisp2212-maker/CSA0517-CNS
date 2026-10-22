#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char text[200], key[100];
    int i, j = 0, shift;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter key: ");
    scanf("%99s", key);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            shift = toupper((unsigned char)key[j % strlen(key)]) - 'A';

            if (isupper((unsigned char)text[i]))
                text[i] = (text[i] - 'A' + shift) % 26 + 'A';
            else
                text[i] = (text[i] - 'a' + shift) % 26 + 'a';

            j++;
        }
    }

    printf("Ciphertext: %s", text);
    return 0;
}
Enter plaintext: ATTACKATDAWN
Enter key: LEMON
Ciphertext: LXFOPVEFRNHR
