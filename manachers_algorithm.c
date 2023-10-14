#include <stdio.h>
#include <string.h>

void preprocessString(char* input, char* modified) {
    int index = 0;
    modified[index++] = '#';
    for (int i = 0; input[i] != '\0'; i++) {
        modified[index++] = input[i];
        modified[index++] = '#';
    }
    modified[index] = '\0';
}

void manachersAlgorithm(char* modified) {
    int n = strlen(modified);
    int P[n] ;
    int C = 0, R = 0;
    int maxLen = 0, centerIndex = 0;

    for (int i = 0; i < n; i++) {
        int mirror = 2 * C - i;
        P[i] = (i < R) ? (R - i > P[mirror] ? P[mirror] : R - i) : 0;

        /* Attempt to expand palindrome centered at i */
        int a = i + 1 + P[i];
        int b = i - 1 - P[i];
        while (a < n && b >= 0 && modified[a] == modified[b]) {
            P[i]++;
            a++;
            b--;
        }

        /* If palindrome centered at i expands past R,
           adjust center and right boundary */
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }

        /* Update the maximum palindrome length and its center */
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    /* Print the longest palindromic substring */
    printf("Longest Palindromic Substring: ");
    for (int i = centerIndex - maxLen; i <= centerIndex + maxLen; i++) {
        if (modified[i] != '#') {
            printf("%c", modified[i]);
        }
    }
    printf("\n");
}

int main() {
    char input[] = "madamracecar";
    char modified[2 * strlen(input) + 1];
    preprocessString(input, modified);
    manachersAlgorithm(modified);
    return 0;
}