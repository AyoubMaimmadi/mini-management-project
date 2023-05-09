#include "loginLogic.c"
#include "functionalities.c" 

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
        printf("Welcome, %s!, this is a platform where you can add, modify, select, and delete students from a small text file database\n", user.name);
        int choice;
        Menu();
        printf("Please choose an action to perform (you must type number): ");
        scanf("%d", &choice);
        functionalityChoice(choice, STUDENTS);
    } else {
        printf("Max attempts reached. Access denied.\n");
    }

    return 0;
}
