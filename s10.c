 #include <stdio.h>

int main()
{
    int a, b, c, d;

   
    while (scanf("%d.%d.%d-%d", &a, &b, &c, &d) == 4) {
       
        printf("%03d\n", a);
        printf("%03d\n", b);
        printf("%03d\n", c);
        printf("%d\n", d);
    }

    return 0;
}