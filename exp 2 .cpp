#include <stdio.h>
#include <ctype.h>

int main() {
    char text[200];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i, index;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            index = toupper((unsigned char)text[i]) - 'A';
            text[i] = isupper((unsigned char)text[i])
                    ? key[index] : tolower(key[index]);
        }
    }

    printf("Ciphertext: %s", text);
    return 0;
}
Enter plaintext: HELLO
Ciphertext: ITSSG
