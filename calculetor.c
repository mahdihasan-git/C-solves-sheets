#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main()
{
    int choice;
    double num1, num2, result;
    int i, n;
    long long fact;

    while (1)
    {
        printf("\n=====================================\n");
        printf("     SCIENTIFIC CALCULATOR\n");
        printf("=====================================\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Power (x^y)\n");
        printf("6. Square Root\n");
        printf("7. Square (x^2)\n");
        printf("8. Sine (sin)\n");
        printf("9. Cosine (cos)\n");
        printf("10. Tangent (tan)\n");
        printf("11. Log Base 10\n");
        printf("12. Natural Log (ln)\n");
        printf("13. Factorial\n");
        printf("0. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                printf("Result = %.2lf\n", num1 + num2);
                break;

            case 2:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                printf("Result = %.2lf\n", num1 - num2);
                break;

            case 3:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);
                printf("Result = %.2lf\n", num1 * num2);
                break;

            case 4:
                printf("Enter two numbers: ");
                scanf("%lf %lf", &num1, &num2);

                if(num2 == 0)
                    printf("Error! Division by zero is not possible.\n");
                else
                    printf("Result = %.2lf\n", num1 / num2);
                break;

            case 5:
                printf("Enter base and power: ");
                scanf("%lf %lf", &num1, &num2);
                result = pow(num1, num2);
                printf("Result = %.2lf\n", result);
                break;

            case 6:
                printf("Enter a number: ");
                scanf("%lf", &num1);

                if(num1 < 0)
                    printf("Square root of negative number is not possible.\n");
                else
                    printf("Result = %.2lf\n", sqrt(num1));
                break;

            case 7:
                printf("Enter a number: ");
                scanf("%lf", &num1);
                printf("Result = %.2lf\n", num1 * num1);
                break;

            case 8:
                printf("Enter angle (degrees): ");
                scanf("%lf", &num1);
                result = sin(num1 * PI / 180);
                printf("Result = %.6lf\n", result);
                break;

            case 9:
                printf("Enter angle (degrees): ");
                scanf("%lf", &num1);
                result = cos(num1 * PI / 180);
                printf("Result = %.6lf\n", result);
                break;

            case 10:
                printf("Enter angle (degrees): ");
                scanf("%lf", &num1);
                result = tan(num1 * PI / 180);
                printf("Result = %.6lf\n", result);
                break;

            case 11:
                printf("Enter a number: ");
                scanf("%lf", &num1);

                if(num1 <= 0)
                    printf("Log is not defined.\n");
                else
                    printf("Result = %.6lf\n", log10(num1));
                break;

            case 12:
                printf("Enter a number: ");
                scanf("%lf", &num1);

                if(num1 <= 0)
                    printf("Natural Log is not defined.\n");
                else
                    printf("Result = %.6lf\n", log(num1));
                break;

            case 13:
                printf("Enter a positive integer: ");
                scanf("%d", &n);

                if(n < 0)
                {
                    printf("Factorial is not possible.\n");
                }
                else
                {
                    fact = 1;
                    for(i = 1; i <= n; i++)
                    {
                        fact = fact * i;
                    }
                    printf("Result = %lld\n", fact);
                }
                break;

            case 0:
                printf("Thank you for using the calculator.\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}