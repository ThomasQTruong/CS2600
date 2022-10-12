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

int charIsInt(char toCheck);
char toLower(char c);
int cArrayToInt(char *cArray);

int main(int argc, char *argv[]) {
  char printFlag = 'n';    // default is n.
  int amountToPrint = 10;  // default is 10 lines.
  int printHeaders = 0;    // -1 = never, 0 = default, 1 = always.
  char *fileNames[argc - 1];
  int fileIndex = 0;

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
          case 'n':
          case 'N':
          case 'c':
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
            } else {
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
          case 'q':
          case 'Q':
            printHeaders = -1;
            break;
          case 'v':
          case 'V':
            printHeaders = 1;
            break;
          default:
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
    // Failed to open file; print and exit.
    if (fileDescriptor == -1) {
      printf("head: cannot open \'%s\' for reading: ", fileNames[i]);
      printf("No such file or directory\n");
      return -1;
    }
    // File name given was a directory; print and exit.
    if (opendir(fileNames[i]) != NULL) {
      printf("head: error reading \'%s\': Is a directory\n", fileNames[i]);
      return -1;
    }
    // Everything is fine.
    struct utmp currentFile;
    while (read(fileDescriptor, &currentFile, 7)) {
      printf("%s\n", currentFile.ut_line);
    }
  }

  //
  // FOR DEBUGING: Print information
  printf("%c | %d | %d\n", printFlag, amountToPrint, printHeaders);
  for (int i = 0; i < fileIndex; ++i) {
    printf("%s\n", fileNames[i]);
  }
  //

  return 0;
}

int charIsInt(char toCheck) {
  return toCheck > 47 && toCheck < 58;
}

char toLower(char c) {
  if (c > 64 && c < 91) {
    return c + 32;
  }
  return c;
}

int cArrayToInt(char *cArray) {
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
