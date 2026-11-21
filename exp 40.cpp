#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 20000
#define NGRAMS 456976  /* 26^4 */

static double logp[NGRAMS];
static const char *english_order = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

static int index4(int a, int b, int c, int d) {
    return ((a * 26 + b) * 26 + c) * 26 + d;
}

static void load_ngrams(const char *filename) {
    for (int i = 0; i < NGRAMS; ++i) logp[i] = -12.0;

    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Cannot open tetragram file: %s\n", filename);
        exit(1);
    }

    char gram[32];
    double count, total = 0;
    while (fscanf(f, "%31s %lf", gram, &count) == 2)
        if (strlen(gram) == 4 && count > 0) total += count;

    rewind(f);
    while (fscanf(f, "%31s %lf", gram, &count) == 2) {
        if (strlen(gram) != 4 || count <= 0) continue;
        int a = toupper((unsigned char)gram[0]) - 'A';
        int b = toupper((unsigned char)gram[1]) - 'A';
        int c = toupper((unsigned char)gram[2]) - 'A';
        int d = toupper((unsigned char)gram[3]) - 'A';
        if (a >= 0 && a < 26 && b >= 0 && b < 26 &&
            c >= 0 && c < 26 && d >= 0 && d < 26)
            logp[index4(a, b, c, d)] = log(count / total);
    }
    fclose(f);
}

static double score(const int *cipher, int n, const int *key) {
    double s = 0;
    for (int i = 0; i + 3 < n; ++i)
        s += logp[index4(key[cipher[i]], key[cipher[i + 1]],
                         key[cipher[i + 2]], key[cipher[i + 3]])];
    return s;
}

static void shuffle_key(int *key) {
    for (int i = 0; i < 26; ++i) key[i] = i;
    for (int i = 25; i > 0; --i) {
        int j = rand() % (i + 1);
        int t = key[i]; key[i] = key[j]; key[j] = t;
    }
}

static void print_plain(const char *original, const int *key) {
    for (size_t i = 0; original[i]; ++i) {
        unsigned char ch = (unsigned char)original[i];
        if (isupper(ch)) putchar('A' + key[ch - 'A']);
        else if (islower(ch)) putchar('a' + key[ch - 'a']);
        else putchar(ch);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s tetragrams.txt\n", argv[0]);
        return 1;
    }
    load_ngrams(argv[1]);

    char original[MAX_TEXT];
    puts("Enter ciphertext:");
    if (!fgets(original, sizeof original, stdin)) return 1;

    int cipher[MAX_TEXT], n = 0, counts[26] = {0};
    for (size_t i = 0; original[i] && n < MAX_TEXT; ++i) {
        if (isalpha((unsigned char)original[i])) {
            cipher[n] = toupper((unsigned char)original[i]) - 'A';
            counts[cipher[n++]]++;
        }
    }
    if (n < 4) {
        puts("Enter at least four letters.");
        return 1;
    }

    /* Frequency mapping provides a starting candidate. */
    int order[26], key[26];
    for (int i = 0; i < 26; ++i) order[i] = i;
    for (int i = 0; i < 26; ++i)
        for (int j = i + 1; j < 26; ++j)
            if (counts[order[j]] > counts[order[i]]) {
                int t = order[i]; order[i] = order[j]; order[j] = t;
            }
    for (int i = 0; i < 26; ++i)
        key[order[i]] = english_order[i] - 'A';

    int best_key[26];
    memcpy(best_key, key, sizeof key);
    double best = score(cipher, n, key);

    /* Random-restart substitution-key search. */
    srand(1);
    for (int restart = 0; restart < 30; ++restart) {
        if (restart == 0) memcpy(key, best_key, sizeof key);
        else shuffle_key(key);

        double current = score(cipher, n, key);
        for (int step = 0; step < 30000; ++step) {
            int a = rand() % 26, b = rand() % 26;
            int t = key[a]; key[a] = key[b]; key[b] = t;

            double next = score(cipher, n, key);
            double temperature = 8.0 * (1.0 - (double)step / 30000.0) + 0.1;
            double probability = exp((next - current) / temperature);

            if (next > current || (double)rand() / RAND_MAX < probability) {
                current = next;
                if (current > best) {
                    best = current;
                    memcpy(best_key, key, sizeof key);
                }
            } else {
                t = key[a]; key[a] = key[b]; key[b] = t;
            }
        }
    }

    puts("Best candidate found:");
    print_plain(original, best_key);
    putchar('\n');
    puts("This heuristic search returns one strong candidate; longer ciphertexts "
         "and better tetragram data improve results.");
    return 0;
}
