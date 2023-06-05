%{
#include <stdio.h>
#include <string.h>

#define MAX_IDENTIFIERS 1000

int id_count = 0; // Counter for identifiers
char identifiers[MAX_IDENTIFIERS][256]; // Array to store identifiers
int keyword_count = 0; // Counter for keywords
int operator_count = 0; // Counter for operators
int parenthesis_count = 0; // Counter for parentheses
int end_statement_count = 0; // Counter for end statements

FILE* output_file; // Output file pointer

void print_token(const char* token_name, const char* token_type) {
    fprintf(output_file, "%s\t<%s>\n", token_name, token_type);

    if (strcmp(token_type, "id") == 0) {
        // Check if the identifier has already been counted
        for (int i = 0; i < id_count; i++) {
            if (strcmp(identifiers[i], token_name) == 0) {
                return;
            }
        }

        // If the identifier has not been counted, add it to the array and increment the counter
        strcpy(identifiers[id_count], token_name);
        id_count++;
    }
    else if (strcmp(token_type, "keyword") == 0) {
        keyword_count++;
    }
    else if (strcmp(token_type, "operator") == 0) {
        operator_count++;
    }
    else if (strcmp(token_type, "parenthesis") == 0) {
        parenthesis_count++;
    }
    else if (strcmp(token_type, "end_statement") == 0) {
        end_statement_count++;
    }
}
%}

%%
@([a-zA-Z])([a-zA-Z0-9])*  { print_token(yytext, "id"); }
switch|if|auto|int|struct|char|else|goto|default|while  { print_token(yytext, "keyword"); }
\+|\-|\*|\/|\%|\=|\!\=|\>|\>|\<|\=\<|\=\>  { print_token(yytext, "operator"); }
\(|\)|\[|\]|\{|\}  { print_token(yytext, "parenthesis"); }
\#  { print_token("#", "end_statement"); }
.  { }
%%

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the output file
    output_file = fopen("output_file.txt", "w");
    if(output_file == NULL) {
        printf("Error: Failed to open output file\n");
        return 1;
    }

    // Set the input file
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        printf("Error: Failed to open input file\n");
        fclose(output_file);
        return 1;
    }

    // Run the lexer
    yylex();

    // Print the counts
    printf("Identifiers: %d\n", id_count);
    printf("Keywords: %d\n", keyword_count);
    printf("Operators: %d\n", operator_count);
    printf("Parentheses: %d\n", parenthesis_count);
    printf("End statements: %d\n", end_statement_count);

    // Close the files
    fclose(yyin);
    fclose(output_file);

    return 0;
}
