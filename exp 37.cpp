#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char text[10000];
    int count[26] = {0}, total = 0;

    puts("Enter ciphertext (one line):");
    if (!fgets(text, sizeof text, stdin)) return 1;

    for (size_t i = 0; text[i]; ++i) {
        if (isalpha((unsigned char)text[i])) {
            count[toupper((unsigned char)text[i]) - 'A']++;
            total++;
        }
    }

    const char *english = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    for (int rank = 0; rank < 26; ++rank) {
        int best = -1;
        for (int i = 0; i < 26; ++i)
            if (best < 0 || count[i] > count[best]) best = i;
        if (best < 0) break;
        printf("%c -> likely %c (%.1f%%)\n", 'A' + best,
               english[rank], total ? 100.0 * count[best] / total : 0.0);
        count[best] = -1;
    }
    return 0;
}
