// #include "functions.h"
#include "functions.c"
#include <stdio.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define USERS "users.txt"
#define MAX_ATTEMPTS 3

int main() {
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  int success = 0;

  success = attemptLogin(MAX_ATTEMPTS, username, password, USERS);

  if (success) {
    printf("Welcome, %s!\n", username);
  } else {
    printf("Max attempts reached. Access denied.\n");
  }

  return 0;
}
