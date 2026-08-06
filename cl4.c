#include <stdio.h>
int main()
{
    int a;
    scanf("%d",&a);
    int sum=0;
    int lastDigite = 0;

    while(a!=0){
        lastDigite = a%10;
        sum += lastDigite;
        a = a/10;
    }
    printf("%d\n", sum);
    return 0;
}