#include <stdio.h>

static int mod(int x) { x %= 26; return x < 0 ? x + 26 : x; }

static int inv26(int a) {
    for (int x = 1; x < 26; ++x)
        if (mod(a * x) == 1) return x;
    return -1;
}

int main(void) {
    /* Columns are two known plaintext vectors and matching ciphertext vectors.
       Replace these demo values with the known pairs. */
    int P[2][2] = {{7, 11}, {4, 15}};
    int C[2][2] = {{8, 19}, {5, 3}};

    int det = mod(P[0][0] * P[1][1] - P[0][1] * P[1][0]);
    int invdet = inv26(det);
    if (invdet < 0) {
        puts("Chosen plaintext matrix is not invertible modulo 26.");
        return 1;
    }

    int Pinv[2][2] = {
        {mod(invdet * P[1][1]), mod(-invdet * P[0][1])},
        {mod(-invdet * P[1][0]), mod(invdet * P[0][0])}
    };

    int K[2][2];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            K[i][j] = mod(C[i][0] * Pinv[0][j] +
                          C[i][1] * Pinv[1][j]);

    printf("Recovered key matrix: [[%d,%d],[%d,%d]]\n",
           K[0][0], K[0][1], K[1][0], K[1][1]);
    return 0;
}
