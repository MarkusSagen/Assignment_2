#pragma once
#include "linked_list.h"


/* Struct declaration for hash table and hash table entries */
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;




/// @brief creates and allocates memory for a hash table
/// @param f: the function to pass to a hash table
/// @param init_cap: the inital max number of buckets to create
/// @return an empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash, ioopm_eq_function eqfunc, int size);

/// @brief insert a new entry into a hash table
/// @param ht: the hash table to insert the entry into
/// @param key: the key to be inserted
/// @param value: the value to be inserted
/// @param f: the function to compare elements in a hash table
void ioopm_hash_table_insert(ioopm_hash_table_t **ht, elem_t key, elem_t value);


/// @brief removes an entry from a hash table with a certain key
/// @param ht: the hash table from which an entry is removed
/// @param key: the key of the entry to remove
/// @param f: the function to compare elements in a hash table
/// @return the index of the entry that was removed, (NULL) if no entry legal entry found
void ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key );


/// @brief destroy the hash table, and its subsequent entries
/// @param ht: the hast table to be removed
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);


/// @brief tries to find an entry from a hash table with a certain key
/// @param ht: the hash table from which an entry is checked for
/// @param key: the key of the entry to search for
/// @param f: the function to compare elements in a hash table
/// @return the entry searched for if it exists
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);


/// @brief finds the number of entries in a hash table
/// @param ht: the hash table from which an entry is removed
/// @return the size of the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *h);


/// @brief Checks if any entries exists in the hash table
/// @param ht: the hash table from which an entry is removed
/// @return true if hash table is empty, otherwise false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h);


/// @brief clears all entries in the hash table
/// Every entry is cleared without freeing the memory for each entry
/// @param ht: the hash table from which an entry is removed
void ioopm_hash_table_clear(ioopm_hash_table_t *h);


/// @brief gets all keys in the hash table and adds to an array
/// IMPORTAINT!!! Remember to free the array from the heap when no longer used
/// @param ht: the hash table to take the keys from
/// @return an array with all keys in the hash table
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *h);


/// @brief gets all values in the hash table and adds to an array
/// IMPORTAINT!!! Remember to free the array from the heap when no longer used
/// @param ht: the hash table to take the values from
/// @return an array with all values in the hash table
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *h);


/// @brief Finds if any entry has a specified key
/// @param ht: the hash table from which an entry is removed
/// @param key: the key searched for
/// @param f: the function to compare elements in a hash table
/// @return true if any entry has the specified key, otherwise false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *h, elem_t key);


/// @brief Finds if any entry has a specified value
/// @param ht: the hash table from which an entry is removed
/// @param value: the value searched for
/// @param f: the function to compare elements in a hash table
/// @return true if any entry has the specified value, otherwise false
bool ioopm_hash_table_has_value(ioopm_hash_table_t *h, elem_t value);


/// @brief checks if all entries have a specified attribute
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to check agains all entries
/// @param arg: a void pointer to compare agains value or key for an entry
/// @return true if all entries share a specified attribute, otherwise false
bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg);


/// @brief checks if any entries have a specified attribute
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to check agains all entries
/// @param arg: a void pointer to compare agains value or key for an entry
/// @return true if any entries share a specified attribute, otherwise false
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg);


/// @brief applies a specified function to all entries in a hash table
/// @param ht: the hash table from which an entry is removed
/// @param pred: a function to apply to all entries
/// @param arg: a void pointer to compare agains value or key for an entry
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, elem_t *arg);


/// @brief Prints the entire hash table
/// @param ht, the hash table to be printed to the console
void ioopm_hash_table_print(ioopm_hash_table_t *ht);
