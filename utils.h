#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_shelf(char *str);

bool not_empty(char *str);

bool is_number(char *str);

 char *read_string();

extern char *strdup(const char *);

typedef union {
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(*check_func)(char[]);
typedef answer_t(*convert_func)(char[]);

answer_t ask_question(char *question, check_func check, convert_func convert);

answer_t make_float(char *str);

int ask_question_int(char *question);

char *ask_question_string(char *question);

char *ask_question_shelf(char *question);
