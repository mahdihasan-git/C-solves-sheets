#include<stdio.h>
int main(){
    int a;
    scanf("%d",&a);

    for(int i=1; a>=0; i++)
    {
        a-=3;
        printf("%d\n",a);
        
    }
    return 0;
    
}