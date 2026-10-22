#include <stdio.h>
#include <math.h>

int main(void) {
    long double fact = 1.0L;
    int i;

    for (i = 2; i <= 25; i++)
        fact *= i;

    printf("Number of possible keys = 25!\n");
    printf("Approximate value = %.3Le\n", fact);
    printf("Equivalent power of 2 = 2^%.2Lf\n",
           logl(fact) / logl(2.0L));

    return 0;
}
Number of possible keys = 25!
Approximate value = 1.551e+25
Equivalent power of 2 = 2^83.68
