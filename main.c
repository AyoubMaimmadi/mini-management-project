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
    printf("Options, please type a number: \n");
    printf("1 -> Add Student (Authomatically saved in students.txt)\n");
    printf("2 -> Modify Student Information\n");
    printf("3 -> Display student with specific id\n");
    printf("4 -> Load students from file\n");
    printf("8 -> Log out\n");
}

int studentExist(int id, const Student *students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int addStudent(Student *students, int *numStudents) {
    Student student;
    printf("Enter student ID: ");
    scanf("%d", &student.id);

    if (studentExist(student.id, students, *numStudents)) {
        printf("A student with the same ID already exists.\n");
        return 0;
    }

    printf("Enter your name: ");
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

    students[*numStudents] = student;
    (*numStudents)++;

    // Open the students.txt file in append mode
    FILE* file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    // Write the student information to the file
    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n",
            student.id, student.name, student.birthDate, student.school,
            student.major, student.credits, student.cgpa, student.entrySemester);

    // Close the file
    fclose(file);

    printf("Student added successfully.\n");
    return 1;

    printf("Student added successfully.\n");
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
    printf("Enter student ID to modify: ");
    scanf("%d", &studentId);

    int studentIndex = findStudentIndex(studentId, students, numStudents);
    if (studentIndex == -1) {
        printf("Student with ID %d does not exist.\n", studentId);
        return 0;
    }

    Student *student = &students[studentIndex];

    printf("Enter modified full name: ");
    scanf(" %[^\n]", student->name);

    printf("Enter modified birth date (yyyy-mm-dd): ");
    scanf(" %[^\n]", student->birthDate);

    printf("Enter modified school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student->school);

    printf("Enter modified major: ");
    scanf(" %[^\n]", student->major);

    printf("Enter modified credits (0-140): ");
    scanf("%d", &student->credits);

    printf("Enter modified CGPA (0-4): ");
    scanf("%f", &student->cgpa);

    printf("Enter modified entry semester (e.g., Fall 2021): ");
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
    printf("CGPA: %.2f\n", student->cgpa);
    printf("Entry Semester: %s\n", student->entrySemester);
}

void loadStudentsFromFile(Student *students, int *numStudents) {
    // Open the students.txt file for reading
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // Read student information from the file and add them to the students array
    while (!feof(file)) {
        Student student;
        fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]\n",
               &student.id, student.name, student.birthDate, student.school,
               student.major, &student.credits, &student.cgpa, student.entrySemester);

        students[*numStudents] = student;
        (*numStudents)++;
    }

    // Close the file
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
        printf("CGPA: %.2f\n", student->cgpa);
        printf("Entry Semester: %s\n", student->entrySemester);
        printf("----------------\n");
    }
}

void performAction(int choice, Student *students, int *numStudents) {
    switch (choice) {
        case 1:
            printf("Add a student.\n");
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
            printf("Enter student ID: ");
            scanf("%d", &studentId);
            displayStudent(students, *numStudents, studentId);
            break;
        case 4:
            printf("Load all students from file (students.txt).\n");
            loadStudentsFromFile(students, numStudents);
            displayAllStudents(students, *numStudents);
            break; 
        case 8:
            printf("Exiting the program.\n");
            exit(0); 
        default:
            printf("Invalid choice.\n");
    }
}

#define MAX_STUDENTS 100

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;

    Student student1;
    student1.id = 1001;
    strcpy(student1.name, "John Doe");
    strcpy(student1.birthDate, "1998-05-15");
    strcpy(student1.school, "SBA");
    strcpy(student1.major, "Finance");
    student1.credits = 90;
    student1.cgpa = 3.75;
    strcpy(student1.entrySemester, "Fall 2019");

    students[numStudents++] = student1;

    Student student2;
    student2.id = 1002;
    strcpy(student2.name, "Jane Smith");
    strcpy(student2.birthDate, "1999-03-22");
    strcpy(student2.school, "SHSS");
    strcpy(student2.major, "Psychology");
    student2.credits = 75;
    student2.cgpa = 3.45;
    strcpy(student2.entrySemester, "Spring 2020");

    students[numStudents++] = student2;

    printf("Login\n");
    char username[50];
    char password[50];
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // Open the users.txt file for reading
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Failed to open the user file.\n");
        return 1;
    }

    // Iterate through the lines in the file and compare the username and password
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

    // Close the users.txt file
    fclose(file);

    if (!loginSuccess) {
        printf("Invalid username or password. Exiting...\n");
        return 1;
    }

    printf("Welcome!\n");
    int choice;
    showMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    performAction(choice, students, &numStudents);

    return 0;
}
