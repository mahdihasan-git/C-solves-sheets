#include <stdio.h>

int main()
{
    double N;
    int taka, coin;

    scanf("%lf", &N);

    taka = (int)N;
    coin = (N - taka) * 100 + 0.5;

    printf("NOTAS:\n");

    printf("%d nota(s) de R$ 100.00\n", taka / 100);
    taka = taka % 100;

    printf("%d nota(s) de R$ 50.00\n", taka / 50);
    taka = taka % 50;

    printf("%d nota(s) de R$ 20.00\n", taka / 20);
    taka = taka % 20;

    printf("%d nota(s) de R$ 10.00\n", taka / 10);
    taka = taka % 10;

    printf("%d nota(s) de R$ 5.00\n", taka / 5);
    taka = taka % 5;

    printf("%d nota(s) de R$ 2.00\n", taka / 2);
    taka = taka % 2;

    printf("MOEDAS:\n");

    printf("%d moeda(s) de R$ 1.00\n", taka);
    printf("%d moeda(s) de R$ 0.50\n", coin / 50);
    coin = coin % 50;

    printf("%d moeda(s) de R$ 0.25\n", coin / 25);
    coin = coin % 25;

    printf("%d moeda(s) de R$ 0.10\n", coin / 10);
    coin = coin % 10;

    printf("%d moeda(s) de R$ 0.05\n", coin / 5);
    coin = coin % 5;

    printf("%d moeda(s) de R$ 0.01\n", coin);

    return 0;
}
