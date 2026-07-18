#include <stdio.h>

int main()
{
    char n[10][31];
    int i;

    for(i = 0; i < 10; i++)
    {
        scanf("%s", n[i]);
    }

    printf("%s\n", n[2]);
    printf("%s\n", n[6]);
    printf("%s\n", n[8]);

    return 0;
}