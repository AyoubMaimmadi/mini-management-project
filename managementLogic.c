// this code may seem long but it is very repetitive
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Student struct
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

// function that checks if the date format is valid
int isValidDateFormat(const char *date) {
    // Validate the birth date format (yyyy-mm-dd)
    int year, month, day;
    // if the date is not in the format of yyyy-mm-dd then return 0
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        return 0;
    }
    // otherwise return 1
    return 1;
}

// function that checks if the birth year is valid
int isValidBirthYear(int year) {
    // Check if the birth year falls within a specific range
    // starting from the year of AUI opening (1995) to the year 2010 to include young students
    return (year >= 1995 && year <= 2010);
}

// function that checks if the credits is within the range (0-140)
int isValidCredit(int credits) {
    // this returns 1 if the credits is within the range (0-140) and 0 otherwise
    return (credits >= 0 && credits <= 140);
}

// function that checks if the cgpa is within the range (0-4)
int isValidCGPA(float cgpa) {
    // this returns 1 if the cgpa is within the range (0-4) and 0 otherwise
    return (cgpa >= 0 && cgpa <= 4);
}

// function that checks if the student exists in the file or not, 1 if exists and 0 otherwise
int studentExists(int id, const char *filename) {
    // this function returns 1 if the student exists in the file and 0 otherwise
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    // initialize the found variable to 0 and line array to 100 in size
    int found = 0;
    char line[100];
    // loop through the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // initialize the currentId variable to 0
        int currentId = 0;
        // scan the line and store the id in the currentId variable
        sscanf(line, "%d,", &currentId);
        // if the currentId is equal to the id then set found to 1 and break the loop
        if (currentId == id) {
            found = 1;
            break;
        }
    }

    // close the file 
    fclose(file);
    // return the found variable (1 if the student exists and 0 otherwise)
    return found;
}

//////////////////////////////////////// Add Student ////////////////////////////////////////
int addStudent(const char *filename) {
    // open the file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    // initialize the student struct
    Student student;
    // get the student id from the user
    printf("Enter student ID (must be a unique number): ");
    scanf("%d", &student.id);
    
    // Check if the student already exists
    if (studentExists(student.id, filename)) {
        printf("A student with the same ID already exists.\n");
        fclose(file);
        return 0;
    }

    // get the student name from the user
    printf("Enter your full name (e.g., John Doe): ");
    getchar(); // Clear the newline character from the previous input
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; // remove the newline because it gave me some problems

    printf("Enter student birth date (yyyy-mm-dd): ");
    fgets(student.birthDate, sizeof(student.birthDate), stdin);
    student.birthDate[strcspn(student.birthDate, "\n")] = '\0';

    // Validate the birth date format
    if (!isValidDateFormat(student.birthDate)) {
        printf("Invalid birth date format. Please use yyyy-mm-dd.\n");
        fclose(file);
        return 0;
    }

    // Get the birth year from the birth date and store it in the year variable
    int year;
    sscanf(student.birthDate, "%d", &year);

    // Check if the birth year falls within the specified range
    if (!isValidBirthYear(year)) {
        printf("Invalid birth year. Please enter a value between 1995 (starting of AUI) and 2010.\n");
        fclose(file);
        return 0;
    }

    // get the student information from the user and store it in the student struct
    printf("Enter student school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter student major (CSC/BA): ");
    scanf(" %[^\n]", student.major);

    printf("Enter student credits (0-140): ");
    scanf("%d", &student.credits);

     // Check if the credits fall within the specified range (0-140)
    if (!isValidCredit(student.credits)) {
        printf("Invalid credits. Please enter a value between 0 and 140.\n");
        fclose(file);
        return 0;
    }

    printf("Enter student CGPA (0-4): ");
    scanf("%f", &student.cgpa);

    // Check if the cgpa fall within the specified range (0-4)
    if (!isValidCGPA(student.cgpa)) {
        printf("Invalid CGPA. Please enter a value between 0 and 4.\n");
        fclose(file);
        return 0;
    }

    printf("Enter student entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student.entrySemester);

    // Write the student information to the file
    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n", student.id, student.name, student.birthDate, student.school, student.major, student.credits, student.cgpa, student.entrySemester);

    // Close the file
    fclose(file);
    printf("\n\n----> Student added successfully.\n\n");
    return 1; // return 1 for a success status
}

////////////////////////////////////// Modify Student Information //////////////////////////////////////
int modifyStudent(const char *filename) {
    // Open the file in read and write mode
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    // Get the student id from the user
    int studentId;
    printf("Enter student ID to modify: ");
    scanf("%d", &studentId);

    // check if the student exists
    if (!studentExists(studentId, filename)) {
        printf("Student with ID %d does not exist.\n", studentId);
        fclose(file);
        return 0;
    }

    // find the position of the student in the file
    // we initialize the pos variable to -1 that indicates that the student is not found (defalut)
    long pos = -1;
    // initialize the line array to 100 in size
    char line[100];
    // loop through the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // initialize the currentId 
        int currentId = 0;
        // scan the line and store the id in the currentId variable
        sscanf(line, "%d,", &currentId);
        // if the currentId is equal to the studentId then set the pos variable to the current position in the file
        if (currentId == studentId) {
            // this means that we found the student the we change pos to the current position in the file 
            pos = ftell(file) - strlen(line);
            // then we break the loop
            break;
        }
    }

    // if pos is still -1 then this means that the student is not found, so we close the file and return 0
    if (pos == -1) {
        printf("Error finding student position in the file.\n");
        fclose(file);
        return 0;
    }

    // otherwise we initialize the student struct and read the student information from the file
    // in order to get the new information from the user that needs to be modified or replaced
    Student student;
    printf("Enter modified full name (e.g., John Doe): ");
    getchar(); // clear the newline character from the previous input
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; // Remove the newline

    printf("Enter modified birth date (yyyy-mm-dd): ");
    fgets(student.birthDate, sizeof(student.birthDate), stdin);
    student.birthDate[strcspn(student.birthDate, "\n")] = '\0';

    // if the birth date format is invalid then we close the file and return 0
    if (!isValidDateFormat(student.birthDate)) {
        printf("Invalid birth date format. Please use yyyy-mm-dd.\n");
        fclose(file);
        return 0;
    }

    // same process as the previous function of add student
    int year;
    sscanf(student.birthDate, "%d", &year);

    // Check if the birth year falls within the specified range
    if (!isValidBirthYear(year)) {
        printf("Invalid birth year. Please enter a value between 1995 (Start of AUI) and 2010.\n");
        fclose(file);
        return 0;
    }

    printf("Enter modified school (SBA/SHSS/SSE): ");
    scanf(" %[^\n]", student.school);

    printf("Enter modified major (CSC/BA): ");
    scanf(" %[^\n]", student.major);

    printf("Enter modified credits (0-140): ");
    scanf("%d", &student.credits);

    // Check if the credits fall within the specified range
    if (!isValidCredit(student.credits)) {
        printf("Invalid credits. Please enter a value between 0 and 140.\n");
        fclose(file);
        return 0;
    }

    printf("Enter modified CGPA (0-4): ");
    scanf("%f", &student.cgpa);

    // Check if the cgpa fall within the specified range
    if (!isValidCGPA(student.cgpa)) {
        printf("Invalid CGPA. Please enter a value between 0 and 4.\n");
        fclose(file);
        return 0;
    }

    printf("Enter modified entry semester (e.g., Fall 2021): ");
    scanf(" %[^\n]", student.entrySemester);

    // finaly, we use fseek to move the file pointer to the position of the student in the file
    // and then we print the student information with the new information in the file
    fseek(file, pos, SEEK_SET);
    fprintf(file, "%d,%s,%s,%s,%s,%d,%.2f,%s\n", studentId, student.name, student.birthDate, student.school, student.major, student.credits, student.cgpa, student.entrySemester);

    // close the file and return 1 for a success status
    fclose(file);
    printf("\n\n----> Student with ID %d modified successfully.\n\n", studentId);
    return 1; 
}

////////////////////////////////////// Delete Student //////////////////////////////////////
int deleteStudent(const char *filename) {
    // Open the file in read mode, because we wont delete from this file 
    // instead we will copy the content of this file to a temporary file
    // except the student that we want to delete
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    // same as before 
    int studentId;
    printf("Enter student ID to delete: ");
    scanf("%d", &studentId);

    // same as before
    if (!studentExists(studentId, filename)) {
        printf("Student with ID %d does not exist.\n", studentId);
        fclose(file);
        return 0;
    }

    // here we create a temporary file to copy the content of the original file except the student that we want to delete
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return 0;
    }
    
    // we initialize the line array to 100 in size
    char line[100];
    // loop through the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentId = 0;
        // scan the line and store the id in the currentId variable
        sscanf(line, "%d,", &currentId);
        // as long as the currentId is not equal to the studentId then we copy the line to the temporary file
        if (currentId != studentId) {
            fputs(line, tempFile);
        }
    }

    // when we finish copying the content of the original file to the temporary file we close both files
    fclose(file);
    fclose(tempFile);

    // we remove the original file
    remove(filename);
    // and finally rename the temporary file to the original filename which is students.txt
    rename("temp.txt", filename);

    // and then return 1 for a success status
    printf("\n\n----> Student with ID %d deleted successfully.\n\n", studentId);
    return 1;
}

////////////////////////////////////// display All Students //////////////////////////////////////
void displayAllStudents(const char *filename) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // print the header of the table of students to be displayed
    printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // initialize the line array to 100 in size
    char line[100];
    // loop through the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // initialize the variables that we will use to store the student information for each line every time we loop
        int id;
        char name[50];
        char birthDate[11];
        char school[4];
        char major[50];
        int credits;
        float cgpa;
        char entrySemester[15];

        // scan the line and store the student information in the variables
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]", &id, name, birthDate, school, major, &credits, &cgpa, entrySemester);

        // and then print the student information in a formatted way seperated by | 
        printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
               id, name, birthDate, school, major, credits, cgpa, entrySemester);
    }

    // close the file
    fclose(file);
}

////////////////////////////////////// display Students Sorted By Name //////////////////////////////////////
void displayStudentsSortedByName(const char *filename) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // initialize an array of structures of type Student where we will store the students information for eachone
    Student students[100]; 
    // initialize a counter to count the number of students in the file to loop through them later for sorting and printing
    int count = 0;
    // initialize the line array to 100 in size
    char line[100];
    // we loop through the file line by line and store the student information in the array of structures
    while (fgets(line, sizeof(line), file) != NULL && count < 100) {
        // we use sscanf to scan the line and store the student information in the array of structures
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]",
               &students[count].id,
               students[count].name,
               students[count].birthDate,
               students[count].school,
               students[count].major,
               &students[count].credits,
               &students[count].cgpa,
               students[count].entrySemester);
        // we increment the counter by 1 every time we loop
        count++;
    }

    // close the file
    fclose(file);

    // sorting the array of students by name (using bubble sort)
    for (int i = 0; i < count - 1; i++) {
        // we iterate over the unsorted part of the array
        for (int j = 0; j < count - i - 1; j++) {
            // we compare the names of adjacent students
            // if the name of the current student is greater than the name of the next student then we swap them
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                // we use a temporary variable of type Student to store the current student
                Student temp = students[j];
                // and the we swap by assigning the current student to the next student
                students[j] = students[j + 1];
                // and then we assign the next student to the temporary variable
                students[j + 1] = temp;
            }
        }
    }

    // print the header of the table of students to be displayed
    printf("---- Students Sorted by Name ----\n");
     printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // loop through the sorted array of students and print the student information in a formatted way seperated by |
    for (int i = 0; i < count; i++) {
        printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
               students[i].id,
               students[i].name,
               students[i].birthDate,
               students[i].school,
               students[i].major,
               students[i].credits,
               students[i].cgpa,
               students[i].entrySemester);
    }
}

//////////////////// display Students Sorted By Registration Order //////////////////////////////////////
// we are assuming that registration order means the entry semester of the student 
void displayStudentsSortedByRegistrationOrder(const char *filename) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // initialize an array of structures of type Student where we will store the students information for eachone
    Student students[100]; 
    // initialize a counter to count the number of students in the file to loop through them later for sorting and printing
    int count = 0;
    // same as the previous function wew loop and store the student information in the array of structures
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL && count < 100) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]",
               &students[count].id,
               students[count].name,
               students[count].birthDate,
               students[count].school,
               students[count].major,
               &students[count].credits,
               &students[count].cgpa,
               students[count].entrySemester);
        // and increment the counter by 1 every time we loop
        count++;
    }

    fclose(file);

    // Also the same as the previous funcion
    // we sort the array of students by entry semester (using bubble sort)
    for (int i = 0; i < count - 1; i++) {
        // we iterate over the unsorted part of the array
        for (int j = 0; j < count - i - 1; j++) {
            // we compare the names of adjacent students
            // if the name of the current student is greater than the name of the next student then we swap them
            if (strcmp(students[j].entrySemester, students[j + 1].entrySemester) > 0) {
                // we use a temporary variable of type Student to store the current student
                Student temp = students[j];
                // and the we swap by assigning the current student to the next student
                students[j] = students[j + 1];
                // and then we assign the next student to the temporary variable
                students[j + 1] = temp;
            }
        }
    }

    // we print the header of the table of students to be displayed
    printf("---- Students Sorted by Registration Order ----\n");
     printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // we loop through the sorted array of students and print the student information in a formatted way seperated by |
    for (int i = 0; i < count; i++) {
        printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
               students[i].id,
               students[i].name,
               students[i].birthDate,
               students[i].school,
               students[i].major,
               students[i].credits,
               students[i].cgpa,
               students[i].entrySemester);
    }
}

////////////////////////////////////// display Students Sorted By ID //////////////////////////////////////
void displayStudentsSortedByID(const char *filename, int sortOrder) {
    // open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // same as the previous function
    Student students[100]; 
    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL && count < 100) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]",
               &students[count].id,
               students[count].name,
               students[count].birthDate,
               students[count].school,
               students[count].major,
               &students[count].credits,
               &students[count].cgpa,
               students[count].entrySemester);
        count++;
    }

    fclose(file);

    // same as the previous functions, except that we sort by sort order (ascending 1, or descending, 2)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // if the sort order is ascending and the id of the current student is greater than the id of the next student
            // or if the sort order is descending and the id of the current student is less than the id of the next student
            if ((sortOrder == 1 && students[j].id > students[j + 1].id) ||
                (sortOrder == 2 && students[j].id < students[j + 1].id)) {
                // Swap the students
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // print the header of the table of students to be displayed
    printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // loop and print the students information in a formatted way seperated by |
    for (int i = 0; i < count; i++) {
        printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
               students[i].id,
               students[i].name,
               students[i].birthDate,
               students[i].school,
               students[i].major,
               students[i].credits,
               students[i].cgpa,
               students[i].entrySemester);
    }
}

//////////////////// display Student By ID //////////////////////////////////////
void displayStudentByID(const char *filename, int id) {
    // open file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // loop through the file until we find the student with the given id
    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentId = 0;
        sscanf(line, "%d,", &currentId);
        // if the id of the current student is equal to the given id then we found the student
        if (currentId == id) {
            // change the value of found to 1 to break the loop
            found = 1;
            break;
        }
    }

    // if we found the student then we print the student information according to this format under
    if (found) {
        int studentId;
        char name[50];
        char birthDate[11];
        char school[4];
        char major[50];
        int credits;
        float cgpa;
        char entrySemester[15];

        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]",
               &studentId, name, birthDate, school, major, &credits, &cgpa, entrySemester);

        printf("---- Student Details ----\n");
        printf("Student ID: %d\n", studentId);
        printf("Name: %s\n", name);
        printf("Birth Date: %s\n", birthDate);
        printf("School: %s\n", school);
        printf("Major: %s\n", major);
        printf("Credits: %d\n", credits);
        printf("CGPA: %.2f\n", cgpa);
        printf("Entry Semester: %s\n", entrySemester);
    } else {
        // otherwise we print that the student does not exist
        printf("Student with ID %d does not exist.\n", id);
    }

    // at last we close the file
    fclose(file);
}

//////////////////// display Students Within a GPA Range //////////////////////////////////////
void displayStudentsWithinGPARange(const char *filename, float minGPA, float maxGPA) {
    // open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // print the header of the table of students to be displayed
    printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // loop through the file and store each student in the variables below
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        char name[50];
        char birthDate[11];
        char school[4];
        char major[50];
        int credits;
        float cgpa;
        char entrySemester[15];

        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]", &id, name, birthDate, school, major, &credits, &cgpa, entrySemester);
        
        // print stident only if the cgpa of the current student is within the given range then we print the student
        if (cgpa >= minGPA && cgpa <= maxGPA) {
            printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
                   id, name, birthDate, school, major, credits, cgpa, entrySemester);
        }
    }

    fclose(file);
}

//////////////////// display Students Within Credits Range //////////////////////////////////////
void displayStudentsWithinCreditsRange(const char *filename, int minCredits, int maxCredits) {
    // open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // print the header of the table of students to be displayed
    printf("---- Students within Credits Range (%d - %d) ----\n", minCredits, maxCredits);
    printf("Student ID | Name                | Birth Date | School | Major | Credits | CGPA | Entry Semester\n");
    printf("---------------------------------------------------------------------------------------------\n");

    // same as the previous function
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        char name[50];
        char birthDate[11];
        char school[4];
        char major[50];
        int credits;
        float cgpa;
        char entrySemester[15];

        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%f,%[^\n]",
               &id, name, birthDate, school, major, &credits, &cgpa, entrySemester);

        // this time we check if the credits of the current student is within the given range then print the student
        if (credits >= minCredits && credits <= maxCredits) {
            printf("%-10d | %-20s | %-10s | %-6s | %-5s | %-7d | %.2f | %-15s\n",
                   id, name, birthDate, school, major, credits, cgpa, entrySemester);
        }
    }

    fclose(file);
}