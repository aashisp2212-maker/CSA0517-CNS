#include <stdio.h>
#include <string.h>

int pkcs7_pad(const unsigned char *in, size_t len, size_t block,
              unsigned char *out) {
    if (!block || block > 255) return -1;
    size_t pad = block - (len % block); /* full block if already aligned */
    memcpy(out, in, len);
    memset(out + len, (int)pad, pad);
    return (int)(len + pad);
}

int main(void) {
    unsigned char out[64];
    const unsigned char msg[] = "ABCDEFGH";
    int n = pkcs7_pad(msg, 8, 8, out);

    printf("Padded length: %d\n", n); /* 16 */
    return 0;
}
