#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"
#include "iterator.h"
#include "hash_table.h"
#include "CUnit/Basic.h"
#define No_Buckets 17




/// the types from above

entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, elem_t key) {
  int hash;
  if (ht->hashfun == NULL) hash = key.i; else  hash = ht->hashfun(key);
  if (hash>0) {
    /// Calculate the bucket for this entry
    int bucket = hash % ht->size;
    entry_t *tmp = &ht->buckets[bucket];
    entry_t *tmp_prev = tmp;
    while (1) {
      if (tmp->hash >= hash) {return tmp_prev;}
      if (tmp->next == NULL) {return tmp;}
      tmp_prev = tmp;
      tmp = tmp->next;
    }
  }
  else return NULL;
}



entry_t *find_previous_rehash(ioopm_hash_table_t *ht, int hash) {
    /// Calculate the bucket for this entry
    int bucket = hash % ht->size;
    entry_t *tmp = &ht->buckets[bucket];
    entry_t *tmp_prev = tmp;
    while (1) {
      if (tmp->hash >= hash) {return tmp_prev;}
      if (tmp->next == NULL) {return tmp;}
      tmp_prev = tmp;
      tmp = tmp->next;
    }
}

static ioopm_hash_table_t *rehash(ioopm_hash_table_t *ht, int size) {
  ioopm_hash_table_t *ht_new = ioopm_hash_table_create(ht->hashfun, ht->eqfunc, size);
  ht_new->calc_size = ht->calc_size;
  for (int i = 0; i <= ht->size; ++i)
    {
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

entry_t *entry_create(elem_t key, elem_t value, entry_t *next, ioopm_hash_function hashfun) {
  entry_t *entry = calloc(1, sizeof(entry_t));
  entry->key = key;
  entry->value = value;
  entry->next = next;
  if (hashfun == NULL) entry->hash = key.i; else entry->hash = hashfun(key);
  return entry;
}

static void entry_destroy(entry_t *entry) {
  free((char *)(entry->key).p);
  free(entry);
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash,ioopm_eq_function eqfunc, int size)
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  if (!size) size = No_Buckets;
  ioopm_hash_table_t *result = calloc(size, sizeof(ioopm_hash_table_t) + size * sizeof(entry_t));
  result->hashfun = hash;
  result->eqfunc = eqfunc;
  result->size = size;
  return result;
}

void ioopm_hash_table_insert(ioopm_hash_table_t **ht, elem_t key, elem_t value)
{
  entry_t *entry = find_previous_entry_for_key(*ht, key);
  if (entry == NULL) return;
  entry_t *next = entry->next;
  int hash;
  /// Check if the next entry should be updated or not
  if ((*ht)->hashfun == NULL) hash = key.i; else hash = (*ht)->hashfun(key);
  if (next && (next->hash == hash))
    {
      next->value = value;
    }
  else
    {
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

elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  entry_t *tmp = find_previous_entry_for_key(ht, key);
  if (tmp==NULL) return NULL;
  entry_t *next = tmp->next;
  int hash;
  if (!next) return NULL;
  if (ht->hashfun == NULL) hash = key.i; else hash = ht->hashfun(key);
  if (next->hash == hash)
    {
      return &next->value;
    }
  else
    {
      return NULL;
    }
}

/* entry_t *bucketz(entry_t *bucket, elem_t key) 
{
  if (bucket->next == NULL) return NULL;
  if (bucket->key == key) return bucket;
  if (bucket->key > key) return NULL;
  return bucketz(bucket->next, key);
}



char **ioopm_hash_table_lookup2(ioopm_hash_table_t *ht, elem_t key)
{
  if (key>0)
    {
      entry_t *sentinel = &ht->buckets[key % No_Buckets];
      entry_t *tmp = bucketz(sentinel, key);
      if (tmp != NULL) return &(tmp->value);
      return NULL;
    }
  return NULL;
}
*/






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

void destroy_bucket(entry_t *entry) {
  entry_t *tmp = entry->next;
  while (tmp != NULL) {
    entry_t *tmp2 = tmp;
    tmp = tmp->next;
    entry_destroy(tmp2);
  }
}



void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  for (int i = 0; i <= ht->size; ++i)
    {
      destroy_bucket(&ht->buckets[i]);
    }
  free(ht);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *h)
{
  int n = 0;
  for (int i = 0; i < h->size; ++i) 
    {
      entry_t *entry = &h->buckets[i];
      while (entry->next != NULL)
        {
          ++n;
          entry = entry->next;
        }
    };
  return n;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *h)
{
  for (int i = 0; i <= h->size; ++i)
    {
      destroy_bucket((&h->buckets[i])->next);
      (&h->buckets[i])->next = NULL;
    }
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h)
{
  for (int i = 0; i < h->size; ++i)
    {
      if ((&h->buckets[i])->next != NULL) return false;      
    }
  return true;
}


/*
int *ioopm_hash_table_keys(ioopm_hash_table_t *h)
{
  int *key_list = calloc(ioopm_hash_table_size(h), sizeof(int));
  int n = 0;
  for (int i = 0; i < No_Buckets; ++i)
    {
      if ((&h->buckets[i])->next != NULL)
        {
          entry_t *entry = (&h->buckets[i])->next;
          while (entry->next != NULL){
            key_list[n] = entry->key;
            ++n;
            entry = entry->next;
          }
          key_list[n] = entry->key;
          ++n;
        }
    }
  return key_list;
}
*/

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *h)
{
  ioopm_list_t *list = ioopm_linked_list_create(h->eqfunc);
  for (int i = 0; i < h->size; ++i)
    {
      if ((&h->buckets[i])->next != NULL)
        {
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



ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *h)
{
  ioopm_list_t *value_list = ioopm_linked_list_create(NULL);
  for (int i = 0; i< h->size; ++i)
    {
      if ((&h->buckets[i])->next != NULL)
        {
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



static bool has_key(elem_t key, elem_t value, elem_t arg, ioopm_eq_function fun)
{
  return ((fun == NULL && key.i == arg.i) || fun(arg, key)); 
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  return ioopm_hash_table_any(ht, has_key, key);
}


static bool has_value(elem_t key, elem_t value, elem_t arg, ioopm_eq_function cmp)
{
  return ((cmp == NULL && (char *)value.p == (char *)arg.p) || cmp(value, arg));
}
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  return ioopm_hash_table_any(ht, has_value, value);
}



bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, elem_t arg) {
  for (int i = 0; i < ht->size; ++i) 
    {
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



bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_predicate pred, elem_t arg)
{
  for (int i = 0; i < h->size; ++i) 
    {
      entry_t *entry = &h->buckets[i];
      while (entry != NULL)
        {
          if (pred(entry->key, entry->value, arg, h->eqfunc)) {
            return true;
          }
          else {
            entry = entry->next;
          }
        }  
    }
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, elem_t *arg) {
  for (int i = 0; i < ht->size; ++i) 
    {
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


/*
void ioopm_hash_table_print(ioopm_hash_table_t *ht) {
  for (int i = 0; i < No_Buckets; ++i) 
    {
      entry_t *entry = &ht->buckets[i];
      printf("---BUCKET %d---\n", i);
      bool j = true;
      if (entry->next == NULL) j = false;
      while (j) {
        entry = entry->next;
        printf("%d:\tValue:%s\n", entry->key, entry->value);
        if (entry->next == NULL) j = false;
      }
    }
}
*/
/*
int string_knr_hash(const elem_t str2)
{
  int result = 0;
  char *str = (char *)str2.p;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0'); 
  return result;
}

bool elem_t_cmp (elem_t a, elem_t b)
{
  return ((char *)a.p == (char *)b.p) && (a.i == b.i);  
}*/
/*
int main () {



  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_knr_hash, elem_t_cmp);
  elem_t key = {.p="abc"};
  elem_t keyfail = {.p="abcdsfa"};
  elem_t value = {.i=13};
  ioopm_hash_table_insert(ht, key, value);
  elem_t *test = ioopm_hash_table_lookup(ht, key);
  puts("abc");
  printf("%d\n", test->i);
  if (ioopm_hash_table_has_key(ht, keyfail)) puts("success");
  if (ioopm_hash_table_has_value(ht, value)) puts("success");
  return 0;
}
*/
