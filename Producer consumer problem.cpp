#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

void addRecord(FILE *file) {
    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.empId);

    printf("Enter Employee Name: ");
    scanf("%s", emp.empName);

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);

    fseek(file, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);

    printf("Record added successfully!\n");
}

void displayAllRecords(FILE *file) {
    struct Employee emp;

    rewind(file);

    printf("\nEmployee Records:\n");
    printf("ID\tName\tSalary\n");

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("%d\t%s\t%.2f\n", emp.empId, emp.empName, emp.empSalary);
    }
}

void updateRecord(FILE *file) {
    struct Employee emp;
    int empId;

    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);

    if (fread(&emp, sizeof(struct Employee), 1, file) != 1) {
        printf("Employee not found!\n");
        return;
    }

    printf("Enter new Employee Name: ");
    scanf("%s", emp.empName);

    printf("Enter new Employee Salary: ");
    scanf("%f", &emp.empSalary);

    fseek(file, -sizeof(struct Employee), SEEK_CUR);
    fwrite(&emp, sizeof(struct Employee), 1, file);

    printf("Record updated successfully!\n");
}

void deleteRecord(FILE *file) {
    int empId;
    struct Employee emp;
    FILE *tempFile;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &empId);

    tempFile = fopen("temp.dat", "wb");

    rewind(file);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empId != empId) {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    printf("Record deleted successfully!\n");
}

int main() {
    FILE *file = fopen("employee.dat", "rb+");

    if (file == NULL) {
        file = fopen("employee.dat", "wb+");
    }

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    int choice;

    do {
        printf("\nEmployee Database\n");
        printf("1. Add Record\n");
        printf("2. Display All Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayAllRecords(file);
                break;
            case 3:
                updateRecord(file);
                break;
            case 4:
                deleteRecord(file);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    fclose(file);

    return 0;
}

