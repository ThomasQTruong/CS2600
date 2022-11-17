/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 5
 * Timeout.c - Add more to this.
 */

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int isInt(char *toCheck);
int stringToInt(char *toConvert);

int main(int argc, char *argv[]) {
  int timeoutSeconds = 10;  // Seconds till timeout (default: 10).
  char *fileName = NULL;    // Name of file.
  int verbose = 0;          // Verbose flag.

  // For every argument (skip ./timeout).
  for (int i = 1; i < argc; ++i) {
    char* argvi = argv[i];

    // Possible flag.
    if (argvi[0] == '-') {
      int argviSize = strlen(argvi);  // Get size.

      // For every character in flag.
      for (int j = 1; j < argviSize; ++j) {
        switch (argvi[j]) {
          // Verbose flag.
          case 'v':
          case 'V':
            verbose = 1;
            break;
          // Timeout seconds flag.
          case 'T':
          case 't':
            // N on same index (-tN).
            if (j + 1 < argviSize) {
              // N is an int, store in timeoutSeconds.
              if (isInt(&(argvi[j + 1])) == 1) {
                timeoutSeconds = stringToInt(&(argvi[j + 1]));
                j = argviSize;

              // ERROR: Time is invalid.
              } else {
                printf("timeout: invalid number of seconds: \'%s\'\n",
                        &(argvi[j + 1]));
                return -1;
              }

            // N should be on the next element (-t N).
            } else if (i + 1 < argc) {
              // If the next argument is an int.
              if (isInt(argv[i + 1]) == 1) {
                timeoutSeconds = stringToInt(argv[i + 1]);
                ++i;  // Skip next argument since it was used for time.
              } else {  // ERROR: Time is invalid.
                printf("timeout: invalid number of seconds: \'%s\'\n",
                        argv[i + 1]);
                return -1;
              }

            // No other argment was given. (-t)
            } else {
              printf("timeout: option requires an argument --\'%c\'\n",
                      argvi[1]);
              return -1;
            }
            break;
          // Invalid flag.
          default:
            printf("timeout: invalid option -- \'%c\'\n", argvi[j]);
            return 1;
        }
      }
    } else {
      // Not a flag, should be file name (only keep latest file).
      fileName = argv[i];
    }
  }

  // Obtained every information needed; begin program.
  if (fileName == NULL) {  // No file given.
    printf("timeout: no file given\n");
    return -1;
  }

  // Create stat buffer and obtain the stats of fileName.
  struct stat sb;
  int success = stat(fileName, &sb);
  // File not found.
  if (success == -1) {
    printf("timeout: file not found\n");
    return 1;
  }

  // Get process ID.
  int pid = getpid();

  // Get current modifcation time for file.
  time_t modificationTime = sb.st_mtime;

  // Sleep timeoutSeconds times.
  for (int counter = 0; counter < timeoutSeconds; ++counter) {
    sleep(1);

    // Reobtain file stats.
    success = stat(fileName, &sb);
    // File not found.
    if (success == -1) {
      printf("timeout: file not found\n");
      return 1;
    }

    // Print time and counter if verbose flag is used.
    if (verbose == 1) {
      printf("%sCounter: %i\n", ctime(&modificationTime), counter);
    }

    // Time changed; file modified - resleep timeoutSeconds times.
    if (modificationTime != sb.st_mtime) {
      counter = -1;
      modificationTime = sb.st_mtime;
    }
  }
  // Slept for too long! Kill process.
  kill(pid, SIGKILL);

  return 0;
}


// Checks whether the string is an int.
int isInt(char *toCheck) {
  int toCheckSize = strlen(toCheck);

  // For every digit in toCheck.
  for  (int i = 0; i < toCheckSize; ++i) {
    // Is NOT a digit.
    if (toCheck[i] < 48 || toCheck[i] > 57) {
      return 0;
    }
  }

  // Is a digit.
  return 1;
}


// Converts string to integer.
int stringToInt(char *toConvert) {
  int toConvertSize = strlen(toConvert);
  int converted = 0;  // converted value of toConvert.

  // For every digit in toConvert.
  for (int i = 0; i < toConvertSize; ++i) {
    converted *= 10;  // Shift digit(s) left.

    // Converts to int and add to converted.
    converted += (toConvert[i] - 48);
  }

  return converted;
}