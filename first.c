#include <stdio.h>
#include <ctype.h>
#include <string.h>

int numOfProductions;
char productionSet[10][10];

// Function declarations
void FIRST(char[], char);
void addToResultSet(char[], char);

// Main function
int main() {
    int i;
    char choice;
    char c;
    char result[20];

    printf("Enter the number of productions: ");
    scanf("%d", &numOfProductions);

    printf("Enter the productions (example: E=E+T):\n");
    for (i = 0; i < numOfProductions; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", productionSet[i]);
    }

    do {
        printf("\nFind the FIRST of: ");
        scanf(" %c", &c);

        FIRST(result, c);

        printf("FIRST(%c) = { ", c);
        for (i = 0; result[i] != '\0'; i++)
            printf("%c ", result[i]);
        printf("}\n");

        printf("Press 'y' to continue: ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

// Function to find FIRST of a symbol
void FIRST(char *Result, char c) {
    int i, j, k;
    char subResult[20];
    int foundEpsilon;

    subResult[0] = '\0';
    Result[0] = '\0';

    // If terminal, add to result directly
    if (!(isupper(c))) {
        addToResultSet(Result, c);
        return;
    }

    // If non-terminal, find its productions
    for (i = 0; i < numOfProductions; i++) {
        if (productionSet[i][0] == c) {
            // Case: A → ε
            if (productionSet[i][2] == '$')
                addToResultSet(Result, '$');
            else {
                j = 2;
                while (productionSet[i][j] != '\0') {
                    foundEpsilon = 0;
                    FIRST(subResult, productionSet[i][j]);

                    // Add subResult to main Result
                    for (k = 0; subResult[k] != '\0'; k++)
                        addToResultSet(Result, subResult[k]);

                    // If ε found, continue to next symbol
                    for (k = 0; subResult[k] != '\0'; k++) {
                        if (subResult[k] == '$') {
                            foundEpsilon = 1;
                            break;
                        }
                    }

                    // Stop if ε not found
                    if (!foundEpsilon)
                        break;

                    j++;
                }
            }
        }
    }
    return;
}

// Function to add terminal/non-terminal to result set
void addToResultSet(char Result[], char val) {
    int k;
    for (k = 0; Result[k] != '\0'; k++)
        if (Result[k] == val)
            return; // Already exists

    Result[k] = val;
    Result[k + 1] = '\0';
}
