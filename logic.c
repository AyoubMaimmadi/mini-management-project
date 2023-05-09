#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char birthDate[11];
    char school[4];
    char major[50];
    int credits;
    float cgpa;
    char entrySemester[15];
} Student;

void showMenu() {
    printf("===== Menu =====\n");
    printf("1. Perform Action 1\n");
    printf("2. Perform Action 2\n");
    printf("3. Add Student\n");
    printf("================\n");
}

int isIdExists(int id, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentId = 0;
        sscanf(line, "%d,", &currentId);
        if (currentId == id) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

void addStudent(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Student student;
    printf("Enter student ID: ");
    scanf("%d", &student.id);

    if (isIdExists(student.id, filename)) {
        printf("A student with the same ID already exists.\n");
        fclose(file);
        return;
    }

    printf("Enter your full name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter student birth date (yyyy-mm-dd): "); // Modified prompt
    scanf(" %[^\n]", student.birthDate);

    printf("Enter student school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter student major: ");
    scanf(" %[^\n]", student.major);

    printf("Enter student credits (0-140): ");
    scanf("%d", &student.credits);

    printf("Enter student CGPA (0-4): ");
    scanf("%f", &student.cgpa);

    printf("Enter student entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student.entrySemester);

    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n", student.id, student.name, student.birthDate, student.school, student.major, student.credits, student.cgpa, student.entrySemester);

    fclose(file);
    printf("Student added successfully.\n");
}

void performAction(int choice, const char *filename) {
    switch (choice) {
        case 1:
            printf("Action 1 selected.\n");
            // Implement the code for action 1 here
            break;
        case 2:
            printf("Action 2 selected.\n");
            // Implement the code for action 2 here
            break;
        case 3:
            printf("Add a new student, if student ID already exists, try modifying.\n");
            addStudent(filename);
            break;
        default:
            printf("Invalid choice.\n");
    }
}

