#include <stdio.h>
#include <stdint.h>

uint32_t rotate28(uint32_t value, int shift) {
    value &= 0x0FFFFFFF;
    return ((value << shift) |
            (value >> (28 - shift))) & 0x0FFFFFFF;
}

int main(void) {
    int shifts[16] = {
        1, 1, 2, 2, 2, 2, 2, 2,
        1, 2, 2, 2, 2, 2, 2, 1
    };

    uint32_t C = 0x0ABCDE1;
    uint32_t D = 0x0123456;
    int i;

    printf("DES 28-bit half rotations:\n");

    for (i = 0; i < 16; i++) {
        C = rotate28(C, shifts[i]);
        D = rotate28(D, shifts[i]);

        printf("Round %2d: C=%07X D=%07X\n",
               i + 1, C, D);
    }

    return 0;
}
DES 28-bit half rotations:
Round  1: C=1579BC2 D=02468AD
Round  2: C=2AF3784 D=048D15A
Round  3: C=2BCF0E1 D=1234568
Round  4: C=2F3C384 D=48D1590
Round  5: C=3CF0E12 D=2345621
Round  6: C=3C3842B D=8D15848
Round  7: C=E10ACF0 D=3456212
Round  8: C=10579E1 D=D158489
Round  9: C=20AF3C2 D=A2B0913
Round 10: C=82BCF08 D=8AC244E
Round 11: C=0AF3C20 D=2B0913A
Round 12: C=2BCF082 D=AC244E8
Round 13: C=F3C20AF D=B0913A2
Round 14: C=CF082BC D=C244E8A
Round 15: C=3C20AF3 D=0913A2B
Round 16: C=78415E7 D=244E8AC
