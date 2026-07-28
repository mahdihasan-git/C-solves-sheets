/*
    SCIENTIFIC CALCULATOR (Console Version)
    Varsity Project - written in C

    How it works:
    - The menu shows 15 numbered operations.
    - You type the number of the operation you want.
    - The program asks for the value(s) it needs.
    - It prints the Expression and the Result, just like a display.
    - Option 15 (Exit) closes the program.

    This version reads input one line at a time and checks that it
    is really a valid number, so a typo can never freeze the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

/* Reads one whole number from the user. Keeps asking until valid. */
int readInt(const char *prompt) {
    char line[100];
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            /* No more input available; exit the program safely. */
            printf("\nNo more input. Exiting.\n");
            exit(0);
        }
        if (sscanf(line, "%d", &value) == 1) {
            return value;
        }
        printf("That is not a valid whole number. Please try again.\n");
    }
}

/* Reads one decimal number from the user. Keeps asking until valid. */
double readDouble(const char *prompt) {
    char line[100];
    double value;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nNo more input. Exiting.\n");
            exit(0);
        }
        if (sscanf(line, "%lf", &value) == 1) {
            return value;
        }
        printf("That is not a valid number. Please try again.\n");
    }
}

void printMenu() {
    printf("\n");
    printf("#############################################################\n");
    printf("                     SCIENTIFIC CALCULATOR                   \n");
    printf("#############################################################\n");
    printf("+----------+----------+-----------+\n");
    printf("| 1.Add    | 2.Sub    | 3.Mul     |\n");
    printf("+----------+----------+-----------+\n");
    printf("| 4.Div    | 5.Power  | 6.Sqrt    |\n");
    printf("+----------+----------+-----------+\n");
    printf("| 7.Sin    | 8.Cos    | 9.Tan     |\n");
    printf("+----------+----------+-----------+\n");
    printf("|10.Cot    |11.Sec    |12.Cosec   |\n");
    printf("+----------+----------+-----------+\n");
    printf("|13.Log    |14.Ln     |15.Exit    |\n");
    printf("+----------+----------+-----------+\n");
}

/* Converts degrees to radians, since C's math functions use radians */
double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

/* Asks the user whether their angle is in degrees or radians,
   and returns the angle already converted to radians for use in math.h */
double getAngleInRadians(double rawValue, char *unitLabelOut) {
    int unitChoice;

    printf("Is the angle in Degrees or Radians?\n");
    printf("  1. Degrees\n");
    printf("  2. Radians\n");
    unitChoice = readInt("Enter choice: ");

    if (unitChoice == 1) {
        strcpy(unitLabelOut, "deg");
        return toRadians(rawValue);
    } else {
        strcpy(unitLabelOut, "rad");
        return rawValue;
    }
}

int main() {
    int choice;
    double a, b, result;
    char unitLabel[4];
    double angle;

    while (1) {
        printMenu();
        choice = readInt("Enter your choice (1-15): ");

        if (choice == 15) {
            printf("\nExiting... Thank you for using Scientific Calculator.\n");
            break;
        }

        printf("\n--------------------------------------------\n");

        switch (choice) {

            case 1: /* Add */
                a = readDouble("Enter value A: ");
                b = readDouble("Enter value B: ");
                result = a + b;
                printf("Expression : %.4f + %.4f\n", a, b);
                printf("Result     : %.4f\n", result);
                break;

            case 2: /* Sub */
                a = readDouble("Enter value A: ");
                b = readDouble("Enter value B: ");
                result = a - b;
                printf("Expression : %.4f - %.4f\n", a, b);
                printf("Result     : %.4f\n", result);
                break;

            case 3: /* Mul */
                a = readDouble("Enter value A: ");
                b = readDouble("Enter value B: ");
                result = a * b;
                printf("Expression : %.4f * %.4f\n", a, b);
                printf("Result     : %.4f\n", result);
                break;

            case 4: /* Div */
                a = readDouble("Enter value A: ");
                b = readDouble("Enter value B: ");
                if (b == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    result = a / b;
                    printf("Expression : %.4f / %.4f\n", a, b);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 5: /* Power */
                a = readDouble("Enter base value A: ");
                b = readDouble("Enter power value B: ");
                result = pow(a, b);
                printf("Expression : %.4f ^ %.4f\n", a, b);
                printf("Result     : %.4f\n", result);
                break;

            case 6: /* Sqrt */
                a = readDouble("Enter value: ");
                if (a < 0) {
                    printf("Error: Cannot find square root of a negative number.\n");
                } else {
                    result = sqrt(a);
                    printf("Expression : sqrt(%.4f)\n", a);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 7: /* Sin */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                result = sin(angle);
                printf("Expression : sin(%.4f %s)\n", a, unitLabel);
                printf("Result     : %.4f\n", result);
                break;

            case 8: /* Cos */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                result = cos(angle);
                printf("Expression : cos(%.4f %s)\n", a, unitLabel);
                printf("Result     : %.4f\n", result);
                break;

            case 9: /* Tan */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                if (fabs(cos(angle)) < 1e-10) {
                    printf("Error: tan is undefined at this angle.\n");
                } else {
                    result = tan(angle);
                    printf("Expression : tan(%.4f %s)\n", a, unitLabel);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 10: /* Cot */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                if (fabs(sin(angle)) < 1e-10) {
                    printf("Error: cot is undefined at this angle.\n");
                } else {
                    result = cos(angle) / sin(angle);
                    printf("Expression : cot(%.4f %s)\n", a, unitLabel);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 11: /* Sec */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                if (fabs(cos(angle)) < 1e-10) {
                    printf("Error: sec is undefined at this angle.\n");
                } else {
                    result = 1.0 / cos(angle);
                    printf("Expression : sec(%.4f %s)\n", a, unitLabel);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 12: /* Cosec */
                a = readDouble("Enter angle value: ");
                angle = getAngleInRadians(a, unitLabel);
                if (fabs(sin(angle)) < 1e-10) {
                    printf("Error: cosec is undefined at this angle.\n");
                } else {
                    result = 1.0 / sin(angle);
                    printf("Expression : cosec(%.4f %s)\n", a, unitLabel);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 13: /* Log base 10 */
                a = readDouble("Enter value: ");
                if (a <= 0) {
                    printf("Error: log is only defined for values greater than 0.\n");
                } else {
                    result = log10(a);
                    printf("Expression : log10(%.4f)\n", a);
                    printf("Result     : %.4f\n", result);
                }
                break;

            case 14: /* Ln (natural log) */
                a = readDouble("Enter value: ");
                if (a <= 0) {
                    printf("Error: ln is only defined for values greater than 0.\n");
                } else {
                    result = log(a);
                    printf("Expression : ln(%.4f)\n", a);
                    printf("Result     : %.4f\n", result);
                }
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 15.\n");
                break;
        }

        printf("--------------------------------------------\n");
    }

    return 0;
}