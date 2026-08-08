#include<stdio.h>
int main(){
    int x,y;
    scanf("%d %d",&x,&y);
    int a=x*y;
     if(a>=100){
        printf("Yes\n");
     }else{
        printf("No\n");
     }
    return 0;
}