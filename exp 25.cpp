#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(void) {
    int p, q, n, m, g;

    printf("Enter prime p: ");
    scanf("%d", &p);

    printf("Enter prime q: ");
    scanf("%d", &q);

    n = p * q;

    printf("Enter plaintext block m: ");
    scanf("%d", &m);

    g = gcd(m, n);

    printf("RSA modulus n = %d\n", n);
    printf("GCD(m, n) = %d\n", g);

    if (g > 1 && g < n) {
        printf("A nontrivial factor of n is found!\n");
        printf("Factors of n: %d and %d\n", g, n / g);
        printf("RSA security is compromised.\n");
    } else {
        printf("No nontrivial factor found.\n");
    }

    return 0;
}
Enter prime p: 59
Enter prime q: 61
Enter plaintext block m: 118
RSA modulus n = 3599
GCD(m, n) = 59
A nontrivial factor of n is found!
Factors of n: 59 and 61
RSA security is compromised.
