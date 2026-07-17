#include <stdio.h>
int main()
{
    char L;
    scanf("%c", &L);

    //'C' - 'A' + 1 => 67 - 65 + 1 = 3
    printf("%d\n", L-'A'+1);

    return 0;
}