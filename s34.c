#include<stdio.h>
int main()
{
    int a, b, c,d,e;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    }
    if (a<b && b<c && c<d && d<e)
    {
        printf("C\n");
    }
    else if (a>b && b>c && c>d && d>e)
    {
        printf("D\n");
    } else
    {
        printf("N\n");
    }
    

   
    return 0;
}