#include "functions.c"
#include "logic.c" 

#include <stdio.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define USERS "users.txt"
#define STUDENTS "students.txt"
#define MAX_ATTEMPTS 3

int main() {
    User user;
    int success = 0;

    success = attemptLogin(MAX_ATTEMPTS, &user, USERS);

    if (success) {
        printf("Welcome, %s!\n", user.username);
        int choice;
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        performAction(choice, STUDENTS);
    } else {
        printf("Max attempts reached. Access denied.\n");
    }

    return 0;
}