#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char* buffer = NULL;
    size_t bufsize = 0;
    if (argc == 2) {
        while (getline(&buffer, &bufsize, stdin) != EOF) {
            if (strstr(buffer, argv[1]) != NULL) {
                printf("%s", buffer);
            }
        }
    } else {
        for (int i = 2; i < argc; i++) {
            FILE* fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                free(buffer);
                exit(1);
            }

            while (getline(&buffer, &bufsize, fp) != EOF) {
                if (strstr(buffer, argv[1]) != NULL) {
                    printf("%s", buffer);
                }
            }
            fclose(fp);
        }
    }

    free(buffer);
    return 0;
}