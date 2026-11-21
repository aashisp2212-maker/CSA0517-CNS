#include <stdio.h>
#include <stdint.h>

/* Demonstration only: real RSA needs large integers and secure padding. */
static uint64_t mod_pow(uint64_t a, uint64_t e, uint64_t n) {
    uint64_t result = 1;
    while (e) {
        if (e & 1) result = (result * a) % n;
        a = (a * a) % n;
        e >>= 1;
    }
    return result;
}

int main(void) {
    uint64_t e, n, c[26];

    printf("Enter public exponent e and modulus n: ");
    if (scanf("%llu %llu", (unsigned long long *)&e,
              (unsigned long long *)&n) != 2) return 1;

    for (int m = 0; m < 26; ++m)
        c[m] = mod_pow((uint64_t)m, e, n);

    puts("Codebook (plaintext 0..25 -> ciphertext):");
    for (int m = 0; m < 26; ++m)
        printf("%d -> %llu\n", m, (unsigned long long)c[m]);
    return 0;
}
