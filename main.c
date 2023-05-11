//importing all the functions from the other files
#include "loginLogic.c"
#include "menu.c" 

#include <stdio.h>
#include <stdlib.h>

//defining the max length of important variables
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define USERS "users.txt"
#define STUDENTS "students.txt"
#define MAX_ATTEMPTS 3

int main() {
    //declaring the user and success variables
    User user;
    int success = 0;

    // calling the attemptLogin function and passing the max attempts, user, and users file
    success = attemptLogin(MAX_ATTEMPTS, &user, USERS);

    //if success it true, then the user is welcomed and the functionality choice function is called
    if (success) {
        printf("\nWelcome, %s!, this is a platform where you can add, modify, display, filter, and delete students from a small text file database.\n\n", user.name);
        functionalityChoice(STUDENTS, &user, USERS);
    } else {
        printf("Max attempts reached. Access denied.\n\n");
    }

    return 0;
}
