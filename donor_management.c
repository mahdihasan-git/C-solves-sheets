/* ============================================================
   BLOOD DONOR MANAGEMENT SYSTEM
   Course   : Programming and Problem Solving Lab (CSE113)
   Language : Standard C (C89/C99 compatible)
   Purpose  : Menu-driven console application to manage blood
              donor records using structures, arrays, strings,
              loops, conditionals and file handling.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------------- Constants ---------------- */
#define MAX_DONORS      100      /* Maximum donors the array can hold   */
#define NAME_LEN        50
#define GENDER_LEN      10
#define BLOOD_LEN       5
#define PHONE_LEN       20
#define ADDRESS_LEN     100
#define DATE_LEN        15
#define FILE_NAME       "donors.dat"

/* ---------------- Structure ---------------- */
struct Donor {
    int  id;
    char name[NAME_LEN];
    int  age;
    char gender[GENDER_LEN];
    char bloodGroup[BLOOD_LEN];
    char phone[PHONE_LEN];
    char address[ADDRESS_LEN];
    char lastDonationDate[DATE_LEN];
    int  available;             /* 1 = available to donate, 0 = not available */
};

/* ---------------- Function Prototypes ---------------- */
void   showMenu(void);
void   clearInputBuffer(void);
int    getMenuChoice(void);

void   loadDonors(struct Donor donors[], int *count);
void   saveAllDonors(const struct Donor donors[], int count);

void   registerDonor(struct Donor donors[], int *count);
void   displayDonors(const struct Donor donors[], int count);
void   searchDonor(const struct Donor donors[], int count);
void   searchByBloodGroup(const struct Donor donors[], int count);
void   updateDonor(struct Donor donors[], int count);
void   deleteDonor(struct Donor donors[], int *count);
void   bloodGroupStatistics(const struct Donor donors[], int count);
void   findEligibleDonors(const struct Donor donors[], int count);

int    donorIdExists(const struct Donor donors[], int count, int id);
int    findDonorIndexById(const struct Donor donors[], int count, int id);

int    readValidatedInt(const char *prompt, int min, int max);
void   readValidatedString(const char *prompt, char *buffer, int maxLen);
int    isValidBloodGroup(const char *bg);
void   toUpperString(char *s);
void   printDonorHeader(void);
void   printDonorRow(const struct Donor *d);

/* Blood groups recognised by the system */
const char *VALID_BLOOD_GROUPS[] = {
    "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
};
#define NUM_BLOOD_GROUPS 8

/* ============================================================
   MAIN FUNCTION
   ============================================================ */
int main(void) {
    struct Donor donors[MAX_DONORS];
    int donorCount = 0;
    int choice;

    loadDonors(donors, &donorCount);

    do {
        showMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1: registerDonor(donors, &donorCount);        break;
            case 2: displayDonors(donors, donorCount);         break;
            case 3: searchDonor(donors, donorCount);            break;
            case 4: searchByBloodGroup(donors, donorCount);     break;
            case 5: updateDonor(donors, donorCount);            break;
            case 6: deleteDonor(donors, &donorCount);           break;
            case 7: bloodGroupStatistics(donors, donorCount);   break;
            case 8: findEligibleDonors(donors, donorCount);     break;
            case 9:
                saveAllDonors(donors, donorCount);
                printf("\nAll records saved. Thank you for using the\n");
                printf("Blood Donor Management System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 9.\n");
        }

    } while (choice != 9);

    return 0;
}

/* ============================================================
   MENU AND INPUT HELPERS
   ============================================================ */
void showMenu(void) {
    printf("\n========================================\n");
    printf("      BLOOD DONOR MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf(" 1. Register New Donor\n");
    printf(" 2. Display All Donors\n");
    printf(" 3. Search Donor\n");
    printf(" 4. Search by Blood Group\n");
    printf(" 5. Update Donor Information\n");
    printf(" 6. Delete Donor Record\n");
    printf(" 7. Blood Group Statistics\n");
    printf(" 8. Find Eligible Donors\n");
    printf(" 9. Exit\n");
    printf("========================================\n");
}

/* Removes leftover characters (including newline) from stdin */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/* Reads the main menu choice safely, rejecting non-numeric input */
int getMenuChoice(void) {
    int choice;
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        return -1; /* forces "Invalid choice" message in main() */
    }
    clearInputBuffer();
    return choice;
}

/* Generic validated integer reader with a min/max range */
int readValidatedInt(const char *prompt, int min, int max) {
    int value;
    int valid = 0;

    do {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (value < min || value > max) {
            printf("Value must be between %d and %d.\n", min, max);
        } else {
            valid = 1;
        }
    } while (!valid);

    return value;
}

/* Reads a non-empty line of text into buffer, trimming the newline */
void readValidatedString(const char *prompt, char *buffer, int maxLen) {
    int valid = 0;

    do {
        printf("%s", prompt);
        if (fgets(buffer, maxLen, stdin) == NULL) {
            buffer[0] = '\0';
        }

        /* Strip trailing newline if present */
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("This field cannot be empty. Please try again.\n");
        } else {
            valid = 1;
        }
    } while (!valid);
}

/* Converts a string to uppercase in place (used for blood group input) */
void toUpperString(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char) toupper((unsigned char) s[i]);
    }
}

/* Checks whether a blood group string matches one of the 8 valid groups */
int isValidBloodGroup(const char *bg) {
    int i;
    for (i = 0; i < NUM_BLOOD_GROUPS; i++) {
        if (strcmp(bg, VALID_BLOOD_GROUPS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* ============================================================
   FILE HANDLING
   ============================================================ */

/* Loads all donor records from donors.dat into the array at startup */
void loadDonors(struct Donor donors[], int *count) {
    FILE *fp;
    struct Donor temp;
    int n = 0;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        /* No file yet — first run of the program. Not an error. */
        *count = 0;
        return;
    }

    while (fread(&temp, sizeof(struct Donor), 1, fp) == 1 && n < MAX_DONORS) {
        donors[n] = temp;
        n++;
    }

    fclose(fp);
    *count = n;

    printf("\n%d donor record(s) loaded from %s.\n", n, FILE_NAME);
}

/* Rewrites the entire donors.dat file from the current in-memory array.
   Called after every add/update/delete so the file always stays in sync. */
void saveAllDonors(const struct Donor donors[], int count) {
    FILE *fp;
    int i;

    fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("\nError: could not open %s for writing!\n", FILE_NAME);
        return;
    }

    for (i = 0; i < count; i++) {
        fwrite(&donors[i], sizeof(struct Donor), 1, fp);
    }

    fclose(fp);
}

/* ============================================================
   DUPLICATE / LOOKUP HELPERS
   ============================================================ */
int donorIdExists(const struct Donor donors[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (donors[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int findDonorIndexById(const struct Donor donors[], int count, int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (donors[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* ============================================================
   1. DONOR REGISTRATION
   ============================================================ */
void registerDonor(struct Donor donors[], int *count) {
    struct Donor newDonor;
    char genderInput[GENDER_LEN];
    char bloodInput[BLOOD_LEN];
    char availInput[GENDER_LEN];

    printf("\n---------- REGISTER NEW DONOR ----------\n");

    if (*count >= MAX_DONORS) {
        printf("Donor list is full! Cannot register more donors.\n");
        return;
    }

    /* Donor ID with duplicate check */
    do {
        newDonor.id = readValidatedInt("Enter Donor ID (positive number): ", 1, 999999);
        if (donorIdExists(donors, *count, newDonor.id)) {
            printf("Donor ID %d already exists! Please enter a unique ID.\n", newDonor.id);
        }
    } while (donorIdExists(donors, *count, newDonor.id));

    readValidatedString("Enter Name: ", newDonor.name, NAME_LEN);

    newDonor.age = readValidatedInt("Enter Age (18-65): ", 18, 65);

    do {
        readValidatedString("Enter Gender (Male/Female/Other): ", genderInput, GENDER_LEN);
    } while (strlen(genderInput) == 0);
    strcpy(newDonor.gender, genderInput);

    do {
        readValidatedString("Enter Blood Group (e.g. A+, O-, AB+): ", bloodInput, BLOOD_LEN);
        toUpperString(bloodInput);
        if (!isValidBloodGroup(bloodInput)) {
            printf("Invalid blood group! Valid options: A+ A- B+ B- AB+ AB- O+ O-\n");
        }
    } while (!isValidBloodGroup(bloodInput));
    strcpy(newDonor.bloodGroup, bloodInput);

    readValidatedString("Enter Phone Number: ", newDonor.phone, PHONE_LEN);
    readValidatedString("Enter Address: ", newDonor.address, ADDRESS_LEN);
    readValidatedString("Enter Last Donation Date (DD-MM-YYYY or 'N/A'): ",
                         newDonor.lastDonationDate, DATE_LEN);

    do {
        readValidatedString("Currently available to donate? (yes/no): ", availInput, GENDER_LEN);
        toUpperString(availInput);
    } while (strcmp(availInput, "YES") != 0 && strcmp(availInput, "NO") != 0);
    newDonor.available = (strcmp(availInput, "YES") == 0) ? 1 : 0;

    donors[*count] = newDonor;
    (*count)++;

    saveAllDonors(donors, *count);

    printf("\nDonor registered successfully! (Total donors: %d)\n", *count);
}

/* ============================================================
   2. DISPLAY ALL DONORS
   ============================================================ */
void printDonorHeader(void) {
    printf("\n%-6s %-18s %-4s %-8s %-6s %-14s %-12s %-10s\n",
           "ID", "Name", "Age", "Gender", "Blood", "Phone", "LastDonate", "Available");
    printf("--------------------------------------------------------------------------------------\n");
}

void printDonorRow(const struct Donor *d) {
    printf("%-6d %-18s %-4d %-8s %-6s %-14s %-12s %-10s\n",
           d->id, d->name, d->age, d->gender, d->bloodGroup,
           d->phone, d->lastDonationDate, d->available ? "Yes" : "No");
}

void displayDonors(const struct Donor donors[], int count) {
    int i;

    printf("\n---------- ALL REGISTERED DONORS ----------\n");

    if (count == 0) {
        printf("No donor records found.\n");
        return;
    }

    printDonorHeader();
    for (i = 0; i < count; i++) {
        printDonorRow(&donors[i]);
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("Total donors: %d\n", count);
}

/* ============================================================
   3. SEARCH DONOR (by ID, Name, or Blood Group)
   ============================================================ */
void searchDonor(const struct Donor donors[], int count) {
    int subChoice, id, i, found;
    char nameQuery[NAME_LEN];
    char bgQuery[BLOOD_LEN];

    if (count == 0) {
        printf("\nNo donor records found. Please register donors first.\n");
        return;
    }

    printf("\n---------- SEARCH DONOR ----------\n");
    printf("1. Search by Donor ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Blood Group\n");
    subChoice = readValidatedInt("Enter choice: ", 1, 3);

    found = 0;

    if (subChoice == 1) {
        id = readValidatedInt("Enter Donor ID: ", 1, 999999);
        i = findDonorIndexById(donors, count, id);
        if (i != -1) {
            printDonorHeader();
            printDonorRow(&donors[i]);
            found = 1;
        }
    } else if (subChoice == 2) {
        readValidatedString("Enter Name (or part of name): ", nameQuery, NAME_LEN);
        printDonorHeader();
        for (i = 0; i < count; i++) {
            if (strstr(donors[i].name, nameQuery) != NULL) {
                printDonorRow(&donors[i]);
                found = 1;
            }
        }
    } else if (subChoice == 3) {
        readValidatedString("Enter Blood Group: ", bgQuery, BLOOD_LEN);
        toUpperString(bgQuery);
        printDonorHeader();
        for (i = 0; i < count; i++) {
            if (strcmp(donors[i].bloodGroup, bgQuery) == 0) {
                printDonorRow(&donors[i]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching donor found.\n");
    }
}

/* ============================================================
   4. SEARCH BY BLOOD GROUP (dedicated menu option)
   ============================================================ */
void searchByBloodGroup(const struct Donor donors[], int count) {
    char bg[BLOOD_LEN];
    int i, found = 0;

    if (count == 0) {
        printf("\nNo donor records found. Please register donors first.\n");
        return;
    }

    printf("\n---------- SEARCH BY BLOOD GROUP ----------\n");
    do {
        readValidatedString("Enter Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ", bg, BLOOD_LEN);
        toUpperString(bg);
        if (!isValidBloodGroup(bg)) {
            printf("Invalid blood group entered!\n");
        }
    } while (!isValidBloodGroup(bg));

    printDonorHeader();
    for (i = 0; i < count; i++) {
        if (strcmp(donors[i].bloodGroup, bg) == 0) {
            printDonorRow(&donors[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No donors found with blood group %s.\n", bg);
    }
}

/* ============================================================
   5. UPDATE DONOR INFORMATION
   ============================================================ */
void updateDonor(struct Donor donors[], int count) {
    int id, index;
    int fieldChoice;
    char bloodInput[BLOOD_LEN];
    char availInput[GENDER_LEN];

    if (count == 0) {
        printf("\nNo donor records found. Please register donors first.\n");
        return;
    }

    printf("\n---------- UPDATE DONOR INFORMATION ----------\n");
    id = readValidatedInt("Enter Donor ID to update: ", 1, 999999);
    index = findDonorIndexById(donors, count, id);

    if (index == -1) {
        printf("Donor with ID %d not found.\n", id);
        return;
    }

    printf("\nCurrent Record:\n");
    printDonorHeader();
    printDonorRow(&donors[index]);

    printf("\nWhich field do you want to update?\n");
    printf("1. Name\n2. Age\n3. Gender\n4. Blood Group\n");
    printf("5. Phone\n6. Address\n7. Last Donation Date\n8. Availability\n9. Cancel\n");
    fieldChoice = readValidatedInt("Enter choice: ", 1, 9);

    switch (fieldChoice) {
        case 1:
            readValidatedString("Enter new Name: ", donors[index].name, NAME_LEN);
            break;
        case 2:
            donors[index].age = readValidatedInt("Enter new Age (18-65): ", 18, 65);
            break;
        case 3:
            readValidatedString("Enter new Gender: ", donors[index].gender, GENDER_LEN);
            break;
        case 4:
            do {
                readValidatedString("Enter new Blood Group: ", bloodInput, BLOOD_LEN);
                toUpperString(bloodInput);
                if (!isValidBloodGroup(bloodInput)) {
                    printf("Invalid blood group!\n");
                }
            } while (!isValidBloodGroup(bloodInput));
            strcpy(donors[index].bloodGroup, bloodInput);
            break;
        case 5:
            readValidatedString("Enter new Phone Number: ", donors[index].phone, PHONE_LEN);
            break;
        case 6:
            readValidatedString("Enter new Address: ", donors[index].address, ADDRESS_LEN);
            break;
        case 7:
            readValidatedString("Enter new Last Donation Date: ", donors[index].lastDonationDate, DATE_LEN);
            break;
        case 8:
            do {
                readValidatedString("Available to donate now? (yes/no): ", availInput, GENDER_LEN);
                toUpperString(availInput);
            } while (strcmp(availInput, "YES") != 0 && strcmp(availInput, "NO") != 0);
            donors[index].available = (strcmp(availInput, "YES") == 0) ? 1 : 0;
            break;
        case 9:
            printf("Update cancelled.\n");
            return;
    }

    saveAllDonors(donors, count);
    printf("\nDonor record updated successfully!\n");
    printDonorHeader();
    printDonorRow(&donors[index]);
}

/* ============================================================
   6. DELETE DONOR RECORD
   ============================================================ */
void deleteDonor(struct Donor donors[], int *count) {
    int id, index, i;
    char confirm[GENDER_LEN];

    if (*count == 0) {
        printf("\nNo donor records found. Please register donors first.\n");
        return;
    }

    printf("\n---------- DELETE DONOR RECORD ----------\n");
    id = readValidatedInt("Enter Donor ID to delete: ", 1, 999999);
    index = findDonorIndexById(donors, *count, id);

    if (index == -1) {
        printf("Donor with ID %d not found.\n", id);
        return;
    }

    printf("\nRecord to be deleted:\n");
    printDonorHeader();
    printDonorRow(&donors[index]);

    readValidatedString("Are you sure you want to delete this record? (yes/no): ", confirm, GENDER_LEN);
    toUpperString(confirm);

    if (strcmp(confirm, "YES") != 0) {
        printf("Deletion cancelled.\n");
        return;
    }

    /* Shift all subsequent records one position to the left */
    for (i = index; i < (*count) - 1; i++) {
        donors[i] = donors[i + 1];
    }
    (*count)--;

    saveAllDonors(donors, *count);
    printf("Donor record deleted successfully! (Total donors: %d)\n", *count);
}

/* ============================================================
   7. BLOOD GROUP STATISTICS
   ============================================================ */
void bloodGroupStatistics(const struct Donor donors[], int count) {
    int stats[NUM_BLOOD_GROUPS];
    int i, j;

    printf("\n---------- BLOOD GROUP STATISTICS ----------\n");

    if (count == 0) {
        printf("No donor records found.\n");
        return;
    }

    for (i = 0; i < NUM_BLOOD_GROUPS; i++) {
        stats[i] = 0;
    }

    for (i = 0; i < count; i++) {
        for (j = 0; j < NUM_BLOOD_GROUPS; j++) {
            if (strcmp(donors[i].bloodGroup, VALID_BLOOD_GROUPS[j]) == 0) {
                stats[j]++;
                break;
            }
        }
    }

    for (i = 0; i < NUM_BLOOD_GROUPS; i++) {
        printf("%-4s : %d donor(s)\n", VALID_BLOOD_GROUPS[i], stats[i]);
    }
    printf("--------------------------------\n");
    printf("Total : %d donor(s)\n", count);
}

/* ============================================================
   8. FIND ELIGIBLE DONORS
   Eligibility rule (kept simple for a lab project):
     - Blood group matches the requested group
     - Age is greater than or equal to the minimum age given
     - Donor is marked as currently available
   ============================================================ */
void findEligibleDonors(const struct Donor donors[], int count) {
    char bg[BLOOD_LEN];
    int minAge, i, found = 0;

    if (count == 0) {
        printf("\nNo donor records found. Please register donors first.\n");
        return;
    }

    printf("\n---------- FIND ELIGIBLE DONORS ----------\n");

    do {
        readValidatedString("Enter Required Blood Group: ", bg, BLOOD_LEN);
        toUpperString(bg);
        if (!isValidBloodGroup(bg)) {
            printf("Invalid blood group!\n");
        }
    } while (!isValidBloodGroup(bg));

    minAge = readValidatedInt("Enter Minimum Age: ", 18, 65);

    printf("\nEligible Donors (Blood Group: %s, Age >= %d, Available: Yes)\n", bg, minAge);
    printDonorHeader();

    for (i = 0; i < count; i++) {
        if (strcmp(donors[i].bloodGroup, bg) == 0 &&
            donors[i].age >= minAge &&
            donors[i].available == 1) {
            printDonorRow(&donors[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No eligible donors found matching the criteria.\n");
    }
}
