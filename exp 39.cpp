#include <ctype.h>
#include <stdio.h>
#include <string.h>

static const double english[26] = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.15,
    0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1,
    2.8, 0.98, 2.4, 0.15, 2.0, 0.074
};

typedef struct {
    int shift;
    double score;
} Candidate;

static double score_text(const char *text, int shift) {
    int counts[26] = {0}, total = 0;

    for (size_t i = 0; text[i]; ++i) {
        if (isalpha((unsigned char)text[i])) {
            int c = toupper((unsigned char)text[i]) - 'A';
            int p = (c - shift + 26) % 26;
            counts[p]++;
            total++;
        }
    }

    if (!total) return -1e9;

    double score = 0;
    for (int i = 0; i < 26; ++i)
        score += (100.0 * counts[i] / total) * english[i];

    return score;
}

static void print_decryption(const char *text, int shift) {
    for (size_t i = 0; text[i]; ++i) {
        unsigned char ch = (unsigned char)text[i];
        if (isupper(ch))
            putchar('A' + (ch - 'A' - shift + 26) % 26);
        else if (islower(ch))
            putchar('a' + (ch - 'a' - shift + 26) % 26);
        else
            putchar(ch);
    }
}

int main(void) {
    char ciphertext[10000];
    Candidate candidates[26];

    puts("Enter ciphertext:");
    if (!fgets(ciphertext, sizeof ciphertext, stdin)) return 1;

    for (int shift = 0; shift < 26; ++shift) {
        candidates[shift] = (Candidate){shift, score_text(ciphertext, shift)};
    }

    /* Sort candidates from highest score to lowest. */
    for (int i = 0; i < 26; ++i)
        for (int j = i + 1; j < 26; ++j)
            if (candidates[j].score > candidates[i].score) {
                Candidate temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }

    int top = 10;
    printf("How many candidates (1-26)? ");
    if (scanf("%d", &top) != 1) top = 10;
    if (top < 1) top = 1;
    if (top > 26) top = 26;

    for (int i = 0; i < top; ++i) {
        printf("\nShift %d, score %.2f: ", candidates[i].shift,
               candidates[i].score);
        print_decryption(ciphertext, candidates[i].shift);
    }
    putchar('\n');
    return 0;
}
