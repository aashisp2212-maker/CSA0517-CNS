#include <stdint.h>
#include <stdio.h>

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
    const uint64_t q = 23, x = 5;
    const uint64_t a = 6, b = 15; /* private secrets */

    uint64_t A = mod_pow(x, a, q);
    uint64_t B = mod_pow(x, b, q);
    uint64_t alice_key = mod_pow(B, a, q);
    uint64_t bob_key = mod_pow(A, b, q);

    printf("Alice sends %llu; Bob sends %llu\n",
           (unsigned long long)A, (unsigned long long)B);
    printf("Shared values: %llu and %llu\n",
           (unsigned long long)alice_key, (unsigned long long)bob_key);
    return 0;
}
