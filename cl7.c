#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int sum=0;
    int lastDigite=0;

    while(n!=0){
        lastDigite=n%10;
        if(lastDigite%2==0){
            sum-=lastDigite;
        }
        else if(lastDigite%2!=0){
            sum+=lastDigite;
        }
        n=n/10;
    }
    printf("%d",sum);

    return 0;

}