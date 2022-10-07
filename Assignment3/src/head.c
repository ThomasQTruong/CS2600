/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 3
 * Replication of head UNIX command.
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char printFlag = 'n';    // default is n.
  int amountToPrint = 10;  // default is 10 lines.
  int printHeaders = 0;    // -1 = never, 0 = default, 1 = always.
  char *fileNames[argc - 1];
  int fileIndex = 0;

  // Get arguments.
  for (int i = 1; i < argc; ++i) {
    char *argv_i = argv[i];
    // Flag notation spotted.
    if (argv_i[0] == '-') {
      // Size of ith argument (amount of char in argument).
      int argv_i_size = strlen(argv_i);
      // Multi-flag; go through every char in ith argument.
      for (int j = 1; j < argv_i_size; ++j) {
        // Set proper values based on flag(s).
        switch (argv_i[j]) {
          case 'n':
          case 'N':
          {
            printFlag = 'n';
            int value = 0;
            // Get number if exists for -n flag.
            if (j + 1 < argv_i_size) {
              for (int k = j + 1, start = k; k < argv_i_size; ++k) {
                value *= 10;
                // Is not a number; print error and stop.
                if (argv_i[k] < 48 || argv_i[k] > 57) {
                  printf("head: invalid number of lines: \'");
                  // Get the number of lines that caused an error.
                  for (int e = start; e < argv_i_size; ++e) {
                    printf("%c", argv_i[e]);
                  }
                  printf("\'\n");
                  return -1;
                }
                value += argv_i[k] - 48;  // Convert ascii to regular int.
              }
              j = argv_i_size;
            } else if (i + 1 < argc) {
              // Space between -n flag and number.
              char *nextArg = argv[i + 1];
              int nextArg_size = strlen(nextArg);
              for (int p = 0; p < nextArg_size; ++p) {
                value *= 10;
                // Is not a number; print error and stop.
                if (nextArg[p] < 48 || nextArg[p] > 57) {
                  printf("head: invalid number of lines: \'%s\'\n", nextArg);
                  return -1;
                }
                value += nextArg[p] - 48;  // Convert ascii to regular int.
                ++i;
              }
            }
            amountToPrint = value;
            break;
          }
          case 'c':
          case 'C':
          {
            printFlag = 'c';
            int value = 0;
            // Get number if exists for -n flag.
            if (j + 1 < argv_i_size) {
              for (int k = j + 1, start = k; k < argv_i_size; ++k) {
                value *= 10;
                // Is not a number; print error and stop.
                if (argv_i[k] < 48 || argv_i[k] > 57) {
                  printf("head: invalid number of bytes: \'");
                  // Get the number of bytes that caused an error.
                  for (int e = start; e < argv_i_size; ++e) {
                    printf("%c", argv_i[e]);
                  }
                  printf("\'\n");
                  return -1;
                }
                value += argv_i[k] - 48;  // Convert ascii to regular int.
              }
              j = argv_i_size;
            } else if (i + 1 < argc) {
              // Space between -n flag and number.
              char *nextArg = argv[i + 1];
              int nextArg_size = strlen(nextArg);
              for (int p = 0; p < nextArg_size; ++p) {
                value *= 10;
                // Is not a number; print error and stop.
                if (nextArg[p] < 48 || nextArg[p] > 57) {
                  printf("head: invalid number of bytes: \'%s\'\n", nextArg);
                  return -1;
                }
                value += nextArg[p] - 48;  // Convert ascii to regular int.
                ++i;
              }
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
            printf("head: invalid trailing option -- %c\n", argv_i[j]);
            return -1;
        }
      }
    } else {
      // Not flag? Should be file names then.
      fileNames[fileIndex] = argv_i;
      ++fileIndex;
    }
  }

  printf("%c | %d | %d\n", printFlag, amountToPrint, printHeaders);
  for (int i = 0; i < fileIndex; ++i) {
    printf("%s\n", fileNames[i]);
  }

  return 0;
}
