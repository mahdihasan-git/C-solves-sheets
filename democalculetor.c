#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

// reads a whole number, keeps asking till the user gives a real one
int readInt(const char *prompt) {
    char line[100];
    int value;

    while (1) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        if (sscanf(line, "%d", &value) == 1)
            return value;
        printf("That is not a valid whole number. Please try again.\n");
    }
}

// same idea but for decimal numbers
double readDouble(const char *prompt) {
    char line[100];
    double value;

    while (1) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        if (sscanf(line, "%lf", &value) == 1)
            return value;
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

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

// asks if the angle is degrees or radians and gives it back in radians
double getAngleInRadians(double rawValue, char *unitLabelOut) {
    int unitChoice;

    printf("Is the angle in Degrees or Radians?\n");
    printf("  1. Degrees\n");
    printf("  2. Radians\n");
    unitChoice = readInt("Enter choice: ");

    if (unitChoice == 1) {
        sprintf(unitLabelOut, "deg");
        return toRadians(rawValue);
    } else {
        sprintf(unitLabelOut, "rad");
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

        case 1: // add
            a = readDouble("Enter value A: ");
            b = readDouble("Enter value B: ");
            result = a + b;
            printf("Expression : %.4f + %.4f\n", a, b);
            printf("Result     : %.4f\n", result);
            break;

        case 2: // subtract
            a = readDouble("Enter value A: ");
            b = readDouble("Enter value B: ");
            result = a - b;
            printf("Expression : %.4f - %.4f\n", a, b);
            printf("Result     : %.4f\n", result);
            break;

        case 3: // multiply
            a = readDouble("Enter value A: ");
            b = readDouble("Enter value B: ");
            result = a * b;
            printf("Expression : %.4f * %.4f\n", a, b);
            printf("Result     : %.4f\n", result);
            break;

        case 4: // divide
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

        case 5: // power
            a = readDouble("Enter base value A: ");
            b = readDouble("Enter power value B: ");
            result = pow(a, b);
            printf("Expression : %.4f ^ %.4f\n", a, b);
            printf("Result     : %.4f\n", result);
            break;

        case 6: // square root
            a = readDouble("Enter value: ");
            if (a < 0) {
                printf("Error: Cannot find square root of a negative number.\n");
            } else {
                result = sqrt(a);
                printf("Expression : sqrt(%.4f)\n", a);
                printf("Result     : %.4f\n", result);
            }
            break;

        case 7: // sin
            a = readDouble("Enter angle value: ");
            angle = getAngleInRadians(a, unitLabel);
            result = sin(angle);
            printf("Expression : sin(%.4f %s)\n", a, unitLabel);
            printf("Result     : %.4f\n", result);
            break;

        case 8: // cos
            a = readDouble("Enter angle value: ");
            angle = getAngleInRadians(a, unitLabel);
            result = cos(angle);
            printf("Expression : cos(%.4f %s)\n", a, unitLabel);
            printf("Result     : %.4f\n", result);
            break;

        case 9: // tan
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

        case 10: // cot
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

        case 11: // sec
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

        case 12: // cosec
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

        case 13: // log base 10
            a = readDouble("Enter value: ");
            if (a <= 0) {
                printf("Error: log is only defined for values greater than 0.\n");
            } else {
                result = log10(a);
                printf("Expression : log10(%.4f)\n", a);
                printf("Result     : %.4f\n", result);
            }
            break;

        case 14: // natural log
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