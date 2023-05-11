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
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

// function that compares two words if they are similar
int wordCompare(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    // If one string is longer than the other
    if (str1[i] != '\0') {
        return 1;
    } else if (str2[i] != '\0') {
        return -1;
    }

    return 0;  // Both strings are equal
}

// function that cleans up the word from the new line character
void wordCleanUp(char *str) {
  int length = wordLength(str);
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
}

// function that checks the credentials of the user if they are valid by comparing them to the users file
int checkCredentials(User *user, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char stored_username[MAX_USERNAME_LENGTH];
        char stored_password[MAX_PASSWORD_LENGTH];
        char stored_name[MAX_NAME_LENGTH];

        sscanf(line, "%s %s %[^\n]", stored_username, stored_password, stored_name);

        if (wordCompare(user->username, stored_username) == 0 &&
            wordCompare(user->password, stored_password) == 0) {
            found = 1;
            strncpy(user->name, stored_name, MAX_NAME_LENGTH);
            break;
        }
    }

    fclose(file);

    return found;
}

// function that attempts to login the user by asking for their username and password 
int attemptLogin(int maxAttempts, User *user, const char *filename) {
    int attempts = 0;

    printf("\nWelcome to the login page for student management platfrom (SMP). All modifications directly impact the students file just like a real database (without the need for a save file option). Permission was aquirred from the professor to impliment it this way.\n\n");

    while (attempts < maxAttempts) {
        printf("Enter your username: ");
        fgets(user->username, MAX_USERNAME_LENGTH, stdin);
        wordCleanUp(user->username);

        printf("Enter your password: ");
        fgets(user->password, MAX_PASSWORD_LENGTH, stdin);
        wordCleanUp(user->password);

        if (checkCredentials(user, filename)) {
            return 1;
        } else {
            attempts++;
            printf("Invalid credentials. Attempts remaining: %d\n",
                   maxAttempts - attempts);
        }
    }

    return 0;
}

// function that validates the password of the user, making sure it has all the necessary requirements
int validatePassword(const char *password) {
    int length = wordLength(password);

    // Check password length
    if (length < 6 || length > 12) {
        printf("Invalid password length. Password must contain 6-12 characters.\n");
        return 0;
    }

    int hasLower = 0;
    int hasUpper = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    // Check password for required character types
    for (int i = 0; i < length; i++) {
        if (islower(password[i]))
            hasLower = 1;
        else if (isupper(password[i]))
            hasUpper = 1;
        else if (isdigit(password[i]))
            hasDigit = 1;
        else if (ispunct(password[i]))
            hasSpecial = 1;
    }

    if (!(hasLower && hasUpper && hasDigit && hasSpecial)) {
        printf("Invalid password format. Password must contain at least one lowercase letter, one uppercase letter, one digit, and one special character.\n");
        return 0;
    }

    return 1;
}

// function that changes the credentials of the user, either the username, password or both
void changeCredentials(User *user, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char currentPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newUsername[MAX_USERNAME_LENGTH];

    printf("Enter your current password: ");
    fgets(currentPassword, MAX_PASSWORD_LENGTH, stdin);
    wordCleanUp(currentPassword);

    if (wordCompare(user->password, currentPassword) != 0) {
        printf("Invalid current password. Please try again.\n");
        fclose(file);
        return;
    }

    int changeUsername = 0;
    int changePassword = 0;

    printf("Choose an option:\n");
    printf("1. Change username\n");
    printf("2. Change password\n");
    printf("3. Change both username and password\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear the newline character from the input buffer

    if (choice == 1 || choice == 3) {
        printf("Enter your new username: ");
        fgets(newUsername, MAX_USERNAME_LENGTH, stdin);
        wordCleanUp(newUsername);

        if (wordCompare(user->username, newUsername) == 0) {
            printf("New username is the same as the current username.\n");
            fclose(file);
            return;
        }

        changeUsername = 1;
    }

    if (choice == 2 || choice == 3) {
        printf("Enter your new password: ");
        fgets(newPassword, MAX_PASSWORD_LENGTH, stdin);
        wordCleanUp(newPassword);

        if (wordCompare(user->password, newPassword) == 0) {
            printf("New password is the same as the current password.\n");
            fclose(file);
            return;
        }

        if (!validatePassword(newPassword)) {
            fclose(file);
            return;
        }

        changePassword = 1;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int credentialsChanged = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char stored_username[MAX_USERNAME_LENGTH];
        char stored_password[MAX_PASSWORD_LENGTH];
        char stored_name[MAX_NAME_LENGTH];

        sscanf(line, "%s %s %[^\n]", stored_username, stored_password, stored_name);

        if (wordCompare(user->username, stored_username) == 0 &&
            wordCompare(user->password, stored_password) == 0) {
            if (changeUsername) {
                strncpy(stored_username, newUsername, MAX_USERNAME_LENGTH);
                strncpy(user->username, newUsername, MAX_USERNAME_LENGTH);
                        }
            
            if (changePassword) {
                strncpy(stored_password, newPassword, MAX_PASSWORD_LENGTH);
                strncpy(user->password, newPassword, MAX_PASSWORD_LENGTH);
            }
            
            credentialsChanged = 1;
        }

        fprintf(tempFile, "%s %s %s\n", stored_username, stored_password, stored_name);
    }

    fclose(file);
    fclose(tempFile);

    if (!credentialsChanged) {
        remove("temp.txt");
        printf("Failed to change credentials. Invalid username or password.\n");
        return;
    }

    remove(filename);
    rename("temp.txt", filename);

    printf("\nCredentials changed successfully.\n");
}

