#include <stdio.h>

// ONLY REQUIRED ON WINDOWS SYSTEM
#include <io.h>
#include <fcntl.h>

int main() {

    
    FILE* fp;
    int ch;
    

    fp = fopen("./test_playground.txt", "r");

    // Setting mode to binary for this file stream, ONLY ON WINDOWS
    _setmode(_fileno(fp), _O_BINARY); 


    if (fp == NULL) {

        perror("Error occurred!");
        return 1;
    }

    printf("start\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\r') {
            printf("Found it!");
            printf("%d", ftell(fp));
        }
    }

    if (ferror(fp)) {
        perror("Error reading from file");
        fclose(fp);
        return 2;
    }
    
    fclose(fp);
    return 0;
}