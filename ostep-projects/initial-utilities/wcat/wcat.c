#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    if (argc <= 1) {
        exit(0);
    }

    char buffer[100];
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        fclose(fp);
    }

    return 0;
}