/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 6
 * tee.c - replica of the tee command, but only supports -a flag.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>


// Handles the interrupt signal.
void sig_handler(int signo);


int main(int argc, char *argv[]) {
  int appendMode = 0;      // Append off by default.
  char *fileNames[argc];   // Name of files.
  int fileNamesIndex = 0;  // Index of fileNames.

  // If an error occured when an interruption signal was sent.
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    printf("tee: cannot catch SIGINT.\n");
  }

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
  // No file given; print error and exit.
  if (fileNamesIndex == 0) {
    printf("tee: no file given\n");
    return -1;
  }

  // Store file descriptors of every file.
  int fileDescriptors[fileNamesIndex];
  for (int i = 0; i < fileNamesIndex; ++i) {
    // Not append mode, open blank file in write only mode.
    if (appendMode == 0) {
      fileDescriptors[i] = open(fileNames[i], O_TRUNC | O_WRONLY
                                | O_CREAT, S_IRWXU);

    // Append mode, open file in append mode.
    } else {
      fileDescriptors[i] = open(fileNames[i], O_WRONLY | O_APPEND
                                | O_CREAT, S_IRWXU);
    }
  }

  // Get user input.
  char userInput;
  while (fgets(&userInput, 2, stdin)) {
    printf("%c", userInput);
    // Write to every file given.
    for (int i = 0; i < fileNamesIndex; ++i) {
      write(fileDescriptors[i], &userInput, 1);
    }
  }

  // Close every used file.
  for (int i = 0; i < fileNamesIndex; ++i) {
    close(fileDescriptors[i]);
  }

  return 0;
}


/**
 * Handles the interrupt signal.
 * 
 * @param signo - the signal ID.
 */
void sig_handler(int signo)
{
  if (signo == SIGINT) {
    // Skip line after signal pressed and exit.
    puts("");
    exit(1);
  }
}
