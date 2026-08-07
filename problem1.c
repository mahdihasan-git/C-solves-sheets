#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int multiply =1;
    int x;
    for(int i=0; i<n;i++){
        x=n%10;
        multiply*=x;
        n=n/10;
    }
    printf("%d",multiply);
    return 0;

}