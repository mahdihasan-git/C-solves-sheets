#include<stdio.h>
int main(){
    long long int A;
    scanf("%lld",&A);

    for (int i=1; i<=A; i++) 
    {  
        if(A%i==0)
        { printf("%lld\n",i);
    }
        
    }
}