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

    students[*numStudents] = student;
    (*numStudents)++;

    printf("Student added successfully.\n");
    return 1; // Return success status
}

int findStudentIndex(int id, const Student *students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1; // Student not found
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

void performAction(int choice, Student *students, int *numStudents) {
    switch (choice) {
        case 1:
            printf("Add a new student, if student ID already exists, try modifying.\n");
            while (1) {
                int added = addStudent(students, numStudents);
                if (added)
                    break;
            }
            break;
        case 2:
            printf("Modify Student Information by given ID.\n");
            modifyStudent(students, *numStudents);
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

    // End of example population

    printf("Welcome!\n");
    int choice;
    showMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    performAction(choice, students, &numStudents);

    return 0;
}
