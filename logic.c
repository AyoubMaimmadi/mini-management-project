#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
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
    printf("1. Add Student\n");
    printf("2. Modify Student Information\n");
    printf("3. Perform Action 3\n");
    printf("4. Log out\n"); 
    printf("================\n");
}

int studentExist(int id, const char *filename) {
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


//////////////////////////////////////// Add Student ////////////////////////////////////////
int addStudent(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    Student student;
    printf("Enter student ID: ");
    scanf("%d", &student.id);

    if (studentExist(student.id, filename)) {
        printf("A student with the same ID already exists.\n");
        fclose(file);
        return 0;
    }

    printf("Enter your full name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter student birth date (yyyy-mm-dd): ");
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
    return 1; // Return success status
}


////////////////////////////////////// Modify Student Information //////////////////////////////////////

int modifyStudent(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int studentId;
    printf("Enter student ID to modify: ");
    scanf("%d", &studentId);

    if (!studentExist(studentId, filename)) {
        printf("Student with ID %d does not exist.\n", studentId);
        fclose(file);
        return 0;
    }

    // Find the position of the student in the file
    long pos = -1;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentId = 0;
        sscanf(line, "%d,", &currentId);
        if (currentId == studentId) {
            pos = ftell(file) - strlen(line);
            break;
        }
    }

    if (pos == -1) {
        printf("Error finding student position in the file.\n");
        fclose(file);
        return 0;
    }

    Student student;
    printf("Enter modified full name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter modified birth date (yyyy-mm-dd): ");
    scanf(" %[^\n]", student.birthDate);

    printf("Enter modified school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter modified major: ");
    scanf(" %[^\n]", student.major);

    printf("Enter modified credits (0-140): ");
    scanf("%d", &student.credits);

    printf("Enter modified CGPA (0-4): ");
    scanf("%f", &student.cgpa);

    printf("Enter modified entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student.entrySemester);

    fseek(file, pos, SEEK_SET);
    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n", studentId, student.name, student.birthDate, student.school, student.major, student.credits, student.cgpa, student.entrySemester);

    fclose(file);
    printf("Student with ID %d modified successfully.\n", studentId);
    return 1; 
}


//////////////////////////////////////////// Action ////////////////////////////////////////////
void performAction(int choice, const char *filename) {
    switch (choice) {
        case 1:
            printf("Add a new student, if student ID already exists, try modifying.\n");
            while (1) {
                int added = addStudent(filename);
                if (added)
                    break;
            }
            break;
        case 2:
            printf("Modify Student Information by given ID.\n");
            modifyStudent(filename);
            break;
        case 3:
            printf("Action 3 selected.\n");
            // Implement the code for action 3 here
            break;
        case 4:
            printf("Exiting the program.\n");
            exit(0); // Exit the program with a status of 0
        default:
            printf("Invalid choice.\n");
    }
}