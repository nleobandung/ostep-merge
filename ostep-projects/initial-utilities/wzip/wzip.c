#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    int ch;
    int count = 0;
    int prev = EOF;
    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: can't open file\n");
            exit(1);
        }
        ch = fgetc(fp);
        while (ch != EOF) {
            if (ch == prev) {
                count++;
            } else {
                if (prev != EOF) {
                    fwrite(&count, sizeof(int), 1, stdout);
                    fwrite(&prev, sizeof(char), 1, stdout);
                }
                prev = ch;
                count = 1;
            }
            ch = fgetc(fp);
        }
        fclose(fp);
    }

    if (count > 0 && prev != EOF) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}