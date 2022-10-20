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

int main(int argc, char *argv[]) {
  char *folderNames[argc - 1];
  int folderIndex = 0;

  // For every argument in argv.
  for (int i = 1; i < argc; ++i) {
    // If argument is a flag.
    if ((argv[i])[0] == '-') {
    } else {  // Not a flag, is folder name.
      folderNames[folderIndex] = argv[i];
      ++folderIndex;
    }
  }

  for (int i = 0; i < folderIndex; ++i) {
    DIR *dirPtr = opendir(folderNames[i]);
    if (dirPtr == NULL) {
      int createDir = mkdir(folderNames[i], S_IRWXU);
    } else {
      printf("Already exists!\n");
    }
  }

  return 0;
}
