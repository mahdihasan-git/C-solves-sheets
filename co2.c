
#include <stdio.h>

int main()
{
    long long int A;
    scanf("%lld",&A);
    
    for (int i=0; i<=A; i++) 
    {  
        if(A%i==0)
        { printf("%lld\n",i);
    }
        
    }

    return 0;
}