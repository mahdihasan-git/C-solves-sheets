#include<stdio.h>
int main()
{
    long int N,T;
    int P,Q;
    char c;
    scanf("%ld ", &N);

    scanf("%d %c %d", &P, &c, &Q);

    if ( c == '+')
    {
        T = P + Q;
    }   
    else if ( c == '-')
    {
        T = P - Q;
    }
    else if ( c == '*')
    {
        T = P * Q;
    }
    else if ( c == '/')
    {
        T = P / Q;
    }
    else
    {
        printf("Invalid operator\n");
        return 1; // Exit with an error code
    }

    if (T == N)
    {
        printf("OK\n");
    }
    else if (T < N)
    {
        printf("OVERFLOW\n");
    }
    
    return 0;
}