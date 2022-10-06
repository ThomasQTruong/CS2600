/*
 * Exercise1.c
 *
 * Copyright (c), 2022 Thomas Truong
 */

#include <stdio.h>

int main(void) {
  int i, j = 1;
  float f1, f2 = 1.5;

  i = (int) f2;  // 1
  f1 = i + j;    // 1 + 1 = 2.0
  printf("%f\n", f1);

  f1 = f2 + j;   // 1.5 + 1 = 2.5
  printf("%f\n", f1);
}
