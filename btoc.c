#include <stdio.h>

const char *head = "#include <stdio.h>\n"
                   "static char array[30000]={0};"
                   "static char *p=array;"
                   "char inp;"
                   "int main(void){";

int unmatched (char c, char *prog)
{
    fprintf(stderr, "\nError: unmatched '%c' in %s\n", c, prog);
    return 1;
}

int main (int argc, char *argv[])
{
    const char *m;
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
    printf(head);

    while((c = fgetc(fp)) != EOF) {
        switch (c) {
            case '.':
                m = "putchar(*p);";
            break;
            case ',':
                m = "inp=getchar();if(inp>0)*p=inp;";
            break;
            case '[':
                m = "while(*p){";
                ++depth;
            break;
            case ']':
                if (depth == 0)
                    return unmatched(']', argv[1]);

                m = "}";
                --depth;
            break;
            case '>':
                m = "++p;";
            break;
            case '<':
                m = "--p;";
            break;
            case '+':
                m = "++*p;";
            break;
            case '-':
                m = "--*p;";
            break;
            default:
                continue;
        }

        printf(m);
    }

    fclose(fp);
    if (depth != 0)
        return unmatched('[', argv[1]);

    printf("return 0;}\n");
    return 0;
}
