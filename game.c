#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int lane = 2;

void drawCar(int lane)
{
    if (lane == 1)
    {
        printf("|  /^^\\   |         |         |\n");
        printf("| |[][]|  |         |         |\n");
        printf("| |[][]|  |         |         |\n");
        printf("| |____|  |         |         |\n");
        printf("|  O  O   |         |         |\n");
    }
    else if (lane == 2)
    {
        printf("|         |  /^^\\   |         |\n");
        printf("|         | |[][]|  |         |\n");
        printf("|         | |[][]|  |         |\n");
        printf("|         | |____|  |         |\n");
        printf("|         |  O  O   |         |\n");
    }
    else
    {
        printf("|         |         |  /^^\\   |\n");
        printf("|         |         | |[][]|  |\n");
        printf("|         |         | |[][]|  |\n");
        printf("|         |         | |____|  |\n");
        printf("|         |         |  O  O   |\n");
    }
}

void drawRoad()
{
    system("cls");

    printf("=========================================\n");
    printf("          SIMPLE CAR GAME\n");
    printf("=========================================\n");
    printf("Press 1 = Left Lane\n");
    printf("Press 2 = Middle Lane\n");
    printf("Press 3 = Right Lane\n");
    printf("Press Q = Quit\n");
    printf("=========================================\n\n");

    printf("+---------------------------------------+\n");

    // Empty road
    for(int i = 0; i < 5; i++)
        printf("|         |         |         |\n");

    // Car
    drawCar(lane);

    // Empty road
    for(int i = 0; i < 3; i++)
        printf("|         |         |         |\n");

    printf("+---------------------------------------+\n");
}

int main()
{
    char ch;

    while(1)
    {
        drawRoad();

        ch = getch();

        if(ch == '1')
            lane = 1;
        else if(ch == '2')
            lane = 2;
        else if(ch == '3')
            lane = 3;
        else if(ch == 'q' || ch == 'Q')
            break;
    }

    system("cls");
    printf("\nThank you for playing!\n");

    return 0;
}