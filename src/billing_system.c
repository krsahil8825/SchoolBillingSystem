#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Structure
typedef struct {
    char name[50];
    int id; // Roll number for students or Employee ID for staff
    char role[20]; // Class for students or Position for staff
    float amount; // Fees for students or Salary for staff
} Record;

// Function Prototypes
void addRecord();
void displayRecords();
void searchRecord();
void modifyRecord();
void deleteRecord();
void saveToFile();
void loadFromFile();

// Global Variables
#define MAX_RECORDS 100
Record records[MAX_RECORDS];
int recordCount = 0;

// Main Function
int main() {
    int choice;

    // Load data from the file into memory
    loadFromFile();

    do {
        printf("\n====== School Billing System ======\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Search Record\n");
        printf("4. Modify Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchRecord();
                break;
            case 4:
                modifyRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    // Save data to the file before exiting
    saveToFile();

    return 0;
}

// Load Records from File
void loadFromFile() {
    FILE *file = fopen("records.txt", "r");
    if (!file) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%[^,],%d,%[^,],%f\n", records[recordCount].name, &records[recordCount].id,
                  records[recordCount].role, &records[recordCount].amount) != EOF) {
        recordCount++;
    }

    fclose(file);
}

// Save Records to File
void saveToFile() {
    FILE *file = fopen("records.txt", "w");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%s,%d,%s,%.2f\n", records[i].name, records[i].id, records[i].role, records[i].amount);
    }

    fclose(file);
}

// Add Record
void addRecord() {
    if (recordCount >= MAX_RECORDS) {
        printf("Cannot add more records. Storage is full.\n");
        return;
    }

    Record newRecord;
    printf("Enter Name: ");
    scanf(" %[^\n]", newRecord.name);
    printf("Enter ID (Roll No/Emp ID): ");
    scanf("%d", &newRecord.id);
    printf("Enter Role (Class/Position): ");
    scanf(" %[^\n]", newRecord.role);
    printf("Enter Amount (Fees/Salary): ");
    scanf("%f", &newRecord.amount);

    records[recordCount++] = newRecord;
    printf("Record added successfully.\n");
}

// Display Records
void displayRecords() {
    if (recordCount == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-20s %-10s %-20s %-10s\n", "Name", "ID", "Role", "Amount");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < recordCount; i++) {
        printf("%-20s %-10d %-20s %-10.2f\n", records[i].name, records[i].id, records[i].role, records[i].amount);
    }
}

// Search Record
void searchRecord() {
    if (recordCount == 0) {
        printf("No records found.\n");
        return;
    }

    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == id) {
            printf("\nRecord Found:\n");
            printf("Name: %s\nID: %d\nRole: %s\nAmount: %.2f\n", records[i].name, records[i].id, records[i].role, records[i].amount);
            return;
        }
    }

    printf("Record not found.\n");
}

// Modify Record
void modifyRecord() {
    if (recordCount == 0) {
        printf("No records found.\n");
        return;
    }

    int id;
    printf("Enter ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == id) {
            printf("Enter new details:\n");
            printf("Enter Name: ");
            scanf(" %[^\n]", records[i].name);
            printf("Enter Role (Class/Position): ");
            scanf(" %[^\n]", records[i].role);
            printf("Enter Amount (Fees/Salary): ");
            scanf("%f", &records[i].amount);
            printf("Record modified successfully.\n");
            return;
        }
    }

    printf("Record not found.\n");
}

// Delete Record
void deleteRecord() {
    if (recordCount == 0) {
        printf("No records found.\n");
        return;
    }

    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < recordCount; i++) {
        if (records[i].id == id) {
            for (int j = i; j < recordCount - 1; j++) {
                records[j] = records[j + 1];
            }
            recordCount--;
            printf("Record deleted successfully.\n");
            return;
        }
    }

    printf("Record not found.\n");
}
