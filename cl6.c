#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int lastDigite=0;
    while(n!=0){
        lastDigite=n%10;
        printf("%d\n",lastDigite);
        n=n/10;
    }
   return 0;

}