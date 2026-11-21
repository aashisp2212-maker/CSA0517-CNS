#include <stdio.h>

int main(void) {
    const int lanes = 8;
    double harmonic = 0.0;

    for (int i = 1; i <= lanes; ++i)
        harmonic += 1.0 / i;

    printf("Expected blocks (coupon collector approximation): %.2f\n",
           64.0 * harmonic);
    return 0;
}
