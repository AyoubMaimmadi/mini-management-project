#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void cleanUp(char *str);
int checkCredentials(const char *username, const char *password,
                     const char *filename);
int attemptLogin(int maxAttempts, char *username, char *password,
                 const char *filename);

#endif
