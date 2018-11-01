#pragma once
#include <stdbool.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


/** Declaration of structs */

/// An element declaration to be stored in a hash table
/// Specifies what keys and values can have as types in the hash table
union elem {
  /// element could be a whole number
  int i;
  /// element could be a very long number
  unsigned int u;
  /// element could be an even longer number
  unsigned long l;
  /// element could be a true or false
  bool b;
  /// element could be a decemal number
  float f;
  /// element could be a pointer to something or not yet specifed form
  void *p;
  /// element could be a word
  char *s;
};



/** Typedef declarations */

/// The Type declaration of an element type in a hash table
typedef union elem elem_t; 
/// The Type declaration of a function to check if two elements are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);                                         
/// The Type declaration of a predicates an element with a key, value and extra element with a function
typedef bool(*ioopm_predicate)(elem_t key, elem_t value, elem_t extra, ioopm_eq_function fun);  
/// The Type declaration of a function that that applies a given function to an element with a key and value and a void pointer. Void pointer could be a function
typedef void(*ioopm_apply_function)(elem_t key, elem_t value, void *extra);                    

