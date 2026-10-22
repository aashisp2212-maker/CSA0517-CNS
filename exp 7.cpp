#include <stdio.h>

int main(void) {
    char text[3000];
    int freq[256] = {0};
    int i;

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] != '\n')
            freq[(unsigned char)text[i]]++;
    }

    printf("\nCharacter frequencies:\n");
    for (i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i <= 126)
                printf("%c : %d\n", i, freq[i]);
            else
                printf("ASCII %d : %d\n", i, freq[i]);
        }
    }

    printf("\nCommon English letters: E, T, A, O, I, N\n");
    printf("Use letter patterns and words such as THE to help decrypt.\n");

    return 0;
}
Enter ciphertext: ABBA!

Character frequencies:
! : 1
A : 2
B : 2

Common English letters: E, T, A, O, I, N
Use letter patterns and words such as THE to help decrypt.
