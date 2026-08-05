#include<stdio.h>
int main(){
    int a;
    scanf("%d",&a);

    for(int i=a; i>=1; i++)
    {
        i-=3;
        if(i>=0){
        printf("%d\n",i);
        }
    }
}