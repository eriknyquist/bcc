#include <stdio.h>

char prev;
unsigned int indentation;
unsigned int seq;

const char *head = "#include <stdio.h>\n\n"
                   "static char array[30000] = {0};\n"
                   "static char *p = array;\n\n"
                   "int main (void)\n{\n"
                   "char inp;\n";

void indent(void)
{
    int i;
    for (i = 0; i < indentation; ++i) printf(" ");
}

void indent_line (const char *code)
{
    indent();
    printf("%s\n", code);
}

void print_sequence (void)
{
    const char *snip;

    switch (prev) {
        case '>':
            snip = "p +";
        break;
        case '<':
            snip = "p -";
        break;
        case '+':
            snip = "*p +";
        break;
        case '-':
            snip = "*p -";
        break;
    }

    indent();
    printf("%s= %d;\n", snip, seq);
}
int main (int argc, char *argv[])
{
    unsigned int depth;
    FILE *fp;
    char c;

    if (argc == 2) {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            printf("Error: can't read file %s\n", argv[1]);
            return 1;
        }
    } else if (argc == 1) {
        fp = stdin;
    } else {
        printf("Usage: %s <brainfuck_source_file>\n", argv[0]);
        return 1;
    }

    depth = 0;
    seq = 0;
    indentation = 4;
    printf("%s\n", head);

    while((c = fgetc(fp)) != EOF) {
        if ((c == '>' || c == '<' || c == '+' || c == '-')) {
            if (seq > 0 && c != prev) {
                print_sequence();
                seq = 0;
            }

            ++seq;
        } else if (seq > 0) {
            print_sequence();
            seq = 0;
        }

        switch (c) {
            case '.':
                indent_line("putchar(*p);");
            break;
            case ',':
                indent_line("inp = getchar();");
                indent_line("if (inp > 0) *p = inp;");
            break;
            case '[':
                printf("\n");
                indent_line("while (*p) {");
                indentation += 4;
                ++depth;
            break;
            case ']':
                if (depth == 0) {
                    fprintf(stderr, "\nError: unmatched ']' in %s\n", argv[1]);
                    return 1;
                }

                indentation -= 4;
                indent_line("}\n");
                --depth;
            break;
        }

        prev = c;
    }

    if (depth != 0) {
        fprintf(stderr, "\nError: unmatched '[' in %s\n", argv[1]);
        return 1;
    }

    indent_line("return 0;\n}\n");
    fclose(fp);
    return 0;
}
