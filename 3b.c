#include <stdio.h>

void mahdi(char cha, int i)
{
    if(i==0){
        return;
    }
    if (cha == 'T')
    {
        if (i % 2 != 0)
        {
            printf("Tanvir eat\n");
        }
        else
        {
            printf("Musfiq eat\n");
        }
    }
    else
    {
        if (i % 2 != 0)
        {
            printf("Musfiq eat\n");
        }
        else
        {
            printf("Tanvir eat\n");
        }
    }
    
    mahdi(cha , i-1);
}

int main()
{
    int i = 5;
    char cha;

    scanf(" %c", &cha);

    mahdi(cha, i);
   
    return 0;
}
