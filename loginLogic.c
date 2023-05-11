#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_LINE_LENGTH (MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2)

typedef struct {
    char name[MAX_NAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;



int wordLength(const char *str) {
  int length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

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


void wordCleanUp(char *str) {
  int length = wordLength(str);
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
}

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



int attemptLogin(int maxAttempts, User *user, const char *filename) {
    int attempts = 0;

    printf("Welcome to the login page for student management platfrom (SMP).\n\n");

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

