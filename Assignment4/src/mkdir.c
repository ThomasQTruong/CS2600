/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 4
 * Replication of mkdir UNIX command.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// Counts the amount of times a char appears in string.
int countCharInString(const char *s, const char target);

int main(int argc, char *argv[]) {
  char *dirNames[argc - 1];   // Array that contains the directory names.
  int dirIndex = 0;           // Index in array, dirNames.
  int pFlag = 0;              // p flag (-p, parents).
  int vFlag = 0;              // v flag (-v, verbose).

  // For every argument in argv (Check for flags/names).
  for (int i = 1; i < argc; ++i) {
    char *argvI = argv[i];
    // If argument is a flag.
    if (argvI[0] == '-') {
      int argvISize = strlen(argvI);
      for (int j = 0; j < argvISize; ++j) {
        switch (argvI[j]) {
          // p flag (parents).
          case 'p':
          case 'P':
            pFlag = 1;
          break;
          // v flag (verbose).
          case 'v':
          case 'V':
            vFlag = 1;
          break;
        }
      }
    } else {  // Not a flag, is folder name.
      dirNames[dirIndex] = argv[i];
      ++dirIndex;
    }
  }

  // For every folder name.
  for (int i = 0; i < dirIndex; ++i) {
    int createDir = mkdir(dirNames[i], S_IRWXU);
    // An error occured when creating directory.
    if (errno != 0 && pFlag == 0) {
      // Print error message.
      printf("mkdir: cannot create directory \'%s\': %s\n",
              dirNames[i], strerror(errno));
    } else if (errno == 0 && vFlag == 1) {
      // Error did not occur and verbose flag is true.
      printf("mkdir: created directory \'%s\'\n", dirNames[i]);
    }

    // No parent(s) error and -p flag used.
    if (errno == 2 && pFlag == 1) {
      // Create directory(s) if needed.
      // Dynamically allocate space to fullPath and currentPath.
      char *fullPath = dirNames[i];
      char *currentPath = (char*)calloc(strlen(dirNames[i]) + 1, sizeof(char));

      // Stores the dir extracted.
      char *bufferStr = NULL;

      // Amount of times to repeat loop.
      int repeatAmount = countCharInString(fullPath, '/');

      // Create every folder needed.
      while (repeatAmount >= 0) {
        bufferStr = strtok_r(fullPath, "/", &fullPath);
        strcat(currentPath, bufferStr);
        strcat(currentPath, "/");
        int success = mkdir(currentPath, S_IRWXU);
        if (success == 0 && vFlag == 1) {  // Succeded (-1 is fail).
          printf("mkdir: created directory \'%s\'\n", currentPath);
        }
        repeatAmount--;
      }

      // Free the dynamically allocated memory.
      free(currentPath);
    }
  }

  return 0;
}



/**
 * Counts the amount of times a char appears in string.
 * 
 * @param s - the string to check.
 * @param target - the char to count.
 * @return int - the count.
 */
int countCharInString(const char *s, const char target) {
  int count = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == target) {
      ++count;
    }
  }
  return count;
}
