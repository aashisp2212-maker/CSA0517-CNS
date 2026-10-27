#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char cipher[2000], plain[2000];
    int freq[26] = {0};
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    char map[26];
    int used[26] = {0};
    int i, j, n;

    printf("Enter encrypted text:\n");
    if (!fgets(cipher, sizeof(cipher), stdin))
        return 1;

    for (i = 0; cipher[i]; i++) {
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;
    }

    /* Rank ciphertext letters by frequency */
    for (i = 0; i < 26; i++) {
        int best = -1;
        for (j = 0; j < 26; j++)
            if (!used[j] &&
                (best == -1 || freq[j] > freq[best]))
                best = j;

        used[best] = 1;
        map[best] = english[i];
    }

    n = (int)strlen(cipher);

    for (i = 0; i < n; i++) {
        unsigned char c = (unsigned char)cipher[i];

        if (isupper(c))
            plain[i] = map[c - 'A'];
        else if (islower(c))
            plain[i] = (char)tolower(map[toupper(c) - 'A']);
        else
            plain[i] = (char)c;
    }

    plain[n] = '\0';

    printf("\nPossible plaintext:\n%s\n", plain);
    printf("\nNote: This is only a frequency-based guess.\n");
    return 0;
}
Enter encrypted text:
WKH TXLFN EURZQ IRA

Possible plaintext:
ETA ONSCT DUJHW PBD

Note: This is only a frequency-based guess.
