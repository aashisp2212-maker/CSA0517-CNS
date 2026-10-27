int main(void) {
    unsigned char p[] = {0x01, 0x02, 0x04};
    unsigned char c[3], d[3];
    keys(0x1FD);

    printf("CTR Encryption:\nCiphertext: ");

    for (int i = 0; i < 3; i++) {
        unsigned char stream = crypt(i, 0);
        c[i] = p[i] ^ stream;

        for (int b = 7; b >= 0; b--)
            printf("%d", (c[i] >> b) & 1);
    }

    printf("\n\nCTR Decryption:\nPlaintext: ");

    for (int i = 0; i < 3; i++) {
        unsigned char stream = crypt(i, 0);
        d[i] = c[i] ^ stream;

        for (int b = 7; b >= 0; b--)
            printf("%d", (d[i] >> b) & 1);
    }

    printf("\n");
    return 0;
}
CTR Encryption:
Ciphertext: 001110000100111100110010

CTR Decryption:
Plaintext: 000000010000001000000100
