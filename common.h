#pragma once
#include <stdbool.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


/* Declaration of structs */


// An element declaration to be stored in a hash table
// Specifies what keys and values can have as types in the hash table
union elem
{
  int i;
  unsigned int u;
  unsigned long l;
  bool b;
  float f;
  void *p;
  char *s;
};

/* Typedef declarations */
typedef union elem elem_t;                                                                      // An element type in a hash table
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);                                           // Function to check if two elements are equal
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, elem_t extra, ioopm_eq_function fun);  // Predicates an element with a key, value and extra element with a function
typedef void(*ioopm_apply_function)(elem_t key, elem_t value, void *extra);                     // Applies a given function to an element with a key and value and a void pointer. Void pointer could be a function
