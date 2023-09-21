#include <stdio.h>

int main() {

    char* temp1 = "222";
    printf("%d\n", sizeof(temp1));

    int x = 5;
    int* st = &x;
    printf("%d\n", sizeof(st));

    char temp2[2] = {2,3};
    printf("%d\n", sizeof(temp2));
    return 0;
}