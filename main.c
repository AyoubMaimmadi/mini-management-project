#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    char birthDate[9];
    char school[4];
    char major[50];
    int credits;
    float cgpa;
    char entrySemester[15];
} Student;

void showMenu() {
    printf("1 -> Add Student\n");
    printf("2 -> Modify Student Information\n");
    printf("3 -> Display student with specific ID\n");
    printf("4 -> Load students from file\n");
    printf("5 -> Save all modifications to students file\n");
    printf("6 -> Modify User Password\n");
    printf("8 -> Log out\n");
    printf("Options, please type a number: \n");
}


void saveStudentToFile(const Student *student) {
    FILE* file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n",
            student->id, student->name, student->birthDate, student->school,
            student->major, student->credits, student->cgpa, student->entrySemester);

    fclose(file);

    printf("Student saved successfully to students.txt.\n");
}


int addStudent(Student *students, int *numStudents) {
    Student student;
    printf("Type the student ID: ");
    scanf("%d", &student.id);

    printf("Type the name of student: ");
    scanf(" %[^\n]", student.name);

    printf("student date of birth example: (20040104) (yyyymmdd): ");
    scanf(" %8[^\n]", student.birthDate);


    printf("Type the student school: ");
    scanf(" %[^\n]", student.school);

    printf("Type the student major: ");
    scanf(" %[^\n]", student.major);

    printf("Type the student number of credits: ");
    scanf("%d", &student.credits);

    printf("Type the student GPA: ");
    scanf("%f", &student.cgpa);

    printf("Type the student startimng semester: ");
    scanf(" %[^\n]", student.entrySemester);

    students[*numStudents] = student;
    (*numStudents)++;

    printf("Student added successfully to the student array.\n");
    return 1;
}

int findStudentIndex(int id, const Student *students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

int modifyStudent(Student *students, int numStudents) {
    int studentId;
    printf("Type the student ID to modify: ");
    scanf("%d", &studentId);

    int studentIndex = findStudentIndex(studentId, students, numStudents);
    if (studentIndex == -1) {
        printf("Cant fin this student ");
        return 0;
    }

    Student *student = &students[studentIndex];

    printf("Type the modified full name: ");
    scanf(" %[^\n]", student->name);

    printf("Type the modified birth date (yyyymmdd): ");
    scanf(" %[^\n]", student->birthDate);

    printf("Type the modified school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student->school);

    printf("Type the modified major: ");
    scanf(" %[^\n]", student->major);

    printf("Type the modified credits (0-140): ");
    scanf("%d", &student->credits);

    printf("Type the modified CGPA (0-4): ");
    scanf("%f", &student->cgpa);

    printf("Type the modified entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student->entrySemester);

    printf("Student with ID %d modified successfully.\n", studentId);
    return 1;
}

void displayStudent(const Student *students, int numStudents, int studentId) {
    int studentIndex = findStudentIndex(studentId, students, numStudents);
    if (studentIndex == -1) {
        printf("Student with ID %d does not exist.\n", studentId);
        return;
    }

    const Student *student = &students[studentIndex];
    printf("Student Information:\n");
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Birth Date: %s\n", student->birthDate);
    printf("School: %s\n", student->school);
    printf("Major: %s\n", student->major);
    printf("Credits: %d\n", student->credits);
    printf("GPA: %.2f\n", student->cgpa);
    printf("Starting Semester: %s\n", student->entrySemester);
}

void loadStudentsFromFile(Student *students, int *numStudents) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    while (!feof(file)) {
        Student student;
        fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]\n",
               &student.id, student.name, student.birthDate, student.school,
               student.major, &student.credits, &student.cgpa, student.entrySemester);

        students[*numStudents] = student;
        (*numStudents)++;
    }

    fclose(file);
}

void displayAllStudents(const Student *students, int numStudents) {
    printf("Students:\n");
    for (int i = 0; i < numStudents; i++) {
        const Student *student = &students[i];
        printf("ID: %d\n", student->id);
        printf("Name: %s\n", student->name);
        printf("Birth Date: %s\n", student->birthDate);
        printf("School: %s\n", student->school);
        printf("Major: %s\n", student->major);
        printf("Credits: %d\n", student->credits);
        printf("GPA: %.2f\n", student->cgpa);
        printf("Starting Semester: %s\n", student->entrySemester);
        printf("----------------\n");
    }
}

void saveStudentsToFile(const Student *students, int numStudents) {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        const Student *student = &students[i];
        fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n",
                student->id, student->name, student->birthDate, student->school,
                student->major, student->credits, student->cgpa, student->entrySemester);
    }

    fclose(file);

    printf("Modifications saved successfully to students.txt.\n");
}

void modifyUserPassword(const char *username, const char *newPassword) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Failed to open the user file.\n");
        return;
    }

    // Create a temporary file to store modified data
    FILE* tempFile = fopen("temp_users.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to open the temporary file.\n");
        fclose(file);
        return;
    }

    char line[100];
    int modified = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[50];
        char storedPassword[50];
        sscanf(line, "%s %s", storedUsername, storedPassword);

        if (strcmp(storedUsername, username) == 0) {
            // Modify the password for the specified username
            fprintf(tempFile, "%s %s\n", username, newPassword);
            modified = 1;
        } else {
            // Copy the existing line to the temporary file
            fprintf(tempFile, "%s %s\n", storedUsername, storedPassword);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!modified) {
        printf("Username not found.\n");
        remove("temp_users.txt");  // Remove the temporary file
        return;
    }

    // Replace the original file with the modified temporary file
    remove("users.txt");
    rename("temp_users.txt", "users.txt");

    printf("Password modified successfully.\n");
}



void performAction(int choice, Student *students, int *numStudents) {
    switch (choice) {
        case 1:
            while (1) {
                int added = addStudent(students, numStudents);
                if (added)
                    break;
            }
            break;
        case 2:
            printf("Modify Student.\n");
            modifyStudent(students, *numStudents);
            break;
        case 3:
            printf("Display student information.\n");
            int studentId;
            printf("Type the student ID: ");
            scanf("%d", &studentId);
            displayStudent(students, *numStudents, studentId);
            break;
        case 4:
            printf("Load all students from file (students.txt).\n");
            loadStudentsFromFile(students, numStudents);
            displayAllStudents(students, *numStudents);
            break;
        case 5:
            printf("Save modifications to students.txt.\n");
            saveStudentsToFile(students, *numStudents);
            break;
        case 6:
            printf("Modify User Password.\n");
            char username[50];
            char newPassword[50];
            printf("Type the username to modify password: ");
            scanf("%s", username);
            printf("Type the new password: ");
            scanf("%s", newPassword);
            modifyUserPassword(username, newPassword);
            break;
        case 8:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice.\n");
    }
}


#define MAX_STUDENTS 100

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;

    // Hardcoded student data (for demonstration purposes)
    Student student1;
    student1.id = 1;
    strcpy(student1.name, "John Doe");
    strcpy(student1.birthDate, "1998-05-15");
    strcpy(student1.school, "SSE");
    strcpy(student1.major, "CSC");
    student1.credits = 90;
    student1.cgpa = 3.75;
    strcpy(student1.entrySemester, "Fall 2019");

    students[numStudents++] = student1;

    Student student2;
    student2.id = 2;
    strcpy(student2.name, "Jane Smith");
    strcpy(student2.birthDate, "1999-03-22");
    strcpy(student2.school, "SHSS");
    strcpy(student2.major, "CSC");
    student2.credits = 75;
    student2.cgpa = 3.45;
    strcpy(student2.entrySemester, "Spring 2020");

    students[numStudents++] = student2;

    char username[50];
    char password[50];
    printf("Type your username to login: ");
    scanf("%s", username);
    printf("Type your password: ");
    scanf("%s", password);

    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Failed to open the user file.\n");
        return 1;
    }

    char line[100];
    int loginSuccess = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[50];
        char storedPassword[50];
        sscanf(line, "%s %s", storedUsername, storedPassword);

        if (strcmp(storedUsername, username) == 0 && strcmp(storedPassword, password) == 0) {
            loginSuccess = 1;
            break;
        }
    }

    fclose(file);

    if (!loginSuccess) {
        printf("Wrong password or username, plz try again.\n");
        return 1;
    }

    printf("Welcome!\n");
    int choice;
    while (1) {
        showMenu();
        printf("Type your choice: ");
        scanf("%d", &choice);

        if (choice == 8) {
            printf("Logging out...\n");
            break;  
        }

        performAction(choice, students, &numStudents);
    }

    return 0;
}
