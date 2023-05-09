#include "managementLogic.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void Menu() {
    printf("============================= MENU =============================\n");
    printf("=============== 1. Add a new student to the list ===============\n");
    printf("=============== 2. Modify Student Information ==================\n");
    printf("=============== 3. Perform Action 3 ============================\n");
    printf("=============== 4. Log out =====================================\n"); 
    printf("================================================================\n");
}

void functionalityChoice(int choice, const char *filename) {
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
            printf("Loged out succesfully, please run the program (main.c) to log back in.\n");
            exit(0); // Exit the program with a status of 0
        default:
            printf("Invalid choice.\n");
    }
}