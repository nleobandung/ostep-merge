#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    FILE* input;
    FILE* output;
    struct stat input_stat, output_stat;

    if (argc <= 1) {
        input = stdin;
        output = stdout;
    } else {
        if (argc > 3) {
            fprintf(stderr, "usage: reverse <input> <output>\n");
            exit(1);
        }
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        if (stat(argv[1], &input_stat) != 0) {
            fprintf(stderr, "reverse: cannot open stat file '%s'\n", argv[1]);
            fclose(input);
            exit(1);
        }
        if (argc == 2) {
            output = stdout;
        } else if (argc == 3) {
            if (stat(argv[2], &output_stat) == 0) {
                if (input_stat.st_dev == output_stat.st_dev &&
                    input_stat.st_ino == output_stat.st_ino) {
                    fprintf(stderr, "reverse: input and output file must differ\n");
                    fclose(input);
                    exit(1);
                }
            }
            output = fopen(argv[2], "w");
            if (output == NULL) {
                fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
                if (input != stdin) {
                    fclose(input);
                }
                exit(1);
            }
        } 
    }

    size_t max_size = 10;
    size_t curr_size = 0;
    char** lines = malloc(max_size * sizeof(char*));
    if (lines == NULL) {
        fprintf(stderr, "malloc failed\n");
        if (input != stdin) {
            fclose(input);
        }
        if (output != stdout) {
            fclose(output);
        }
        exit(1);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, input);
    while (read != -1) {
        if (curr_size == max_size) {
            max_size *= 2;
            lines = realloc(lines, max_size * sizeof(char*));
            if (lines == NULL) {
                fprintf(stderr, "malloc faile\n");
                if (input != stdin) {
                    fclose(input);
                }
                if (output != stdout) {
                    fclose(output);
                }
                exit(1);
            }
        }

        lines[curr_size] = strdup(line);
        if (lines[curr_size] == NULL) {
            fprintf(stderr, "strdup failed\n");
            if (input != stdin) {
                fclose(input);
            }
            if (output != stdout) {
                fclose(output);
            }
            exit(1);
        }
        curr_size++;
        read = getline(&line, &len, input);
    }
    free(line);
    
    for (size_t i = curr_size; i > 0; i--) {
        fprintf(output, "%s", lines[i - 1]);
        free(lines[i - 1]);
    }

    free(lines);
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}