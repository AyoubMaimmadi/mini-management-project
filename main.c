#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this is the structure of the student
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

// this is the menu function
void showMenu() {
    printf("1 -> Add Student\n");
    printf("2 -> Modify Student Information\n");
    printf("3 -> Display student with specific id\n");
    printf("4 -> Load students from file\n");
    printf("5 -> Save all modifications to students file\n");
    printf("6 -> Modify User Password\n");
    printf("7 -> Log out\n");
    printf("Please choose an option: \n");
}

// this is the function to save the added student to the file students.txt
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

// this is the function to add a student by typing the information and then save it to the array of students
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

    printf("Student added successfully to the students array.\n");
    return 1;
}

// this is the function to find the index of the student by a given id
int findStudentIndex(int id, const Student *students, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// this is a function to modify student informations by a given id 
int modifyStudent(Student *students, int numStudents) {
    int studentId;
    printf("Type the student ID you want to modify: ");
    scanf("%d", &studentId);

    int studentIndex = findStudentIndex(studentId, students, numStudents);
    if (studentIndex == -1) {
        printf("This id does not exist.\n ");
        return 0;
    }

    Student *student = &students[studentIndex];

    printf("Type the new full name: ");
    scanf(" %[^\n]", student->name);

    printf("Type the new birth date (yyyymmdd): ");
    scanf(" %[^\n]", student->birthDate);

    printf("Type the new school: ");
    scanf(" %[^\n]", student->school);

    printf("Type the new major: ");
    scanf(" %[^\n]", student->major);

    printf("Type the new credits: ");
    scanf("%d", &student->credits);

    printf("Type the new GPA: ");
    scanf("%f", &student->cgpa);

    printf("Type the new starting semester: ");
    scanf(" %[^\n]", student->entrySemester);

    printf("Student modified successfully.\n");
    return 1;
}

// this is the function to display a specific student informations by a given id
void displayStudent(const Student *students, int numStudents, int studentId) {
    int studentIndex = findStudentIndex(studentId, students, numStudents);
    if (studentIndex == -1) {
        printf("Student is not found.\n", studentId);
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

// this is the function to load all the students informations from the file students.txt
void loadStudentsFromFile(Student *students, int *numStudents) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    
    // while it is not the end of the file it will read the informations and save it to the array of students to be displayed later
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

// this is the function to display all the students informations from the loaded file data
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

// this is a function to save any modifications to the file students.txt
void saveStudentsToFile(const Student *students, int numStudents) {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // loop over the array of students and print the modifications to the file students.txt
    for (int i = 0; i < numStudents; i++) {
        const Student *student = &students[i];
        fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n",
                student->id, student->name, student->birthDate, student->school,
                student->major, student->credits, student->cgpa, student->entrySemester);
    }

    fclose(file);

    printf("Students file updated.\n");
}

// this is a functions to change the password of the user by a given username 
void modifyUserPassword(const char *username, const char *newPassword) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Failed to open the user file.\n");
        return;
    }

    // create a temporary file to save the new password to it
    FILE* tempFile = fopen("temp_users.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to open the temporary file.\n");
        fclose(file);
        return;
    }

    char line[100];
    int modified = 0;

    // loop over the file and check if the username is found or not
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[50];
        char storedPassword[50];
        sscanf(line, "%s %s", storedUsername, storedPassword);

        // if the username is found it will change the password and save it to the temporary file
        if (strcmp(storedUsername, username) == 0) {
            fprintf(tempFile, "%s %s\n", username, newPassword);
            modified = 1;
        } else {
            fprintf(tempFile, "%s %s\n", storedUsername, storedPassword);
        }
    }

    fclose(file);
    fclose(tempFile);

    // if the username is not found it will print a message to the user
    if (!modified) {
        printf("Username not found.\n");
        remove("temp_users.txt");
        return;
    }

    // remove the old file and rename the temporary file to the old file name
    remove("users.txt");
    rename("temp_users.txt", "users.txt");

    printf("Password modified successfully.\n");
}


void performAction(int choice, Student *students, int *numStudents) {
    if (choice == 1) {
        while (1) {
            int added = addStudent(students, numStudents);
            if (added)
                break;
        }
    } else if (choice == 2) {
        printf("Modify Student.\n");
        modifyStudent(students, *numStudents);
    } else if (choice == 3) {
        printf("Display student information.\n");
        int studentId;
        printf("Type the student ID, try IDs 1, or 2: ");
        scanf("%d", &studentId);
        displayStudent(students, *numStudents, studentId);
    } else if (choice == 4) {
        printf("Load all students from file (students.txt).\n");
        loadStudentsFromFile(students, numStudents);
        displayAllStudents(students, *numStudents);
    } else if (choice == 5) {
        printf("Save modifications to students.txt.\n");
        saveStudentsToFile(students, *numStudents);
    } else if (choice == 6) {
        printf("Modify User Password.\n");
        char username[50];
        char newPassword[50];
        printf("Type the username to modify password: ");
        scanf("%s", username);
        printf("Type the new password: ");
        scanf("%s", newPassword);
        modifyUserPassword(username, newPassword);
    } else if (choice == 7) {
        printf("Goodbye!\n");
        exit(0);
    } else {
        printf("Invalid choice.\n");
    }
}


#define MAX_STUDENTS 100

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;

    // Hardcoded student data
    Student student1;
    student1.id = 1;
    strcpy(student1.name, "John Doe");
    strcpy(student1.birthDate, "19980515");
    strcpy(student1.school, "SSE");
    strcpy(student1.major, "CSC");
    student1.credits = 90;
    student1.cgpa = 3.75;
    strcpy(student1.entrySemester, "Fall 2019");

    students[numStudents++] = student1;

    Student student2;
    student2.id = 2;
    strcpy(student2.name, "Jane Smith");
    strcpy(student2.birthDate, "19990322");
    strcpy(student2.school, "SHSS");
    strcpy(student2.major, "CSC");
    student2.credits = 75;
    student2.cgpa = 3.45;
    strcpy(student2.entrySemester, "Spring 2020");

    students[numStudents++] = student2;

    // login functionality
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

    // loop over the file and check if the username and password are correct or not
    char line[100];
    int loginSuccess = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[50];
        char storedPassword[50];
        sscanf(line, "%s %s", storedUsername, storedPassword);

        // if the username and password are found it will change the boolean value of loginSuccess = 1
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
    
    // loop over the menu and perform the action based on the user choice untill the user choose to logout
    while (1) {
        showMenu();
        printf("Type your choice: ");
        scanf("%d", &choice);

        if (choice == 8) {
            printf("Loging out...\n");
            break;  
        }

        performAction(choice, students, &numStudents);
    }

    return 0;
}
