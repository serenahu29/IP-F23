//Serena Hu
//shu53
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

#define TEST_RESTRICTION_1 10
#define TEST_RESTRICTION_2 2
#define TEST_RESTRICTION_3 5
#define TEST_RESTRICTION_4 30

#define MAX_WORD_NUM 1024

void test_read_files() {
  
  FILE *tempFile = fopen("testInput", "w");
  if (tempFile == NULL) {
    fprintf(stderr,"Failed to create a temporary test file");
    exit(1);
  }

  const char *testInput[] = {
    "5",
    "intermediate",
    "inttterrmeediateeee",
    "program",
    "ppproograaamm",
    "aaa"
  };

  for (size_t i = 0; i < sizeof(testInput) / sizeof(testInput[0]); ++i) {
    fprintf(tempFile, "%s\n", testInput[i]);
  }

  fclose(tempFile);

  FILE *testFile = fopen("testInput", "r");
  if (testFile == NULL) {
    fprintf(stderr,"Failed to open the temporary test file for reading");
    exit(1);
  }
  char sizetemp;
  fscanf(testFile, "%c",&sizetemp);
  const char* s = &sizetemp;
  int size;
  sscanf(s,"%d",&size);
  
  char words[MAX_WORD_NUM][MAX_WORD_SIZE + 1];
  int result = read_file(testFile, words, size);

  fclose(testFile);

  assert(result == 0);

  remove("testInput");
  

}

void test_match_regex() {
  assert(match("abc", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("abcd", "abc", TEST_RESTRICTION_1) == 0);
  assert(match("", "", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("123", "123", TEST_RESTRICTION_1) == 1);
}


void test_match_regex_star() {
  assert(match("cd*", "c", TEST_RESTRICTION_1) == 1);
  assert(match("abcd*", "abc", TEST_RESTRICTION_1) == 1);
  assert(match("c*d", "ccd", TEST_RESTRICTION_1) == 1);
  assert(match("abc*d", "abcccccccd", TEST_RESTRICTION_1) == 1);
  assert(match("abc*de", "abcccccccd", TEST_RESTRICTION_1) == 0);

  // TODO: Write your own tests!
  //a*a   a
  assert(match("abg*d", "abgggd", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_question() {
  assert(match("a?", "", TEST_RESTRICTION_1) == 1);
  assert(match("a?", "b", TEST_RESTRICTION_1) == 0);
  assert(match("a?", "a", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("a?c", "ac", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_tilde() {
  assert(match("~", "aaaa", TEST_RESTRICTION_1) == 1);
  assert(match("~", "", TEST_RESTRICTION_1) == 1);
  assert(match("~", "a", TEST_RESTRICTION_1) == 1);

  // TODO: Write your own tests!
  assert(match("~", "aa", TEST_RESTRICTION_1) == 1);
}

void test_match_regex_multiple() {
  assert(match("~abc", "sda12!$2", TEST_RESTRICTION_1) == 0);
  
  //assert(match("P?E*e", "e",TEST_RESTRICTION_1) == 1);
  assert(match("!2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  assert(match("!~2*keK?ee?rCC?C*aP?E*eR*T*", "!2222keKerCCCaeRRRT",
               TEST_RESTRICTION_1) == 1);
  // TODO: Write your own tests!
  assert(match("~abc", "sda12!$3", TEST_RESTRICTION_1) == 0);
}

void test_match_regex_tilde_restriction() {
  // TODO: Write your own tests!
  assert(match("~a", "aaaa", TEST_RESTRICTION_2) == 0);
  assert(match("~a", "aaaa", TEST_RESTRICTION_3) == 1);
  assert(match("~a", "aaaa", TEST_RESTRICTION_4) == 1);
}

int main() {
  printf("Starting Tests...\n");
  test_read_files();
  test_match_regex();
  test_match_regex_star();
  test_match_regex_question();
  test_match_regex_tilde();
  test_match_regex_multiple();
  test_match_regex_tilde_restriction();
  printf("All tests passed!!!\n");
}
