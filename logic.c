#include <stdio.h>

void performAction(int choice, const char *filename) {
    switch (choice) {
        case 1:
            printf("Action 1 selected.\n");
            // Implement the code for action 1 here
            break;
        case 2:
            printf("Action 2 selected.\n");
            // Implement the code for action 2 here
            break;
        case 3:
            printf("Action 3 selected.\n");
            // Implement the code for action 3 here
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void showMenu() {
    printf("===== Menu =====\n");
    printf("1. Perform Action 1\n");
    printf("2. Perform Action 2\n");
    printf("3. Perform Action 3\n");
    printf("================\n");
}

