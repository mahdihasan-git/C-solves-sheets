#include <stdio.h>

int main()
{
    int n, t;
    scanf("%d %d", &n, &t);

    int arr[n];

    int sum = 0;
    int count = 0;
    int found = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);

        if (arr[i] != -1)
        {
            sum += arr[i];
            count++;

            if (sum >= t)
            {
                found = 1;
                break;
            }
        }
    }

    if (found == 1)
    {
        printf("%d\n", count);
    }
    else
    {
        printf("Mission Failed\n");
    }

    return 0;
}