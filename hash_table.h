#pragma once

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "list_linked.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define No_Buckets 17
#define Load_Factor_HT 0.75


/* Struct declaration for hash table and hash table entries */
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

/* Declaration of Hash_table function pointers */
typedef int (*hash_func)(ioopm_elem_t);
typedef void (*f_entry)(entry_t *);
typedef void (*f_entry_collector)(void *,void *, int, char*); 
typedef bool (*ioopm_apply_function)(ioopm_elem_t, ioopm_elem_t, void *);


/// TODO:: REMOVE LATER TO EXAMPLE.H
// void find_value(ioopm_hash_table_t *ht, int x); // Not declare static in case you want to use it for testing purposes
// bool test_func(int key, char *value, void *x); //Made this myself





/// @brief creates and allocates memory for a hash table
/// @param f: the function to pass to a hash table
/// @param init_cap: the inital max number of buckets to create
/// @return an empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(hash_func f, int init_cap);


/// @brief destroy the hash table, and its subsequent entries
/// @param ht: the hast table to be removed
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);


/// @brief insert a new entry into a hash table
/// @param ht: the hash table to insert the entry into
/// @param key: the key to be inserted
/// @param value: the value to be inserted
/// @param f: the function to compare elements in a hash table
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, ioopm_elem_t key, ioopm_elem_t value, cmp_element_fun f);


/// @brief inserts a pointer to a element into the hash table
/// @param ht: the hash table to insert the pointer
/// @param key: key of the pointer to be inserted
/// @param value: value of the pointer to be inserted
/// @param f: the function to compare elements in a hash table
void ioopm_hash_table_insertptp(ioopm_hash_table_t *ht, ioopm_elem_t key, ioopm_elem_t value, cmp_element_fun f);



/// @brief removes an entry from a hash table with a certain key
/// @param ht: the hash table from which an entry is removed
/// @param key: the key of the entry to remove
/// @param f: the function to compare elements in a hash table
/// @return the index of the entry that was removed, (NULL) if no entry legal entry found
ioopm_elem_t *ioopm_hash_table_remove(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f);


/// @brief tries to find an entry from a hash table with a certain key
/// @param ht: the hash table from which an entry is checked for
/// @param key: the key of the entry to search for
/// @param f: the function to compare elements in a hash table
/// @return the entry
ioopm_elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f);


/// @brief finds the number of entries in a hash table
/// @param ht: the hash table from which an entry is removed
/// @return the size of the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);


/// @brief Checks if any entries exists in the hash table
/// @param ht: the hash table from which an entry is removed
/// @return true if hash table is empty, otherwise false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);


/// @brief clears all entries in the hash table
/// Every entry is cleared without freeing the memory for each entry
/// @param ht: the hash table from which an entry is removed
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);


/// @brief gets all keys in the hash table and adds to an array
/// IMPORTAINT!!! Remember to free the array from the heap when no longer used
/// @param ht: the hash table to take the keys from
/// @return an array with all keys in the hash table
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);


/// @brief gets all values in the hash table and adds to an array
/// IMPORTAINT!!! Remember to free the array from the heap when no longer used
/// @param ht: the hash table to take the values from
/// @return an array with all values in the hash table
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);


/// @brief Finds if any entry has a specified key
/// @param ht: the hash table from which an entry is removed
/// @param key: the key searched for
/// @param f: the function to compare elements in a hash table
/// @return true if any entry has the specified key, otherwise false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f);


/// @brief Finds if any entry has a specified value
/// @param ht: the hash table from which an entry is removed
/// @param value: the value searched for
/// @param f: the function to compare elements in a hash table
/// @return true if any entry has the specified value, otherwise false
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, ioopm_elem_t value, cmp_element_fun f);


/// @brief checks if all entries have a specified attribute
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to check agains all entries
/// @param arg: a void pointer to compare agains value or key for an entry
/// @return true if all entries share a specified attribute, otherwise false
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);


/// @brief checks if any entries have a specified attribute
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to check agains all entries
/// @param arg: a void pointer to compare agains value or key for an entry
/// @return true if any entries share a specified attribute, otherwise false
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);


/// @brief applies a specified function to all entries in a hash table
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to apply to all entries
/// @param arg: a void pointer to compare agains value or key for an entry
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

#endif

