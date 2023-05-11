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



int studentExists(int id, const char *filename) {
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
    printf("Enter student ID (must be a unique number): ");
    scanf("%d", &student.id);

    if (studentExists(student.id, filename)) {
        printf("A student with the same ID already exists.\n");
        fclose(file);
        return 0;
    }

    printf("Enter your full name (e.g., John Doe): ");
    scanf(" %[^\n]", student.name);

    printf("Enter student birth date (yyyy-mm-dd): ");
    scanf(" %[^\n]", student.birthDate);

    printf("Enter student school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter student major (CSC/BA): ");
    scanf(" %[^\n]", student.major);

    printf("Enter student credits (0-140): ");
    scanf("%d", &student.credits);

    printf("Enter student CGPA (0-4): ");
    scanf("%f", &student.cgpa);

    printf("Enter student entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student.entrySemester);

    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n", student.id, student.name, student.birthDate, student.school, student.major, student.credits, student.cgpa, student.entrySemester);

    fclose(file);
    printf("\n\n----> Student added successfully.\n\n");
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

    if (!studentExists(studentId, filename)) {
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
    printf("Enter modified full name (e.g., John Doe): ", student.name);
    scanf(" %[^\n]", student.name);

    printf("Enter modified birth date (yyyy-mm-dd): ");
    scanf(" %[^\n]", student.birthDate);

    printf("Enter modified school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter modified major (CSC/BA): ");
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
    printf("\n\n----> Student with ID %d modified successfully.\n\n", studentId);
    return 1; 
}

////////////////////////////////////// Delete Student //////////////////////////////////////

int deleteStudent(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int studentId;
    printf("Enter student ID to delete: ");
    scanf("%d", &studentId);

    if (!studentExists(studentId, filename)) {
        printf("Student with ID %d does not exist.\n", studentId);
        fclose(file);
        return 0;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentId = 0;
        sscanf(line, "%d,", &currentId);
        if (currentId != studentId) {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0) {
        printf("Error deleting original file.\n");
        return 0;
    }

    if (rename("temp.txt", filename) != 0) {
        printf("Error renaming temporary file.\n");
        return 0;
    }

    printf("\n\n----> Student with ID %d deleted successfully.\n\n", studentId);
    return 1;
}
