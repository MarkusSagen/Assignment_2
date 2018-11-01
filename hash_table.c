#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "iterator.h"
#include "hash_table.h"
#define No_Buckets 17



/* Declaration of structs */

// Entries in the hash table
struct entry
{
  int hash;
  elem_t key;       
  elem_t value;    
  entry_t *next;    
};

// The structure of the hash table
struct hash_table
{
  int size;
  int calc_size;
  ioopm_hash_function hashfun;
  ioopm_eq_function eqfunc;
  entry_t buckets[];
};




/* Declaration of functions */


// Find the previous entry for a given key - returns Null if that entry was not found
entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, elem_t key) {
  unsigned long hash;                      

  if (ht->hashfun == NULL) hash = key.i; 
  else  hash = ht->hashfun(key);
  
  if (hash>0) {
    /// Calculate the bucket for this entry
    int bucket = hash % ht->size;
    entry_t *tmp = &ht->buckets[bucket];
    entry_t *tmp_prev = tmp;

    while (true) {
      if (tmp->hash >= hash) return tmp_prev;
      if (tmp->next == NULL) return tmp;
      tmp_prev = tmp;
      tmp = tmp->next;
    }
  }

  else return NULL;
}






// Finds the previous value in a rehashed hash table
entry_t *find_previous_rehash(ioopm_hash_table_t *ht, int hash) {
    /// Calculate the bucket for this entry
    int bucket = hash % ht->size;
    entry_t *tmp = &ht->buckets[bucket];
    entry_t *tmp_prev = tmp;

    // Loop until rehashed
    while (1) {
      if (tmp->hash >= hash) return tmp_prev;
      if (tmp->next == NULL) return tmp;
      tmp_prev = tmp;
      tmp = tmp->next;
    }
}




// Increases the size of the hash table by rehashing
static ioopm_hash_table_t *rehash(ioopm_hash_table_t *ht, int size) {
  ioopm_hash_table_t *ht_new = ioopm_hash_table_create(ht->hashfun, ht->eqfunc, size);
  ht_new->calc_size = ht->calc_size;

  for (int i = 0; i <= ht->size; ++i) {
    entry_t *tmp = ht->buckets[i].next;

    while(tmp != NULL) {
      entry_t *tmp_prev = find_previous_rehash(ht_new, tmp->hash);
      entry_t *tmpnext = tmp->next;
      tmp->next=tmp_prev->next;
      tmp_prev->next = tmp;
      tmp = tmpnext;
    }
  }

  free(ht);
  return ht_new;
}




// Creates a new entry in a hash table
entry_t *entry_create(elem_t key, elem_t value, entry_t *next, ioopm_hash_function hashfun) {
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;

  if (hashfun == NULL) entry->hash = key.i; else entry->hash = hashfun(key);

  return entry;
}




// Destroys an entry and all content in it
static void entry_destroy(entry_t *entry) {
  free((char *)(entry->key).p);
  free(entry);
}




// Creates an entire hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash,ioopm_eq_function eqfunc, int size) {
  if (!size) size = No_Buckets;

  ioopm_hash_table_t *result = calloc(size, sizeof(ioopm_hash_table_t) + size * sizeof(entry_t));
  result->hashfun = hash;
  result->eqfunc = eqfunc;
  result->size = size;

  return result;
}




// Inserts an entry into a hash table 
void ioopm_hash_table_insert(ioopm_hash_table_t **ht, elem_t key, elem_t value)
{
  entry_t *entry = find_previous_entry_for_key(*ht, key);

  if (entry == NULL) return;
  entry_t *next = entry->next;
  int hash;

  // Checks if the next entry should be updated or not
  if ((*ht)->hashfun == NULL) hash = key.i; else hash = (*ht)->hashfun(key);

  if (next && (next->hash == hash)) next->value = value;
  else {
    entry->next = entry_create(key, value, next, (*ht)->hashfun);
    (*ht)->calc_size += 1;
    if (((*ht)->calc_size*100) / ((*ht)->size) > 75) {
      int primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};
      int i = 0;
      for (; primes[i]!=(*ht)->size; ++i);
      *ht = rehash(*ht, primes[++i]);
    } 
  }
}




// Finds if hash table contains a given key
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  entry_t *tmp = find_previous_entry_for_key(ht, key);
  if (tmp == NULL) return NULL;

  entry_t *next = tmp->next;
  int hash;

  if (!next) return NULL;

  if (ht->hashfun == NULL) hash = key.i; 
  else hash = ht->hashfun(key);

  if (next->hash == hash) return &next->value;
  else return NULL;
}




// Removes all entris in an entire hash table
void ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  int hash;
  if (ht->hashfun == NULL) hash = key.i; else hash = ht->hashfun(key);
  if (hash>0) {
    /// Find the previous entry for key
    entry_t *tmp = find_previous_entry_for_key(ht, key);
    if (tmp->next != NULL) {
      if ((tmp->next->hash) == hash) {
        entry_t *tmp_rm = tmp->next;
        tmp->next = tmp->next->next;
        entry_destroy(tmp_rm);
        ht->calc_size -=1;
      }
    }
  }
}




// Destroys a bucket in a hash table
void destroy_bucket(entry_t *entry) {
  entry_t *tmp = entry->next;
  while (tmp != NULL) {
    entry_t *tmp2 = tmp;
    tmp = tmp->next;
    entry_destroy(tmp2);
  }
}




// Destroys an entire hash table
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  for (int i = 0; i <= ht->size; ++i) {
    destroy_bucket(&ht->buckets[i]);
  }

  free(ht);
}




// Finds the size of the hash table - How many entries it contains
size_t ioopm_hash_table_size(ioopm_hash_table_t *h) {
  int n = 0;
  for (int i = 0; i < h->size; ++i)  {
    entry_t *entry = &h->buckets[i];
    while (entry->next != NULL) {
      ++n;
      entry = entry->next;
    }
  }

  return n;
}




// Clears an entire hash table
void ioopm_hash_table_clear(ioopm_hash_table_t *h) {
  for (int i = 0; i <= h->size; ++i) {
    destroy_bucket((&h->buckets[i])->next);
    (&h->buckets[i])->next = NULL;
  }
}




// Checks if an hash tabel is empty - Has no entries
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h) {
  for (int i = 0; i < h->size; ++i) {
    if ((&h->buckets[i])->next != NULL) return false;      
  }

  return true;
}




// Gets a linked list of all keys in an entire hash table
// IMPORTAINT! Dealocate memory of the list after use
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *h) {
  ioopm_list_t *list = ioopm_linked_list_create(h->eqfunc);

  for (int i = 0; i < h->size; ++i) {
    if ((&h->buckets[i])->next != NULL) {
      entry_t *entry = (&h->buckets[i])->next;
      ioopm_linked_list_prepend(list, entry->key);
      
      while (entry->next != NULL){
        entry = entry->next;
        ioopm_linked_list_prepend(list, entry->key);
      }                  
    }
  }

  return list;
}




// Gets a linked list of all values in an entire hash table
// IMPORTAINT! Dealocate memory of the list after use
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *h) {
  ioopm_list_t *value_list = ioopm_linked_list_create(NULL);
  
  for (int i = 0; i< h->size; ++i) {
    if ((&h->buckets[i])->next != NULL) {
      entry_t *entry = (&h->buckets[i])->next;
      ioopm_linked_list_append(value_list, entry->value);

      while (entry->next != NULL){
        entry = entry->next;
        ioopm_linked_list_append(value_list, entry->value);          
      }
    }
  }

  return value_list;
}





// Helper function: Checks if hash table has a given key
static bool has_key(elem_t key, elem_t value, elem_t arg, ioopm_eq_function fun) {
  return ((fun == NULL && key.i == arg.i) || fun(arg, key)); 
}




// Checks if hash table has a given key
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key) {
  return ioopm_hash_table_any(ht, has_key, key);
}




// Helper function: Checks if hash table has a given value
static bool has_value(elem_t key, elem_t value, elem_t arg, ioopm_eq_function cmp) {
  return ((cmp == NULL && (char *)value.p == (char *)arg.p) || cmp(value, arg));
}




// Checks if hash table has a given value
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value) {
  return ioopm_hash_table_any(ht, has_value, value);
}




// Test function: Apply a Test-function pred to all entries. 
// True if all entries satisfies condition 
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, elem_t arg) {
  for (int i = 0; i < ht->size; ++i) {
    entry_t *entry = &ht->buckets[i];
    bool j = true;
    if (entry->next == NULL) j = false;

    while (j) {
      entry = entry->next;
      if (!pred(entry->key, entry->value, arg, ht->eqfunc)) return false;
      if (entry->next == NULL) j = false;
    }
  }

  return true;
}





// Test function: Apply a Test-function pred to all entries. 
// True if any entries satisfies condition 
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg) {
  for (int i = 0; i < h->size; ++i)  {
    entry_t *entry = &h->buckets[i];
    while (entry != NULL) {
      if (pred(entry->key, entry->value, arg, h->eqfunc)) return true;
      else  entry = entry->next;
    }  
  }

  return false;
}




// Tester function: Helper function: Applies test to all entries 
// Apply a test-function pred to all entries 
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, elem_t *arg) {
  for (int i = 0; i < ht->size; ++i) {
    entry_t *entry = &ht->buckets[i];
    bool j = true;
    if (entry->next == NULL) j = false;
    
    while (j) {
      entry = entry->next;
      apply_fun(entry->key, entry->value, arg);
      if (entry->next == NULL) j = false;
    }
  }
}




