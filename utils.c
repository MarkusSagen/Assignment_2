#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"
#include "common.h"





// Checks if a string is an empty string
bool not_empty(char *str) {
  return str[0] != '\0';
}

bool is_positive(char *number) {
  return atoi(number)>0;
}


// Checks if asked for shelf has valid shelf name
bool is_shelf(char *str) {
  return str[0] >= 'A' && str[0] <= 'Z' && str[1] >= '0' && str[1] <= '9'  && str[2] >= '0' && str[2] <= '9' && str[3] == '\0'; 
}




// Checks if number is a valid integer
bool is_number(char *str) {
  bool k = false;

  for (int i = 0; str[i] != '\0'; ++i) {
    int j = str[i] - '0';
    if (k && i>0) k = false;
    if (str[i] == '-' && i == 0) {j=0;k=true;};
    if (j < 0 || j > 9) return false;
  }

  if (k) return false;    
  return true;
}




// Reads an inputed sentance
char *read_string() {
  int buf_siz = 50;
  char buf[buf_siz];
  int i = 0;

  while (i<buf_siz) {
    buf[i] = getchar();
    if (buf[i] == '\n') {
      buf[i] = '\0';
      return strdup(buf);
    }
    ++i; }

  return strdup(buf);
}




// Asks a question that will repete until requirement is met
char* ask_question(char *question, char *error_msg, check_func check) {
  printf("%s", question);
  int buf_siz = 50;
  char buf[buf_siz];
  int i = 0;

  while (i<buf_siz) {
    buf[i] = getchar();

    if (buf[i] == '\n') {
      buf[i] = '\0';
      if (check(buf)) return strdup(buf);
      else return ask_question(error_msg, error_msg, check);
    }
    ++i;  }

  if (check(buf)) return strdup(buf);
  else return ask_question(error_msg, error_msg, check);
}




// Checks if answer to a given question is yes
bool yes_no() {
  char *str_in = read_string();
  float score = str_cmp(str_in, "y");
  if (score>=3 || str_in[0]=='\0') return true; 
  else return false;
}




// Returns always true
bool check_true() {
  return true;
}




// Converts a string inputed as float to actual type float
answer_t make_float(char *str)
{
  return (answer_t) { .float_value = atof(str) };
}




// Checks if two given characters are the same
static float char_match (char in, char cmp) {
  if (in == cmp) return 1;
  if  ((cmp >= 'a' && cmp <= 'z' && in == cmp - 'a' + 'A') || (cmp >= 'A' && cmp <= 'Z' && in == cmp + 'a' - 'A')) return 1;
  return 0;
}




// Compares if two strings are the same as each other
float str_cmp(char *in, char *cmp) {
  float result = 0;
  int in_p = 0;
  int cmp_p = 0;
  bool c = true;
  float mult = 1;
  float result_tmp;
  
  while (in[in_p] != '\0' && cmp[cmp_p] != '\0') {
    if (c) mult = 1; 
    else mult = 0.5;
    c = false;
    result_tmp = char_match(in[in_p], cmp[cmp_p]);

    if (result_tmp > 0) {
      ++in_p; result += result_tmp * mult; 
      c = true;
    }

    if (cmp_p==0 && result_tmp > 0) {result += 2;}
    if (cmp[cmp_p] == ' ') c = true;
    ++cmp_p;
  }

  return result;
}


