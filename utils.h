#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"


/* Declarations of typedef */

typedef union {
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool(*check_func)(char[]);
typedef answer_t(*convert_func)(char[]);






/// @brief Checks if string is a valid shelf number
/// @param str, the string to check
///        Must be of type Ex: "A99"
/// @return True if valid shelf number, false otherwise
bool is_shelf(char *str);


/// @brief Checks if a given string has no characters
/// @param str, the string to check
/// @return True if not empty, false otherwise
bool not_empty(char *str);


/// @brief Checks if a given string is a integer number
/// @param str, the string to check
/// @return True if is a integer, false otherwise
bool is_number(char *str);


/// @brief Reads a given string 
char *read_string();


/// @brief Checks a question is of a asked for type. Repeats the question otherwise
/// @param question, the question being asked and displayed to the user
/// @param error_msg, the message to be displayed if inputed value vas of the wrong type
/// @param check, the function to check agains the asked for question 
///        Ex: int, char, bool, char *
/// @return Answer if the answer to the question was of correct type
///         otherwise displays error message and the question once again
char *ask_question(char *question, char *error_msg, check_func check);


/// @brief Checks if a given string is written as a float
/// @param str, the string to check
/// @return The string but converted to float if matched, otherwise as string
answer_t make_float(char *str);


/// @brief Checks if two strings are the same
/// @param str_in, the string inputed 
/// @param str_ref, the string to be compared to as reference
/// @return 1 if the stings are the same
float str_cmp(char *str_in, char *str_ref);


/// @brief Helper function that always returns true
/// @return Always returns true
bool check_true();

bool is_positive(char *number);
