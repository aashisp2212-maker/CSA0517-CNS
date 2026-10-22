#include <stdio.h>
#include <ctype.h>

int mod26(int x) {
    x %= 26;
    return x < 0 ? x + 26 : x;
}

int inverse(int a) {
    int i;
    for (i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1;
}

int main(void) {
    char text[500], p[500], c[500];
    int i, n = 0, a = 9, b = 4, d = 5, e = 7;
    int det = mod26(a*e - b*d), inv = inverse(det);

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i]; i++)
        if (isalpha((unsigned char)text[i]))
            p[n++] = toupper((unsigned char)text[i]);

    if (n % 2) p[n++] = 'X';
    p[n] = '\0';

    for (i = 0; i < n; i += 2) {
        int x = p[i] - 'A', y = p[i+1] - 'A';
        c[i]   = 'A' + mod26(a*x + b*y);
        c[i+1] = 'A' + mod26(d*x + e*y);
    }
    c[n] = '\0';

    printf("Ciphertext: %s\n", c);

    if (inv == -1) {
        printf("Key cannot be inverted modulo 26.\n");
        return 1;
    }

    printf("Decrypted: ");
    for (i = 0; i < n; i += 2) {
        int x = c[i] - 'A', y = c[i+1] - 'A';
        int u = mod26(inv * mod26(e*x - b*y));
        int v = mod26(inv * mod26(a*y - d*x));
        printf("%c%c", 'A'+u, 'A'+v);
    }

    printf("\n");
    return 0;
}
Enter plaintext: HELP
Ciphertext: BLDE
Decrypted: HELP
