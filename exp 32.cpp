#include <stdio.h>

int main(void) {
    puts("DSA: never reuse k. Reuse can expose the private key.");
    puts("RSA: textbook RSA signatures are deterministic.");
    puts("RSA-PSS uses a salt; use a vetted library for signing.");
    return 0;
}
