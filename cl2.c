#include <stdio.h>

int main()
{
    long long int a;
    scanf("%lld", &a);

    for(long long int i = 2; i <= a; i += 2)
    {
        printf("%lld\n", i);
    }

    return 0;
}