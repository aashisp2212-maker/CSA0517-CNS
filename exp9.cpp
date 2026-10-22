#include <stdio.h>
#include <ctype.h>

int main(void) {
    char key[100], ct[500], sq[25], out[500];
    int used[26] = {0}, n = 0, i, j, r1, c1, r2, c2;
    char a, b, temp;

    printf("Enter keyword: ");
    scanf("%99s", key);
    printf("Enter ciphertext (even number of letters): ");
    scanf("%499s", ct);

    for (i = 0; key[i]; i++) {
        a = toupper((unsigned char)key[i]);
        if (a == 'J') a = 'I';
        if (a >= 'A' && a <= 'Z' && !used[a-'A']) {
            sq[n++] = a;
            used[a-'A'] = 1;
        }
    }

    for (a = 'A'; a <= 'Z'; a++)
        if (a != 'J' && !used[a-'A'])
            sq[n++] = a;

    n = 0;
    while (ct[n]) n++;

    if (n % 2 != 0) {
        printf("Ciphertext must contain an even number of letters.\n");
        return 1;
    }

    for (i = 0; i < n; i += 2) {
        a = toupper((unsigned char)ct[i]);
        b = toupper((unsigned char)ct[i+1]);
        if (a == 'J') a = 'I';
        if (b == 'J') b = 'I';

        for (j = 0; j < 25; j++) {
            if (sq[j] == a) r1 = j/5, c1 = j%5;
            if (sq[j] == b) r2 = j/5, c2 = j%5;
        }

        if (r1 == r2) {
            a = sq[r1*5 + (c1+4)%5];
            b = sq[r2*5 + (c2+4)%5];
        } else if (c1 == c2) {
            a = sq[((r1+4)%5)*5+c1];
            b = sq[((r2+4)%5)*5+c2];
        } else {
            temp = sq[r1*5+c2];
            b = sq[r2*5+c1];
            a = temp;
        }

        out[i] = a;
        out[i+1] = b;
    }

    out[n] = '\0';
    printf("Plaintext: %s\n", out);
    return 0;
}
Enter keyword: MONARCHY
Enter ciphertext (even number of letters): GATLMZ
Plaintext: INSTRU
