#include<stdio.h>
int main(){
    int N,X;
     scanf("%d%d",&N,&X);
    int arr[N];
    counte=0;
     for(int i=0;i<N;i++){
         scanf("%d%d",&arr[i]);
            if(arr[i]%X==0){
                counte++;
            }
     }
    return 0;
}