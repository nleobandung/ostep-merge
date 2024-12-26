#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    int count;
    int ch;
    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: can't open file\n");
            exit(1);
        }

        while (fread(&count, sizeof(int), 1, fp) && fread(&ch, sizeof(char), 1, fp)) {
            for (int j = 0; j < count; j++) {
                fwrite(&ch, sizeof(char), 1, stdout);
            }
        }

        fclose(fp);
    }

    return 0;
}