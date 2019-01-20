#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Given 2 numbers, returns the one that is greater in value
#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
// Maximum length for an array
#define BUF_SIZ 1024

// Reverses a string
// source: https://people.cs.umu.se/isak/snippets/strrev.c
char *strrev(char *str) {
  char *p1, *p2;

  if (!str || !*str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}

// Converts a char to an int
int char_to_int(char ch) {
  return ch - '0';
}

// Converts an int to a char
char int_to_char(int i) {
  return i + '0';
}

// Error checking for valid number and print error messages
void check_valid_int(char *str, int len, int max_len) {
  // Check if any of the numbers' length exceed the maximum length defined
  if (len > max_len) {
    printf("Error: Number exceeds maximum character length of %d.\n", max_len);
    exit(EXIT_FAILURE);
  }

  // Check if numbers received from input are valid decimal numbers
  for (int i = 0; i < len; i++) {
    if (!isdigit(str[i])) {
      printf("Error: Invalid integer.\n");
      exit(EXIT_FAILURE);
    }
  }
}

void main() {
  // Create arrays for storing the 2 numbers and the result
  // NOTE:
  // 1. Using malloc enables us to allocate a large amount of memory for the array (since the numbers will be big)
  // 2. The size of allocated memory will be BUF_SIZ + 2 (we must include '\0' and '\n' characters from user inputs)
  // 3. The maximum length for the 2 number arrays will be 1 less than the maximum length for the result array (the result will have 1 extra slot for the final carry)
  // 4. All user input numbers will be strings
  char *num_1 = (char *) malloc(sizeof(char) * (BUF_SIZ + 2));
  char *num_2 = (char *) malloc(sizeof(char) * (BUF_SIZ + 2));
  int *result = (int *) malloc(sizeof(int) * (BUF_SIZ + 3));

  // Error checking for memory allocation
  if (!num_1 || !num_2 || !result) {
    printf("Error: Could not allocate memory.");
    exit(EXIT_FAILURE);
  }

  int num_1_length, num_2_length;
  
  // Prompt user to enter a number and store it in an array
  // NOTE: BUF_SIZ + 2 for the extra '\0' and '\n' characters from input
  printf("Enter First Number: ");
  fgets(num_1, BUF_SIZ + 2, stdin);
  // Remove newline characters
  num_1[strcspn(num_1, "\r\n")] = 0;
  // Store the lengths of 2 numbers
  num_1_length = strlen(num_1);
  // Check for invalid input of integers
  check_valid_int(num_1, num_1_length, BUF_SIZ);

  // Prompt user to enter a number and store it in an array
  // NOTE: BUF_SIZ + 2 for the extra '\0' and '\n' characters from input
  printf("Enter Second Number: ");
  fgets(num_2, BUF_SIZ + 2, stdin);
  // Remove newline characters
  num_2[strcspn(num_2, "\r\n")] = 0;
  // Store the lengths of 2 numbers
  num_2_length = strlen(num_2);
  // Check for invalid input of integers
  check_valid_int(num_2, num_2_length, BUF_SIZ);
  
  // Reverse 2 number arrays (we are going add them from the ones to tens, etc.)
  strrev(num_1);
  strrev(num_2);

  // Define a variable to set the 'carry' part of summing 2 numbers
  int carry = 0;

  // Get the maximum length from the 2 number arrays so we safely loop through them
  int max_length = num_1_length > num_2_length ? num_1_length : num_2_length;

  int i, j, sum;

  for (i = 0; i < max_length; i++) {
    // Add 2 numbers
    if (num_1_length == num_2_length || (i < num_1_length && i < num_2_length)) {
      sum = carry + char_to_int(num_1[i]) + char_to_int(num_2[i]);
    }
    // Add the rest of the second number
    else if (i >= num_1_length) { 
      sum = carry + char_to_int(num_2[i]);
    }
    // Add the rest of the first number
    else if (i >= num_2_length) {
      sum = carry + char_to_int(num_1[i]);
    }

    // Store the sum and set the carry
    result[i] = int_to_char(sum % 10);
    carry = sum / 10;
  }

  // If we have a left-over carry, add it to the front (last in reversed array) of the final result
  if (carry > 0) {
    result[i] = int_to_char(carry);
    i++;
  }

  // Print the result
  printf("Result: ");
  for (j = i - 1; j >= 0; j--) {
    printf("%c", result[j]);
  }
  printf("\n");

  // Free malloc'd memory after we have finished
  free(num_1);
  free(num_2);
  free(result);

  exit(EXIT_SUCCESS);
}
