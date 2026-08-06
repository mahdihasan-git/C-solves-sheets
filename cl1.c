#include<stdio.h>
int main()
{
    int a;
    scanf("%d",&a);
    int count=0;
        
        for(int i=1; i<=a; i++){

         int b= a%i;

        if(b == 0){
            count++;
        }
    }
           if(a==1){
            printf("not prime or none prime\n");
           }
           else if(count==2){
                printf("Prime Number\n");
            }else{
                printf("NOT a Prime\n");
           }
     
    return 0;
}