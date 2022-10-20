/*
 * Copyright (c) 2022 [Thomas Truong]
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 4
 * Replication of mkdir UNIX command.
 */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int countCharInString(char *s, char target);

int main(int argc, char *argv[]) {
  char *dirNames[argc - 1];
  int dirIndex = 0;
  int pFlag = 0;

  // For every argument in argv.
  for (int i = 1; i < argc; ++i) {
    // If argument is a flag.
    if ((argv[i])[0] == '-') {
    } else {  // Not a flag, is folder name.
      dirNames[dirIndex] = argv[i];
      ++dirIndex;
    }
  }

  // For every folder name.
  for (int i = 0; i < dirIndex; ++i) {
    int createDir = mkdir(dirNames[i], S_IRWXU);
    // An error occured when creating directory.
    if (errno != 0) {
      // Print error message.
      printf("mkdir: cannot create directory \'%s\': %s\n",
              dirNames[i], strerror(errno));
    }
    printf("%i\n", errno);
    if (errno == 2) {  // Parent directory(s) doesnt exist.
      // Recursively create directory(s) if needed.
    }
  }

  return 0;
}

int countCharInString(char *s, char target) {
  int count = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == target) {
      ++count;
    }
  }
  return count;
}