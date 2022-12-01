/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 6
 * Tee.c - 
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int appendMode = 0;      // Append off by default.
  char *fileNames[argc];   // Name of files.
  int fileNamesIndex = 0;  // Index of fileNames.

  // For every argument.
  for (int i = 1; i < argc; ++i) {
    char *argvi = argv[i];

    // If argvi is a flag.
    if (argvi[0] == '-') {
      int argviSize = strlen(argvi);

      // For every flag in argvi.
      for (int j = 1; j < argviSize; ++j) {
        switch (argvi[j]) {
          // Append flag.
          case 'A':
          case 'a':
            appendMode = 1;
            break;
          // Invalid flag.
          default:
            printf("tee: invalid option -- \'%c\'\n", argvi[j]);
            return 1;
            break;
        }
      }
    // Not a flag, its a file then.
    } else {
      fileNames[fileNamesIndex] = argvi;
      ++fileNamesIndex;
    }
  }

  // Obtained every data needed.
  
  return 0;
}
