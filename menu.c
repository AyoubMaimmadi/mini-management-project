// importing the functions from the managementLogic file which handles all the important functions for the program
#include "managementLogic.c"

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// this is the menu function that displays the menu for the user to choose from
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

// this is the display options function that displays the options for the user to choose from
// note: these options are for the display filtered student information option (sitch case 4)
// they are displayed only in case 4 fom the menu function of display filtered student information
// also it has its own switch case statement to handle the user's choice inside the original switch case statement
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

// this is the functionality choice function that handles all the case statements for the user's choice
void functionalityChoice(const char *studentFile, User *user, const char *usersFile) {
    // declaring the variables for some inputs from the user that will be used in the switch case statements
    int choice;
    int sortChoice; 
    int studentID;
    float minGPA, maxGPA;
    int minCredits, maxCredits;

    // Loop forever while 1(true) )until the user chooses to exit (return)
    while (1) {
        // displaying the menu for the user to choose from
        Menu();
        printf("\nPlease choose an action to perform (you must type number): ");
        scanf("%d", &choice);
        getchar(); // to clear the newline character from the input buffer
        // switch statement to perform the action based on the user's choice
        // the following are the case statements for the user's choice
        // they are pretty self explanatory so no need for many comments
        switch (choice) {
            case 1:
                printf("\nAdd a new student, if student ID already exists, try modifying.\n");
                // we loop forever until the user adds a student successfully (meaning added is 1, we break)
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
            // this is the case where we are displaying the display menu by entering another switch statement
            case 4:
                printf("\nDisplay Filtered student information.\n");
                // we loop forever until the user chooses to exit (return)
                while (1) {
                    // we show the display options for the user to choose from
                    displayOptions();
                    printf("\nPlease choose an option to display: ");
                    scanf("%d", &choice);
                    getchar(); // to clear the newline character from the input buffer
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
                            printf("\nPlease choose a sort order (1: ascending, 2: descending): ");
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
                    // if the user chooses to exit (number 7), we break from this switch case statement
                    // but we also return to the original switch case statement (the one that handles the user's choice)
                    if (choice == 7) {
                        break;
                    }
                }
                break;
            case 5:
                printf("\nChange Credentials.\n\n");
                changeCredentials(user, usersFile); 
                break;
            case 6:
                // we can exit the program by returning  
                printf("\nLogged out successfully. Please run the program (main.c) to log back in.\n\n");
                return; 
            // if the user enters a choice that is not recognized, display an error message
            default:
                printf("\nSorry, this choice is not recognized! \n\n");
                break;
        }
    }
}
