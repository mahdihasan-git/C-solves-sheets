#include<stdio.h>
int main(){
    long long int b,g;
    scanf("%lld %lld",&b,&g);

    b*=8;

    g*=4;

    long long int n = b-g;
    printf("%lld\n",n/2);

    return 0;

}