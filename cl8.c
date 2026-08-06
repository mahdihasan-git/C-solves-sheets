#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int sum=1;
    for(int i=n; i>0;i--){
           sum=sum*i;
    }
 printf("%d",sum);
 return 0;

}