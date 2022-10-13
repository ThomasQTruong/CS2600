/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 3
 * Replication of head UNIX command.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <dirent.h>

// Checks whether a char is an int.
int charIsInt(char toCheck);
// Converts an uppercase char to lowercase.
char toLower(char c);
// Converts a char array (string) into an int.
int cArrayToInt(const char *cArray);

int main(int argc, char *argv[]) {
  char printFlag = 'n';       // default is n.
  int amountToPrint = 10;     // default is 10 lines.
  int printHeaders = 0;       // -1 = never, 0 = default, 1 = always.
  char *fileNames[argc - 1];  // Name of files.
  int fileIndex = 0;          // Points to the next array slot in fileNames.

  // Get arguments.
  for (int i = 1; i < argc; ++i) {
    char *argvI = argv[i];
    // Flag notation spotted.
    if (argvI[0] == '-') {
      // Size of ith argument (amount of char in argument).
      int argvISize = strlen(argvI);
      // Multi-flag; go through every char in ith argument.
      for (int j = 1; j < argvISize; ++j) {
        // Set proper values based on flag(s).
        switch (argvI[j]) {
          case 'n':  // Line number flag.
          case 'N':
          case 'c':  // Characters/bytes flag.
          case 'C':
          {
            // Set flag variable.
            printFlag = toLower(argvI[j]);

            // Determine where the line/byte number is.
            char *cArray = NULL;
            if (j + 1 < argvISize) {  // -flag#
              cArray = &argvI[j + 1];
            } else if (i + 1 < argc) {  // -flag #
              cArray = argv[i + 1];
              // Skip next argument since it is the line/byte number.
              ++i;
            } else {  // ERROR: no no argument given.
              printf("head: option requires an argument -- \'%c\'\n", argvI[j]);
              return -1;
            }

            // Check for negatives.
            int negative = 0;
            if (cArray[0] == '-') {
              cArray++;
              negative = 1;
            }

            int value = cArrayToInt(cArray);
            // Not a valid int, print error msg and exit.
            if (value == -1) {
              printf("head: invalid number of ");
              if (printFlag == 'c') {  // Bytes flag.
                printf("bytes");
              } else {  // Lines flag.
                printf("lines");
              }
              printf(": \'%s\'\n", cArray);
              return -1;
            }
            j = argvISize;
            // Was a negative.
            if (negative == 1) {
              value *= -1;
            }
            amountToPrint = value;
            break;
          }
          case 'q':  // Quiet flag (do not print file names).
          case 'Q':
            printHeaders = -1;
            break;
          case 'v':  // Verbose flag (print all file names).
          case 'V':
            printHeaders = 1;
            break;
          default:  // ERROR: not valid option given.
            printf("head: invalid trailing option -- %c\n", argvI[j]);
            return -1;
        }
      }
    } else {
      // Not flag? Should be file names then.
      fileNames[fileIndex] = argvI;
      ++fileIndex;
    }
  }
  // No file given; print error and exit.
  if (fileIndex == 0) {
    printf("head: no file given\n");
    return -1;
  }

  // For every file.
  for (int i = 0; i < fileIndex; ++i) {
    // Get index of file; -1 = failed.
    int fileDescriptor = open(fileNames[i], O_RDONLY);
    // ERROR: Failed to open file; print and exit.
    if (fileDescriptor == -1) {
      printf("head: cannot open \'%s\' for reading: ", fileNames[i]);
      printf("No such file or directory\n");
      return -1;
    }
    // ERROR: File name given was a directory; print and exit.
    if (opendir(fileNames[i]) != NULL) {
      printf("head: error reading \'%s\': Is a directory\n", fileNames[i]);
      return -1;
    }

    // Everything is fine; print file name(s)?
    if (printHeaders == 1 || (printHeaders == 0 && fileIndex > 1)) {
      printf("==> %s <==\n", fileNames[i]);
    }

    // Print file content.
    char fileChar;
    int cursor = 0;
    if (printFlag == 'c') {  // Print characters.
      while (read(fileDescriptor, &fileChar, 1) && cursor < amountToPrint) {
        printf("%c", fileChar);
        ++cursor;
      }
    } else {  // Print lines.
      while (read(fileDescriptor, &fileChar, 1) && cursor < amountToPrint) {
        printf("%c", fileChar);
        if (fileChar == '\n') {
          ++cursor;
        }
      }
    }

    // Skips line for next file.
    if (printHeaders != -1 && i < fileIndex - 1) {
      printf("\n");
    }
  }

  /*
  // FOR DEBUGING: Print information
  printf("%c | %d | %d\n", printFlag, amountToPrint, printHeaders);
  for (int i = 0; i < fileIndex; ++i) {
    printf("%s\n", fileNames[i]);
  }
  */

  return 0;
}


/**
 * Checks whether a char is an int.
 * 
 * @param toCheck - the char to check if it is an int.
 * @return int - 1 = true, 0 = false.
 */ 
int charIsInt(char toCheck) {
  printf("%d", toCheck > 47 && toCheck < 58);
  return toCheck > 47 && toCheck < 58;
}


/**
 * Converts an uppercase char to lowercase.
 * If char is not valid, it is left alone and returned.
 * 
 * @param c - the char to convert.
 * @return char - the lowercased char/untouched char (if invalid).
 */
char toLower(char c) {
  if (c > 64 && c < 91) {
    return c + 32;
  }
  return c;
}


/**
 * Converts a char array (string) into an int.
 * 
 * @param *cArray - points to the char array to convert.
 * @return int - the converted char or -1 if failed.
 */
int cArrayToInt(const char *cArray) {
  int value = 0;
  int cArraySize = strlen(cArray);
  // Nothing to convert!
  if (cArraySize == 0) {
    return -1;
  }
  // For every char.
  for (int i = 0; i < cArraySize; ++i) {
    value *= 10;
    // Not an int.
    if (!charIsInt(cArray[i])) {
      return -1;
    }
    value += cArray[i] - 48;  // Convert ascii to regular int.
  }
  return value;
}
