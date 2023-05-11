#include "managementLogic.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void Menu() {
    printf("============================= MENU =============================\n");
    printf("=============== 1. Add a new student to the List ===============\n");
    printf("=============== 2. Modify Student Information ==================\n");
    printf("=============== 3. Delete a Student ============================\n");
    printf("=============== 4. Log out =====================================\n"); 
    printf("================================================================\n");
}

void functionalityChoice(const char *filename) {
    int choice;
    while (1) {
        Menu();
        printf("Please choose an action to perform (you must type number): ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

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
                printf("Delete Student Information by given ID.\n");
                deleteStudent(filename);
                break;
            case 8:
                printf("Logged out successfully. Please run the program (main.c) to log back in.\n");
                return; // Exit the function and return to the caller
            default:
                printf("Sorry, this choice is not recognized! Try another one: \n");
        }
    }
}