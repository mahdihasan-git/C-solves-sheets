#include <stdio.h>
int main(){

    int n,lastDigite;
    scanf("%d",&n);
        int sum =0;
            while(n!=0){
                lastDigite=n%10;
                if(lastDigite%2==0){
                    sum+=lastDigite;
                }      n=n/10;  
            }
    printf("%d\n",sum);
    return 0;
}