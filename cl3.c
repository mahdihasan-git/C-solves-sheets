#include <stdio.h>
int main()
{
   int a;
   scanf("%d", &a);
   int counte = 0;

   while(a!=0){
   a= a/10;
    counte++;
   }
   printf("%d",counte);
   
   return 0;

}