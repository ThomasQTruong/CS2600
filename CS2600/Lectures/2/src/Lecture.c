/*
 * Lecture.c
 * 
 * Copyright (c) 2022, Thomas Truong
 */

#include <stdio.h>

void print1();
void print2();

struct st {
  int a;
  char ch;
};

int main(void) {
  print2();

  return 0;
}

void print1() {
  char ch = 'c';
  char *chptr = &ch;
  int i = 20;
  int *intptr = &i;
  float f = 1.20000;
  float *fptr = &f;
  char *ptr = "I am a string";

  printf("\n[%c] [%d] [%f] [%c] [%s]\n", *chptr, *intptr, *fptr, *ptr, ptr);
}

void print2() {
  struct st obj;
  struct st *stobj = &obj;

  stobj->a = 5;
  stobj->ch = 'a';

  printf("\n[%d] [%c]\n", stobj->a, stobj->ch);
}