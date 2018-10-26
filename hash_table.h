#pragma once
#include "linked_list.h"

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;



struct entry
{
  int hash;
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  int size;
  int calc_size;
  ioopm_hash_function hashfun;
  ioopm_eq_function eqfunc;
  entry_t buckets[];
};

entry_t* find_previous_entry_for_key(ioopm_hash_table_t *ht, elem_t key);
entry_t * entry_create(elem_t key, elem_t value, entry_t *next, ioopm_hash_function hashfun);
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash, ioopm_eq_function eqfunc, int size);
void ioopm_hash_table_insert(ioopm_hash_table_t **ht, elem_t key, elem_t value);
void ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key );
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

//Ticket 2
size_t ioopm_hash_table_size(ioopm_hash_table_t *h);
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h);
void ioopm_hash_table_clear(ioopm_hash_table_t *h);
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *h);
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *h);
bool ioopm_hash_table_has_key(ioopm_hash_table_t *h, elem_t key);

bool ioopm_hash_table_has_value(ioopm_hash_table_t *h, elem_t value);


bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg);


bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg);


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, elem_t *arg);

void ioopm_hash_table_print(ioopm_hash_table_t *ht);
