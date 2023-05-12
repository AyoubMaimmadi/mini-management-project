//importing all the functions from the other files
#include "loginLogic.c"
#include "menu.c" 

#include <stdio.h>
#include <stdlib.h>

// defining the max length of the username and password
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// defining the users and students file names 
#define USERS "users.txt"
#define STUDENTS "students.txt"

// defining the max attempts for the user to login
#define MAX_ATTEMPTS 3

int main() {
    //declaring the user 
    User user;
    // initializing a boolean success variable to 0 for false
    int success = 0;

    // calling the attemptLogin function and passing the max attempts, user, and users file
    // the function returns a boolean value 1 of true if the user is successfully logged in
    // this function comes from the loginLogic.c file
    success = attemptLogin(MAX_ATTEMPTS, &user, USERS);

    //if success it true, then the user is welcomed and the functionality choice function is called
    if (success) {
        printf("\nWelcome, %s!, this is a platform where you can add, modify, display, filter, and delete students from a small text file database.\n\n", user.name);
        // we pass the students file, the user, and the users file to the functionality choice function
        // this function is where the user can choose what they want to do, and handles all the case statements
        // this function comes from the menu.c file
        functionalityChoice(STUDENTS, &user, USERS);
    } else {
        // if the user is not successfully logged in (meaning success == 0), then the max attempts have been reached
        printf("Max attempts reached. Access denied.\n\n");
    }

    return 0;
}
