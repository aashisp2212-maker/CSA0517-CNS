#include <stdio.h>
#include <ctype.h>

int main(void) {
    char text[1000];
    int shift, i;

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    for (shift = 0; shift < 26; shift++) {
        printf("Shift %2d: ", shift);

        for (i = 0; text[i] != '\0'; i++) {
            if (isupper((unsigned char)text[i]))
                putchar((text[i] - 'A' - shift + 26) % 26 + 'A');
            else if (islower((unsigned char)text[i]))
                putchar((text[i] - 'a' - shift + 26) % 26 + 'a');
            else
                putchar(text[i]);
        }
    }

    printf("\nExamine the candidates to identify likely English text.\n");
    return 0;
}
Enter ciphertext: KHOOR
Shift  0: KHOOR
Shift  1: JGNNQ
Shift  2: IFMMP
Shift  3: HELLO
...
Shift 25: LIPPS
