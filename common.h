#pragma once
#include <stdbool.h>



union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
};


typedef union elem elem_t;
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, elem_t extra, ioopm_eq_function fun);
typedef void(*ioopm_apply_function)(elem_t key, elem_t value, void *extra);
