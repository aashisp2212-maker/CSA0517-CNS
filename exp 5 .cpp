#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    char text[200];
    int a, b, i;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key a: ");
    scanf("%d", &a);
    printf("Enter key b: ");
    scanf("%d", &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    if (gcd(a, 26) != 1) {
        printf("Invalid key a. Choose a value coprime to 26.\n");
        return 1;
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper((unsigned char)text[i]))
            text[i] = (a * (text[i]-'A') + b) % 26 + 'A';
        else if (islower((unsigned char)text[i]))
            text[i] = (a * (text[i]-'a') + b) % 26 + 'a';
    }

    printf("Ciphertext: %s", text);
    return 0;
}
Enter plaintext: HELLO
Enter key a: 5
Enter key b: 8
Ciphertext: RCLLA
