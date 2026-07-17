#include <stdio.h>

int main()
{
    int A, B, C, temp;
    int x, y, z;

    scanf("%d %d %d", &A, &B, &C);

   
    x = A;
    y = B;
    z = C;

   
    if (A > B)
    {
        temp = A;
        A = B;
        B = temp;
    }

    if (A > C)
    {
        temp = A;
        A = C;
        C = temp;
    }

    if (B > C)
    {
        temp = B;
        B = C;
        C = temp;
    }

    printf("%d\n%d\n%d\n", A, B, C);

    
    printf("\n");

    
    printf("%d\n%d\n%d\n", x, y, z);

    return 0;
}