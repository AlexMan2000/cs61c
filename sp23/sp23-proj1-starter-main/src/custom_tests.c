#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) {
  return x > 42;
}

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  // Head should not be tail
  char e1 = 'W';
  bool output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'A';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'S';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'D';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }


  // Body should not be tail
  e1 = '<';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'v';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = '>';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = '^';
  output = is_tail(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  // Tail should be tail
  e1 = 'w';
  output = is_tail(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 'a';
  output = is_tail(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 's';
  output = is_tail(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 'd';
  output = is_tail(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  // Head should be head
  char e1 = 'W';
  bool output = is_head(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 'A';
  output = is_head(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 'S';
  output = is_head(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }

  e1 = 'D';
  output = is_head(e1);
  if(!assert_true("output_test_4.1", output)) {
    return false;
  }


  // Body should not be tail
  e1 = '<';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'v';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = '>';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = '^';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  // Tail should not be head
  e1 = 'w';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'a';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 's';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  e1 = 'd';
  output = is_head(e1);
  if(!assert_false("output_test_4.1", output)) {
    return false;
  }

  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  char* test_char_arr = SNAKE;
  for (int i = 0; i < strlen(test_char_arr); i++) {
    if (!assert_true("output_test_4.1", is_snake(test_char_arr[i]))) {
      return false;
    }
  }

  
  char* test = "1238zoutuorut";
  for (int i = 0; i < strlen(test); i++) {
    if (!assert_false("output_test_4.1", is_snake(test[i]))) {
      return false;
    }
  }
  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  char e1 = '<';
  char output = body_to_tail(e1);
  if(!assert_equals_char("output_test_4.1", 'a', output)) {
    return false;
  }

  e1 = 'v';
  output = body_to_tail(e1);
  if(!assert_equals_char("output_test_4.1", 's', output)) {
    return false;
  }

  e1 = '>';
  output = body_to_tail(e1);
  if(!assert_equals_char("output_test_4.1", 'd', output)) {
    return false;
  }

  e1 = '^';
  output = body_to_tail(e1);
  if(!assert_equals_char("output_test_4.1", 'w', output)) {
    return false;
  }
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  char e1 = 'W';
  char output = head_to_body(e1);
  if(!assert_equals_char("output_test_4.1", '^', output)) {
    return false;
  }

  e1 = 'A';
  output = head_to_body(e1);
  if(!assert_equals_char("output_test_4.1", '<', output)) {
    return false;
  }

  e1 = 'S';
  output = head_to_body(e1);
  if(!assert_equals_char("output_test_4.1", 'v', output)) {
    return false;
  }

  e1 = 'D';
  output = head_to_body(e1);
  if(!assert_equals_char("output_test_4.1", '>', output)) {
    return false;
  }
  return true;
}

bool test_get_next_row() {
  // TODO: Implement this function.
  unsigned int current_row = 1;
  char* test_string_1 = "vsS";
  char* test_string_2 = "^wW";
  char* test_string_3 = "adAD<>x";

  for (int i = 0; i < strlen(test_string_1); i++) {
    unsigned int output = get_next_row(current_row, test_string_1[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 2, output)) {
      return false;
    }
  }

  for (int i = 0; i < strlen(test_string_2); i++) {
    unsigned int output = get_next_row(current_row, test_string_2[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 0, output)) {
      return false;
    }
  }

  for (int i = 0; i < strlen(test_string_3); i++) {
    unsigned int output = get_next_row(current_row, test_string_3[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 1, output)) {
      return false;
    }
  }

  return true;
}

bool test_get_next_col() {
  // TODO: Implement this function.
  unsigned int current_col = 1;
  char* test_string_1 = ">dD";
  char* test_string_2 = "<aA";
  char* test_string_3 = "wsWS^v";

  for (int i = 0; i < strlen(test_string_1); i++) {
    unsigned int output = get_next_col(current_col, test_string_1[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 2, output)) {
      return false;
    }
  }

  for (int i = 0; i < strlen(test_string_2); i++) {
    unsigned int output = get_next_col(current_col, test_string_2[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 0, output)) {
      return false;
    }
  }

  for (int i = 0; i < strlen(test_string_3); i++) {
    unsigned int output = get_next_col(current_col, test_string_3[i]);
    if (!assert_equals_unsigned_int("output_test_4.1", 1, output)) {
      return false;
    }
  }

  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
