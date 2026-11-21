#include <stdint.h>
#include <stdio.h>

static void left_shift(uint8_t *out, const uint8_t *in, int n) {
    uint8_t carry = 0;
    for (int i = n - 1; i >= 0; --i) {
        uint8_t next = in[i] >> 7;
        out[i] = (uint8_t)((in[i] << 1) | carry);
        carry = next;
    }
}

static void cmac_subkey(uint8_t *out, const uint8_t *L, int n,
                        uint8_t Rb) {
    left_shift(out, L, n);
    if (L[0] & 0x80)
        out[n - 1] ^= Rb;
}

int main(void) {
    uint8_t L128[16] = {0}, K1[16], K2[16];
    /* Supply L = E_K(0^128) from a real block cipher. */
    cmac_subkey(K1, L128, 16, 0x87);
    cmac_subkey(K2, K1, 16, 0x87);

    puts("Computed two 128-bit CMAC subkeys (demo input was all zero).");
    return 0;
}
