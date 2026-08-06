#include <stdio.h>

int main() {
    char str[100] = "this is a simple string";
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            count++;
        }
        i++;
    }

    count = count + 1;

    printf("Number of words = %d\n", count);
    return 0;
}