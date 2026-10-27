#include <stdio.h>

int perm(int x, const int *t, int n, int bits) {
    int r = 0;
    for (int i = 0; i < n; i++)
        r = (r << 1) | ((x >> (bits - t[i])) & 1);
    return r;
}

int P10[]={3,5,2,7,4,10,1,9,8,6};
int P8[]={6,3,7,4,8,5,10,9};
int IP[]={2,6,3,1,4,8,5,7};
int IPI[]={4,1,3,5,7,2,8,6};
int EP[]={4,1,2,3,2,3,4,1};
int P4[]={2,4,3,1};
int S0[4][4]={{1,0,3,2},{3,2,1,0},
              {0,2,1,3},{3,1,3,2}};
int S1[4][4]={{0,1,2,3},{2,0,1,3},
              {3,0,1,0},{2,1,0,3}};

int K1,K2;

int rot5(int x,int s) {
    return ((x<<s)|(x>>(5-s)))&31;
}

void keys(int k) {
    int x=perm(k,P10,10,10);
    int l=(x>>5)&31,r=x&31;
    l=rot5(l,1); r=rot5(r,1);
    K1=perm((l<<5)|r,P8,8,10);
    l=rot5(l,2); r=rot5(r,2);
    K2=perm((l<<5)|r,P8,8,10);
}

int sb(int x,int box[4][4]) {
    int row=((x&8)>>2)|(x&1);
    int col=(x>>1)&3;
    return box[row][col];
}

int fk(int x,int k) {
    int l=x>>4,r=x&15;
    int z=perm(r,EP,8,4)^k;
    int y=(sb(z>>4,S0)<<2)|sb(z&15,S1);
    return (((l^perm(y,P4,4,4))<<4)|r);
}

int crypt(int x,int decrypt) {
    int a=perm(x,IP,8,8);
    a=fk(a,decrypt?K2:K1);
    a=((a&15)<<4)|(a>>4);
    a=fk(a,decrypt?K1:K2);
    return perm(a,IPI,8,8);
}

int main(void) {
    unsigned char p[]={0x01,0x23};
    unsigned char c[2],d[2];
    int iv=0xAA,prev=iv;
    keys(0x1FD);

    for(int i=0;i<2;i++) {
        c[i]=crypt(p[i]^prev,0);
        prev=c[i];
    }

    printf("CBC Encryption:\n");
    for(int i=0;i<2;i++)
        printf("%08d ",0); /* replaced below */
    printf("\nCiphertext: ");
    for(int i=0;i<2;i++)
        for(int b=7;b>=0;b--)
            printf("%d",(c[i]>>b)&1);

    prev=iv;
    for(int i=0;i<2;i++) {CBC Encryption:
Ciphertext: 1111010000001011

CBC Decryption:
Plaintext: 0000000100100011
        d[i]=crypt(c[i],1)^prev;
        prev=c[i];
    }

    printf("\n\nCBC Decryption:\nPlaintext: ");
    for(int i=0;i<2;i++)
        for(int b=7;b>=0;b--)
            printf("%d",(d[i]>>b)&1);
    printf("\n");
    return 0;
}
