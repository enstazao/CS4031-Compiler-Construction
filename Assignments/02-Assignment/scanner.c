#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function to check if a string is a reserved word
int isReservedWord(char* str) {
    char *keywords[] = {"switch", "if", "auto", "int", "struct", "char", "else", "goto", "default", "while", "for"};
    int num_keywords = 11;
    int i;
    for (i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// function to write output to file
void writeOutput(char* token, char* type, int count, FILE* fp) {
    if (count > 0) {
        fprintf(fp, "%s\t<%s, %d>\n", token, type, count);
    } else {
        fprintf(fp, "%s\t<%s>\n", token, type);
    }
}

int main() {
    char input_filename[] = "input_file.txt";
    char output_filename[] = "output_file.txt";
    char buffer[100];
    int count = 0; // count of identifiers
    FILE* fp_input = fopen(input_filename, "r");
    FILE* fp_output = fopen(output_filename, "w");
    if (fp_input == NULL || fp_output == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    while (fscanf(fp_input, "%s", buffer) == 1) {
        // check if identifier
        if (buffer[0] == '@' && isalpha(buffer[1])) {
            int valid = 1;
            int i = 2;
            while (buffer[i] != '\0') {
                if (!isalnum(buffer[i])) {
                    valid = 0;
                    break;
                }
                i++;
            }
            if (valid) {
                count++;
                writeOutput(buffer, "id", count, fp_output);
                continue;
            }
        }
        // check if reserved word
        if (isReservedWord(buffer)) {
            char reserved_type[25];
            fprintf(fp_output,  "%s\t<%s%s>\n", buffer, buffer, "");
            continue;
        }
        // check if operator
        if (strchr("+-*/%><!=&|", buffer[0])) {
            char op_type[5];
            switch(buffer[0]) {
                case '+':
                    strcpy(op_type, "+");
                    break;
                case '-':
                    strcpy(op_type, "-");
                    break;
                case '*':
                    strcpy(op_type, "*");
                    break;
                case '/':
                    strcpy(op_type, "/");
                    break;
                case '%':
                    strcpy(op_type, "%");
                    break;
                case '>':
                    strcpy(op_type, ">");
                    break;

                case '<':
                    strcpy(op_type, "<");
                    break;
                case '=':
                    strcpy(op_type, "=");
                    break;
                case '!':
                    strcpy(op_type, "!");
                    break;
            }
            writeOutput(buffer, op_type, 0, fp_output);
            continue;
        }
        // check if parenthesis
        if (strchr("{}()[],", buffer[0])) {
            char type[5];
            switch (buffer[0]) {
                case '{':
                    strcpy(type, "{");
                    break;
                case '}':
                    strcpy(type, "}");
                    break;
                case '(':
                    strcpy(type, "(");
                    break;
                case ')':
                    strcpy(type, ")");
                    break;
                case '[':
                    strcpy(type, "[");
                    break;
                case ']':
                    strcpy(type, "]");
                    break;
                default:
                    break;
            }
            writeOutput(buffer, type, 0, fp_output);
            continue;
        }
    }
    fclose(fp_input);
    fclose(fp_output);
    return 0;
}


// End of Function