#include<stdio.h>
int main()
{
    int A, B, C;
    int temp;
    int X, Y, Z;
    scanf("%d %d %d",&A , &B, &C);

    X=A;
    Y=B;
    Z=C;


    if (A>B)
    {
        temp=A;
        A=B;
    }
    if (B>C)
    {
        temp=B;
        B=C;
    }
    if (A>C)
    {
        temp=A;
        A=C;
    }
    printf("%d\n %d\n %d\n",A,B,C);

    printf("\n");

    printf("%d\n %d\n %d\n",X,Y,Z);
    
     
    return 0;

}