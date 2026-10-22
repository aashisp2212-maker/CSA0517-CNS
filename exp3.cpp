#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char key[100], text[300], square[25], used[26] = {0};
    int i, j, n = 0, pos, r1, c1, r2, c2;
    char a, b, temp;

    printf("Enter keyword: ");
    scanf("%99s", key);
    printf("Enter plaintext: ");
    scanf(" %299[^\n]", text);

    for (i = 0; key[i]; i++) {
        a = toupper((unsigned char)key[i]);
        if (a == 'J') a = 'I';
        if (a >= 'A' && a <= 'Z' && !used[a-'A']) {
            square[n++] = a;
            used[a-'A'] = 1;
        }
    }

    for (a = 'A'; a <= 'Z'; a++) {
        if (a == 'J') continue;
        if (!used[a-'A']) square[n++] = a;
    }

    printf("\nPlayfair matrix:\n");
    for (i = 0; i < 25; i++) {
        printf("%c ", square[i]);
        if (i % 5 == 4) printf("\n");
    }

    char clean[300], out[600];
    n = 0;

    for (i = 0; text[i]; i++) {
        a = toupper((unsigned char)text[i]);
        if (a >= 'A' && a <= 'Z') {
            if (a == 'J') a = 'I';
            clean[n++] = a;
        }
    }
    clean[n] = '\0';

    pos = 0;
    for (i = 0; i < n;) {
        a = clean[i++];
        if (i < n && clean[i] == a) b = 'X';
        else if (i < n) b = clean[i++];
        else b = 'X';

        r1 = c1 = r2 = c2 = 0;
        for (j = 0; j < 25; j++) {
            if (square[j] == a) r1 = j / 5, c1 = j % 5;
            if (square[j] == b) r2 = j / 5, c2 = j % 5;
        }

        if (r1 == r2) {
            a = square[r1*5 + (c1+1)%5];
            b = square[r2*5 + (c2+1)%5];
        } else if (c1 == c2) {
            a = square[((r1+1)%5)*5 + c1];
            b = square[((r2+1)%5)*5 + c2];
        } else {
            temp = square[r1*5+c2];
            b = square[r2*5+c1];
            a = temp;
        }

        out[pos++] = a;
        out[pos++] = b;
    }
    out[pos] = '\0';

    printf("Ciphertext: %s\n", out);
    return 0;
}
Keyword MONARCHY, plaintext INSTRUMENTS
Cipher text: GATLMZCLRQXA
