#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Structure to store each three-address code statement
struct expr {
    char op[2];     // Operator (+, -, *, /, =)
    char op1[5];    // Operand 1
    char op2[5];    // Operand 2
    char res[5];    // Result variable
    int flag;       // 0 = keep, 1 = delete (optimized)
} arr[10];

int n;  // number of expressions

// Function declarations
void input();
void constantFoldingAndPropagation();
void change(int p, char *res);
void output();

// Function to take input
void input() {
    int i;
    printf("\nEnter the number of expressions: ");
    scanf("%d", &n);
    printf("\nEnter the input (format: op op1 op2 res):\n");
    printf("Example: + 2 3 t1\n\n");

    for (i = 0; i < n; i++) {
        printf("Expression %d: ", i + 1);
        scanf("%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
        arr[i].flag = 0; // initialize as active
    }
}

// Function to replace occurrences of a variable with a constant in later lines
void change(int p, char *res) {
    int i;
    for (i = p + 1; i < n; i++) {
        // If result of current expression is used as operand in later expressions
        if (strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, res);
        else if (strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, res);
    }
}

// Function for constant folding and propagation
void constantFoldingAndPropagation() {
    int i, op1, op2, res;
    char op, resStr[5];

    for (i = 0; i < n; i++) {
        // Check if both operands are digits (constants)
        // or it’s an assignment operation (=)
        if ((isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) ||
            strcmp(arr[i].op, "=") == 0) {

            // Convert string operands to integers
            op1 = atoi(arr[i].op1);
            op2 = atoi(arr[i].op2);
            op = arr[i].op[0];

            // Perform the operation
            switch (op) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '=': res = op1; break;
                default: continue; // skip unknown operators
            }

            // Convert result to string
            sprintf(resStr, "%d", res);

            // Mark this expression as redundant (already optimized)
            arr[i].flag = 1;

            // Propagate result to later statements
            change(i, resStr);
        }
    }
}

// Function to print optimized code
void output() {
    int i;
    printf("\nOptimized code is:\n");
    for (i = 0; i < n; i++) {
        if (!arr[i].flag) {
            printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
        }
    }
}

// Main function
int main() {
    input();
    constantFoldingAndPropagation();
    output();
    return 0;
}
