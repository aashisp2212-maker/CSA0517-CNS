/* Build: cc q33.c -o q33 -lcrypto */
#include <openssl/des.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    DES_cblock key = {1,2,3,4,5,6,7,8};
    DES_key_schedule schedule;
    DES_set_key_unchecked(&key, &schedule);

    DES_cblock plain = "1234567"; /* 8 bytes including NUL */
    DES_cblock cipher, recovered;

    DES_ecb_encrypt(&plain, &cipher, &schedule, DES_ENCRYPT);
    DES_ecb_encrypt(&cipher, &recovered, &schedule, DES_DECRYPT);

    printf("Recovered: %s\n", (char *)recovered);
    return 0;
}
