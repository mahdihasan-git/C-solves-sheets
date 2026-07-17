#include<stdio.h>
int main()
{
    int N;
    int H,RS,M,S;
    scanf("%d",&N);

    H=N/3600;
    RS=N%3600;
    M=RS/60;
    S=RS%60;
    

    printf("%d:%d:%d",H,M,S);

    return 0;

}