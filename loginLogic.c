#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

//defining the max length of important variables
#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_LINE_LENGTH (MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2)

//defining the user struct
typedef struct {
    char name[MAX_NAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;


// funtions that return the length of a word
int wordLength(const char *str) {
  int length = 0;
  // incrementing the length of the word until the end of the word /0 is reached
  while (str[length] != '\0') {
    length++;
  }
  // returning the length of the word an an int
  return length;
}

// function that compares two words if they are similar and returns 0 if they are the same, 1 if the first word is greater than the second and -1 if the second word is greater than the first
int wordCompare(const char *str1, const char *str2) {
    int i = 0;
    // comparing the two words until the end of one of them is reached
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            // If the characters are different, return the difference
            return str1[i] - str2[i];
        }
        i++;
    }

    // If one word is longer than the other
    if (str1[i] != '\0') {
        return 1;
    // If the other word is longer than the first
    } else if (str2[i] != '\0') {
        return -1;
    }

    return 0;  // if both words are equal
}

// function that cleans up the word from the new line character
void wordCleanUp(char *str) {
  // getting the length of the word
  int length = wordLength(str);
  // if the word is not empty and 
  // if the last character of the word is a new line character, replace it with the end of word character
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
}

// function that checks the credentials of the user if they are valid by comparing them to the users file
int checkCredentials(User *user, const char *filename) {
    // opening the file and returning if it fails
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    // initializing the variables of line that will be read from the file and found that will looped over
    char line[MAX_LINE_LENGTH];
    // boolean value that checks if the user is found in the file
    int found = 0;

    // looping over the file line by line 
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // initializing the variables that will be stored from the file contents
        char stored_username[MAX_USERNAME_LENGTH];
        char stored_password[MAX_PASSWORD_LENGTH];
        char stored_name[MAX_NAME_LENGTH];

        // scanning the line and storing the variables we just initialized
        sscanf(line, "%s %s %[^\n]", stored_username, stored_password, stored_name);

        // comparing the username and password of the user with the stored username and password
        if (wordCompare(user->username, stored_username) == 0 &&
            wordCompare(user->password, stored_password) == 0) {
            // if the user is found, we change the boolean variable to 1 for later use
            found = 1;
            // we copy the name of the user to the user struct so we can use it later for the welcome message
            strncpy(user->name, stored_name, MAX_NAME_LENGTH);
            break;
        }
    }

    // closing the file
    fclose(file);

    // returning the boolean value of found 0 if the user is not found and 1 if the user is found
    return found;
}

// function that attempts to login the user by asking for their username and password 
int attemptLogin(int maxAttempts, User *user, const char *filename) {
    // initializing the variable that will count the attempts of the user and comparing it to the max attempts
    int attempts = 0;

    printf("\nWelcome to the login page for student management platfrom (SMP). All modifications directly impact the students file just like a real database (without the need for a save file option). Permission was aquirred from the professor to impliment it this way.\n\n");

    // looping over the login page until the user reaches the max attempts
    // while max attempts is not reached, we ask the user for their username and password 
    // clean the input from the new line character and check if the credentials are valid
    while (attempts < maxAttempts) {
        printf("Enter your username: ");
        fgets(user->username, MAX_USERNAME_LENGTH, stdin);
        wordCleanUp(user->username);

        printf("Enter your password: ");
        fgets(user->password, MAX_PASSWORD_LENGTH, stdin);
        wordCleanUp(user->password);

        // if the credentials are valid, we return 1 and the user is logged in
        if (checkCredentials(user, filename)) {
            return 1;
            // if the credentials are not valid, we increment the attempts and print the attempts remaining
        } else {
            attempts++;
            printf("Invalid credentials. Attempts remaining: %d\n\n",
                   maxAttempts - attempts);
        }
    }
    // if the user reaches the max attempts, we return 0 and the user is not logged in
    return 0;
}

// function that validates the password of the user, making sure it has all the necessary requirements
int validatePassword(const char *password) {
    // we get the length of the password
    int length = wordLength(password);

    // we check if the length of the password is between 6 and 12 characters
    if (length < 6 || length > 12) {
        printf("Invalid password length. Password must contain 6-12 characters.\n");
        // we return 0 if the password is too short of too long 
        return 0;
    }

    // initializing the variables that will check if the password has the required character types
    // we set them to 0, and if they are found, we set them to 1 to indicate that they are found
    int hasLower = 0;
    int hasUpper = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    // we loop over the password character by character and check if it has the required character types
    for (int i = 0; i < length; i++) {
        // if the character is lowercase, we set hasLower to 1
        if (islower(password[i]))
            hasLower = 1;
        // if the character is uppercase, we set hasUpper to 1
        else if (isupper(password[i]))
            hasUpper = 1;
        // if the character is a digit, we set hasDigit to 1
        else if (isdigit(password[i]))
            hasDigit = 1;
        // if the character is a special character like @ or %, we set hasSpecial to 1
        else if (ispunct(password[i]))
            hasSpecial = 1;
    }

    // if one of these variables are not set to 1, we print an error message and return 0
    if (!(hasLower && hasUpper && hasDigit && hasSpecial)) {
        printf("Invalid password format. Password must contain at least one lowercase letter, one uppercase letter, one digit, and one special character.\n");
        return 0;
    }

    // otherwise, we return 1 that indicates that the password is valid
    return 1;
}

// function that changes the credentials of the user, either the username, password or both
void changeCredentials(User *user, const char *filename) {
    // we open the file in read mode
    FILE *file = fopen(filename, "r");
    // if the file is null, we print an error message and return
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // initializing the variables that will store the new credentials
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newUsername[MAX_USERNAME_LENGTH];

    // we ask the user for their current password and clean the input from the new line character
    printf("Enter your current password: ");
    fgets(currentPassword, MAX_PASSWORD_LENGTH, stdin);
    wordCleanUp(currentPassword);

    // we check if the current password is the same as the password of the user
    if (wordCompare(user->password, currentPassword) != 0) {
        printf("Invalid current password. Please try again.\n\n");
        fclose(file);
        return;
    }

    // we initialize the variables that will check if the user changed their username or password
    // we set them to 0, and if they are changed, we set them to 1 to indicate that they are changed
    int changeUsername = 0;
    int changePassword = 0;

    // we ask the user for their choice and clean the input from the new line character
    printf("Choose an option:\n");
    printf("1. Change username\n");
    printf("2. Change password\n");
    printf("3. Change both username and password\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    getchar(); // to clear the newline character from the input buffer

    // if the user chooses 1 or 3, we ask them for their new username
    // if the user chooses 3 we also change the username as well as the password
    if (choice == 1 || choice == 3) {
        printf("Enter your new username: ");
        fgets(newUsername, MAX_USERNAME_LENGTH, stdin);
        wordCleanUp(newUsername);
        // if the new username is the same as the current username, we print an error message and return
        if (wordCompare(user->username, newUsername) == 0) {
            printf("New username is the same as the current username.\n");
            fclose(file);
            return;
        }
        // otherwise, we set changeUsername to 1 to indicate that the username is changed   
        changeUsername = 1;
    }

    // if the user chooses 2 or 3, we ask them for their new password
    // if the user chooses 3 we also change the username as well as the password
    if (choice == 2 || choice == 3) {
        printf("Enter your new password: ");
        fgets(newPassword, MAX_PASSWORD_LENGTH, stdin);
        wordCleanUp(newPassword);
        // if the new password is the same as the current password, we print an error message and return    
        if (wordCompare(user->password, newPassword) == 0) {
            printf("New password is the same as the current password.\n");
            fclose(file);
            return;
        }
        // otherwise, we check if the new password is valid, if not, we return
        if (!validatePassword(newPassword)) {
            fclose(file);
            return;
        }
        // otherwise, we set changePassword to 1 to indicate that the password is changed
        changePassword = 1;
    }

    // we create a temporary file to store the new credentials as well as the other credentials from the file
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(file);
        return;
    }

    // we initialize a variable that will store the line from the file  
    char line[MAX_LINE_LENGTH];
    // to check if the credentials are changed
    int credentialsChanged = 0;

    // we loop over the file line by line
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // initializing the variables that will store the credentials from the file
        char stored_username[MAX_USERNAME_LENGTH];
        char stored_password[MAX_PASSWORD_LENGTH];
        char stored_name[MAX_NAME_LENGTH];

        // we scan the line and store the credentials in the variables
        sscanf(line, "%s %s %[^\n]", stored_username, stored_password, stored_name);

        // if the username and password from the file are the same as the username and password of the user
        if (wordCompare(user->username, stored_username) == 0 &&
            wordCompare(user->password, stored_password) == 0) {
            // and if the user changed their username or password, we change the credentials
            if (changeUsername) {
                // we copy the new username to the stored username and the username of the user
                strncpy(stored_username, newUsername, MAX_USERNAME_LENGTH);
                strncpy(user->username, newUsername, MAX_USERNAME_LENGTH);
                        }
            // and if the user changed their password, we change the credentials
            if (changePassword) {
                // we copy the new password to the stored password and the password of the user
                strncpy(stored_password, newPassword, MAX_PASSWORD_LENGTH);
                strncpy(user->password, newPassword, MAX_PASSWORD_LENGTH);
            }
            // to indicate that the credentials are changed
            credentialsChanged = 1;
        }
        // and finally, we write the credentials to the temporary file to rename it later
        fprintf(tempFile, "%s %s %s\n", stored_username, stored_password, stored_name);
    }

    // we close the files
    fclose(file);
    fclose(tempFile);

    // and if the credentials are not changed, we print an error message and return
    if (!credentialsChanged) {
        remove("temp.txt");
        printf("Failed to change credentials. Invalid username or password.\n");
        return;
    }

    // otherwise, we remove the old file and rename the temporary file to the old file
    remove(filename);
    rename("temp.txt", filename);

    printf("\nCredentials changed successfully.\n");
}

