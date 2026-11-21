#include <stdio.h>

int gcd(int a, int b)
{
    while(b != 0){
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(void)
{
    int n, m, g;

    printf("Enter RSA modulus n: ");
    scanf("%d",&n);

    printf("Enter plaintext block m: ");
    scanf("%d",&m);

    g = gcd(n,m);

    printf("GCD(m,n) = %d\n",g);

    if(g > 1 && g < n){
        printf("Factor 1 = %d\n",g);
        printf("Factor 2 = %d\n",n/g);
        printf("RSA modulus can be factored.\n");
    }
    else{
        printf("No non-trivial factor found.\n");
    }

    return 0;
}
