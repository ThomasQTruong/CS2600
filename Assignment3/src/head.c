/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 3
 * Replication of head UNIX command.
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
  char printFlag = 'n';    // default is n.
  int amountToPrint = 10;  // default is 10 lines.
  int printHeaders = 0;    // -1 = never, 0 = default, 1 = always.

  // Get arguments.
  for (int i = 1; i < argc; ++i) {
    char *argv_i = argv[i];
    // Flag notation spotted.
    if (argv_i[0] == '-') {
      // Size of ith argument (amount of char in argument).
      int argv_i_size = sizeof(argv_i) / sizeof(argv_i[0]);
      // Multi-flag; go through every char in ith argument.
      printf("%s | %d\n", argv_i, sizeof(argv_i) / sizeof(char));
      for (int j = 1; j < argv_i_size; ++j) {
        // Set proper values based on flag(s).
        switch (argv_i[j]) {
          case 'n':
          case 'N':
          {
            printFlag = 'n';
            int value = 0;
            // Get number if exists for -n flag.
            for (int k = j + 1, start = j + 1; k < argv_i_size; ++k) {
              value *= 10;
              // Is not a number; print error and stop.
              if (argv_i[k] < 48 || argv_i[k] > 57) {
                printf("head: invalid number of lines: \'");
                // Get the number of lines that caused an error.
                for (int e = start; e < argv_i_size; ++e) {
                  printf("%d%c", e, argv_i[e]);
                }
                printf("\'\n");
                return -1;
              }
              value += argv_i[j] - 48;  // Convert ascii to regular int.
            }
            break;
          }
          case 'c':
          case 'C':
            printFlag = 'c';
            break;
          case 'q':
          case 'Q':
            printHeaders = -1;
            break;
          case 'v':
          case 'V':
            printHeaders = 1;
            break;
        }
      }
    }
  }

  printf("%c | %d | %d\n", printFlag, amountToPrint, printHeaders);

  return 0;
}
