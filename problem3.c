#include<stdio.h>
int main(){
    int N,X;
     scanf("%d%d",&N,&X);
    int arr[N];
    int counte=0;
     for(int i=1;i<=N;i++){
         scanf("%d",&arr[i]);
            if(arr[i]%X==0){
               counte=i;
            }
     }
     
     if(counte==N-2){
        printf("Yeee! Argentina\n");
     }
     else{ printf("Messi missed the penalty!\n");}
     
    return 0;
}