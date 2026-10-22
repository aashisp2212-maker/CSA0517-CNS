#include <stdio.h>
#include <ctype.h>

int main(void) {
    char sq[] = "MFHIKUNOPQZVWXYELARGDSTBC";
    char text[500], clean[500];
    int i, j, n = 0, r1, c1, r2, c2;
    char a, b, temp;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i]; i++) {
        a = toupper((unsigned char)text[i]);
        if (a >= 'A' && a <= 'Z') {
            if (a == 'J') a = 'I';
            clean[n++] = a;
        }
    }
    clean[n] = '\0';

    printf("Ciphertext: ");

    for (i = 0; i < n;) {
        a = clean[i++];

        if (i < n && clean[i] == a)
            b = 'X';
        else if (i < n)
            b = clean[i++];
        else
            b = 'X';

        for (j = 0; j < 25; j++) {
            if (sq[j] == a) r1 = j/5, c1 = j%5;
            if (sq[j] == b) r2 = j/5, c2 = j%5;
        }

        if (r1 == r2) {
            a = sq[r1*5 + (c1+1)%5];
            b = sq[r2*5 + (c2+1)%5];
        } else if (c1 == c2) {
            a = sq[((r1+1)%5)*5+c1];
            b = sq[((r2+1)%5)*5+c2];
        } else {
            temp = sq[r1*5+c2];
            b = sq[r2*5+c1];
            a = temp;
        }

        printf("%c%c", a, b);
    }

    printf("\n");
    return 0;
}
Enter plaintext: HI
Ciphertext: IK
Matrix used
M F H I K
U N O P Q
Z V W X Y
E L A R G
D S T B C
