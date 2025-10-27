#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nop, m = 0;
char prod[10][10], res[10];

void FOLLOW(char c);
void FIRST(char c);
void addToResult(char c);

int main() {
    int i, choice;
    char c, ch;

    printf("Enter the number of productions: ");
    scanf("%d", &nop);

    printf("Enter the productions (example: E=E+T):\n");
    for (i = 0; i < nop; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", prod[i]);
    }

    do {
        m = 0;
        printf("\nFind FOLLOW of: ");
        scanf(" %c", &c);

        FOLLOW(c);

        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", res[i]);
        printf("}\n");

        printf("Press 1 to continue: ");
        scanf("%d%c", &choice, &ch);

    } while (choice == 1);

    return 0;
}

// Function to find FOLLOW of a symbol
void FOLLOW(char c) {
    int i, j;

    // Rule 1: Add $ to FOLLOW of start symbol
    if (prod[0][0] == c)
        addToResult('$');

    // Loop through each production
    for (i = 0; i < nop; i++) {
        for (j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                // Case 1: symbol followed by another symbol
                if (prod[i][j + 1] != '\0')
                    FIRST(prod[i][j + 1]);

                // Case 2: symbol at end of production
                if (prod[i][j + 1] == '\0' && c != prod[i][0])
                    FOLLOW(prod[i][0]);
            }
        }
    }
}

// Function to find FIRST of a symbol (used for FOLLOW)
void FIRST(char c) {
    int k;

    // If terminal
    if (!(isupper(c))) {
        addToResult(c);
        return;
    }

    // If non-terminal
    for (k = 0; k < nop; k++) {
        if (prod[k][0] == c) {
            // Case: A → ε
            if (prod[k][2] == '$')
                FOLLOW(prod[k][0]);
            // Case: A → terminal
            else if (islower(prod[k][2]))
                addToResult(prod[k][2]);
            // Case: A → non-terminal
            else
                FIRST(prod[k][2]);
        }
    }
}

// Function to add unique symbols to result set
void addToResult(char c) {
    int i;
    for (i = 0; i < m; i++)
        if (res[i] == c)
            return; // already exists
    res[m++] = c;
}
