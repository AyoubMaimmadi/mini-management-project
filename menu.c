#include "managementLogic.c"
// #include "displayStudentsLogic.c"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void Menu() {
    printf("============================= MENU ============================\n");
    printf("=============== 1. Add a new student to the List \n");
    printf("=============== 2. Modify Student Information \n");
    printf("=============== 3. Delete a Student \n");
    printf("=============== 4. Display Filtered student information \n");
    printf("=============== 5. Change Credentials \n");
    printf("=============== 6. Log out \n");
    printf("================================================================\n\n");

    
}

void displayOptions() {
    printf("\n=================== Display Options ==========================\n");
    printf("=== 0. Display all students \n");
    printf("=== 1. Display all students in registration order \n");
    printf("=== 2. Display all students sorted by name \n");
    printf("=== 3. Display all students sorted by ID \n");
    printf("=== 4. Display a single student by ID \n");
    printf("=== 5. Display students within a GPA range \n");
    printf("=== 6. Display students within a credits range \n");
    printf("=== 7. Exit student display filter \n");
    printf("================================================================\n\n");
}

void functionalityChoice(const char *studentFile) {
    int choice;
    int sortChoice; 
    int studentID;
    float minGPA, maxGPA;
    int minCredits, maxCredits;


    while (1) {
        Menu();
        printf("\nPlease choose an action to perform (you must type number): ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                printf("\nAdd a new student, if student ID already exists, try modifying.\n");
                while (1) {
                    int added = addStudent(studentFile);
                    if (added)
                        break;
                }
                break;
            case 2:
                printf("\nModify Student Information by given ID.\n");
                modifyStudent(studentFile);
                break;
            case 3:
                printf("\nDelete Student Information by given ID.\n");
                deleteStudent(studentFile);
                break;
            case 4:
                printf("\nDisplay Filtered student information.\n");
                while (1) {
                    displayOptions();
                    printf("\nPlease choose an option to display: ");
                    scanf("%d", &choice);
                    getchar(); // Clear the newline character from the input buffer
                    switch (choice) {
                        case 0: 
                            printf("\nDisplaying all students.\n");
                            displayAllStudents(studentFile);
                            break;
                        case 1:
                            printf("\nDisplaying all students in registration order.\n");
                            displayStudentsSortedByRegistrationOrder(studentFile);
                            break;
                        case 2:
                            printf("\nDisplaying all students sorted by name.\n");
                            displayStudentsSortedByName(studentFile);
                            break;
                        case 3:
                            printf("\nPlease choose a sort order (1: asc, 2: desc): ");
                            scanf("%d", &sortChoice);
                            displayStudentsSortedByID(studentFile, sortChoice);
                            break;
                        case 4:
                            printf("Displaying a single student by ID.\n");
                            printf("\nPlease Enter a specific Student ID: ");
                            scanf("%d", &studentID);
                            displayStudentByID(studentFile, studentID);
                            break;
                        case 5:
                            printf("\nDisplaying students within a GPA range.\n");
                            printf("Please enter the minimum GPA: ");
                            scanf("%f", &minGPA);
                            printf("Please enter the maximum GPA: ");
                            scanf("%f", &maxGPA);
                            displayStudentsWithinGPARange(studentFile, minGPA, maxGPA);
                            break;
                       case 6:
                            printf("\nDisplaying students within a credits range.\n");
                            printf("Please enter the minimum credits: ");
                            scanf("%d", &minCredits);
                            printf("Please enter the maximum credits: ");
                            scanf("%d", &maxCredits);
                            displayStudentsWithinCreditsRange(studentFile, minCredits, maxCredits);
                            break;

                        case 7:
                            printf("\nExiting student display filter.\n");
                            break;
                        default:
                            printf("\nSorry, this choice is not recognized! Try another one: \n");
                            break;
                    }
                    if (choice == 7) {
                        break;
                    }
                }
                break;
            case 5:
                printf("\nChange Credentials.\n\n");
                // changeCredentials(); 
                break;
            case 6:
                printf("\nLogged out successfully. Please run the program (main.c) to log back in.\n\n");
                return; 
            default:
                printf("\nSorry, this choice is not recognized! \n\n");
                break;
        }
    }
}
