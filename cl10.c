#include<stdio.h>
int main(){
    long long int n;
    scanf("%lld",&n);
    long long int sum=0;
    long long int lastDigite =0;
    long long int slastDigite =0;

        for(int i=1;i<=n;i++){

            slastDigite = lastDigite;
            lastDigite = lastDigite +i;
                sum = lastDigite + slastDigite;

                printf("%lld\n",sum);
        }
    return 0;
}