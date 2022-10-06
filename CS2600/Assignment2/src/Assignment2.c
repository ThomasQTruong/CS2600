/*
 * Thomas Truong
 * Bronco ID: 014426906
 * CS2600, Fall 2022
 * Programming Assignment 2
 * Menu-driven database that stores three quantities for a single person.
 */

#include <stdio.h>

int main(void) {
  // User's option for menu.
  int option = 0;

  // The default value of age and points.
  const int UNKNOWN = -2029133647;

  // Data of a person.
  char name[256];
  int age = UNKNOWN;
  double points = UNKNOWN;

  // Repeat until user exits.
  do {
    // Display options.
    printf("[1] Enter a name.\n");
    printf("[2] Enter an age.\n");
    printf("[3] Enter amount of points.\n");
    printf("[4] Display data.\n");
    printf("[5] Clear data.\n");
    printf("[6] Exit program.\n");

    // Accept input.
    printf("Enter an option: ");
    scanf("%d", &option);

    if (option == 1) {
      // Get name.
      printf("Enter the name: ");
      scanf("%s", name);
    } else if (option == 2) {
      // Get the age.
      printf("Enter age: ");
      scanf("%d", &age);
    } else if (option == 3) {
      // Get points.
      printf("Enter the points per game: ");
      scanf("%lf", &points);
    } else if (option == 4) {
      // Display known data.
      printf("-Known Data-\n");
      if (name[0] != '\0') {
        // Name known; print.
        printf("Name: %s\n", name);
      }
      if (age != UNKNOWN) {
        // Age known; print.
        printf("Age: %d\n", age);
      }
      if (points != UNKNOWN) {
        // Points known; print.
        printf("Points per game: %f\n", points);
      }
    } else if (option == 5) {
      // Clear data.
      name[0] = '\0';
      age = UNKNOWN;
      points = UNKNOWN;
    } else if (option == 6) {
      // Exit program.
      printf("Good bye!\n");
    } else {
      // Invalid option.
      printf("ERROR: Invalid option! Please try again.\n");
    }
    printf("\n");
  } while (option != 6);

  return 0;
}
