#include <stdio.h>

int main()
{
    int A, B, C, temp;

    scanf("%d %d %d", &A, &B, &C);

    // Check if it is a valid triangle
    if (A + B > C && A + C > B && B + C > A)
    {
        // Check triangle type
        if (A == B && B == C)
        {
            printf("Valido-Equilatero\n");
        }
        else if (A != B && B != C && A != C)
        {
            printf("Valido-Escaleno\n");
        }
        else
        {
            printf("Valido-Isoceles\n");
        }

        // Sort the sides so that A is the largest
        if (A < B)
        {
            temp = A;
            A = B;
            B = temp;
        }

        if (A < C)
        {
            temp = A;
            A = C;
            C = temp;
        }

        if (B < C)
        {
            temp = B;
            B = C;
            C = temp;
        }

        // Check if it is a right triangle
        if (A * A == B * B + C * C)
        {
            printf("Retangulo: S\n");
        }
        else
        {
            printf("Retangulo: N\n");
        }
    }
    else
    {
        printf("Invalido\n");
    }

    return 0;
}