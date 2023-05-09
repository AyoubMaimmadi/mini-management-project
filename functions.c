// #include "functions.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_LINE_LENGTH (MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2)

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;


size_t wordLength(const char *str) {
  size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

int wordCompare(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str1[i] == str2[i]) {
    i++;
  }
  return str1[i] - str2[i];
}

void cleanUp(char *str) {
  size_t length = wordLength(str);
  if (length > 0 && str[length - 1] == '\n') {
    str[length - 1] = '\0';
  }
}

int checkCredentials(const User *user, const char *filename) {
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

        sscanf(line, "%s %s", stored_username, stored_password);

        if (wordCompare(user->username, stored_username) == 0 &&
            wordCompare(user->password, stored_password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    return found;
}

int attemptLogin(int maxAttempts, User *user, const char *filename) {
    int attempts = 0;

    while (attempts < maxAttempts) {
        printf("Enter your username: ");
        fgets(user->username, MAX_USERNAME_LENGTH, stdin);
        cleanUp(user->username);

        printf("Enter your password: ");
        fgets(user->password, MAX_PASSWORD_LENGTH, stdin);
        cleanUp(user->password);

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