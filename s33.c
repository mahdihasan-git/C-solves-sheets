#include <stdio.h>
int main()
{
    float L,C;
    scanf("%f", &L);
    scanf("%f", &C);
    
    if (L+C%2==0)
    {
        printf("1\n");
    }
    else if ( L+C %2!=0)
    {
        printf("0\n");
    }
    
    return 0;
}