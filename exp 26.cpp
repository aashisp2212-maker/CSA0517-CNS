
/* OpenSSL 3.x: generate a completely new RSA key pair.
   Build: cc q26.c -o q26 -lcrypto */

#include <openssl/evp.h>
#include <stdio.h>

int main(void) {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL);
    EVP_PKEY *key = NULL;

    if (!ctx || EVP_PKEY_keygen_init(ctx) <= 0 ||
        EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0 ||
        EVP_PKEY_keygen(ctx, &key) <= 0) {
        fprintf(stderr, "RSA key generation failed\n");
        EVP_PKEY_CTX_free(ctx);
        return 1;
    }

    puts("Generated a new RSA key pair with a new modulus.");
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(ctx);
    return 0;
}
