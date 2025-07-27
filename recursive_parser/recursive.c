#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;
int length;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error() {
    printf("\n❌ Error at position %d\n", pos + 1);
    exit(1);
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}

// E -> T E'
void E() {
    T();
    Eprime();
}

// E' -> + T E' | ε
void Eprime() {
    if (input[pos] == '+') {
        match('+');
        T();
        Eprime();
    }
}

// T -> F T'
void T() {
    F();
    Tprime();
}

// T' -> * F T' | ε
void Tprime() {
    if (input[pos] == '*') {
        match('*');
        F();
        Tprime();
    }
}

// F -> (E) | id
void F() {
    if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalpha(input[pos])) {  // id can be single letter
        match(input[pos]);  // match the identifier
    } else {
        error();
    }
}

int main() {
    printf("Enter the expression: ");
    scanf("%s", input);
    length = strlen(input);

    E();

    if (pos == length) {
        printf("✅ Parsing successful.\n");
    } else {
        printf("❌ Error: Input not fully consumed at position %d\n", pos + 1);
    }

    return 0;
}
