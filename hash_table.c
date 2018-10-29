#include "hash_table.h"




/* Struct declaration*/
/* Declareation of properties of an entry */
struct entry
{
    ioopm_elem_t key;
    ioopm_elem_t value;
    cmp_element_fun cmp_fun;
    entry_t *next;
};

/* Declareation of properties of a hash table */
struct hash_table
{
    size_t capacity;
    entry_t **buckets;
    hash_func hash_function;
};









/* Helper function: Rehash the hash table */
static void rehash_hash_table(ioopm_hash_table_t *ht, size_t ht_capacity, entry_t **arr)
{
    for (int i = 0; i < ht_capacity; i++)
    {
        // insert back all entries to resized hash table
        entry_t *entry = arr[i];
        ioopm_hash_table_insert(ht, entry->key, entry->value, entry->cmp_fun);
        free(entry);
    }
}




/* Helper function: Frees an entry */
static void entry_destroy(entry_t *entry_to_remove)
{
    entry_to_remove->next = 0;
    free(entry_to_remove);
}




/* Helper function: Allow inserting negative numbers */
static int neg_modulo(int x, int mod)
{
    double tmp = ((double) x / (double)mod);
    tmp = ceil((-tmp));
    return ( x + (((int) tmp) * mod) );
}




/* Finds entry before a serched for entry with a given key */
static entry_t **find_entry_for_key(entry_t **entry, ioopm_elem_t key, cmp_element_fun f)
{
    entry_t **cursor = entry;
    while (*cursor && !f((*cursor)->key, key))
    {
        cursor = &(*cursor)->next;
    }
    return cursor;
}




/* Helper function: Applies function to each entry from a given first entry */
/* Return how many enties affected */
static size_t apply_changer_all_entries(entry_t *entry, f_entry f)
{
    size_t acc = 0;
    entry_t *next_entry;
    
    while (entry != NULL)
    {
        /// TODO:: REMOVE THIS
        if (entry == NULL)
        {
            break;
        }
        /// TODO:: CHANGE TO: "entry = entry->next"
        next_entry = entry->next;
        f(entry);
        entry = next_entry;
        ++acc;
    }
    
    return acc;
}




/* Helper funcrtion: Adds an entry to an array  */
static void entry_gath_aux_entries(void *arr, void *entry, int acc, char* flag)
{
    *((entry_t **)arr + acc) = ((entry_t *)entry);
}




/* Helper funcrtion: Collects all entries keys or values */
static void entry_gath_aux_list(void *lt, void *entry, int acc, char* flag)
{
    if ( strcmp(flag,"key") == 0 )
    {
        ioopm_linked_list_append(((ioopm_list_t *) lt), ((entry_t *)entry)->key);
    }
    else
    {
        ioopm_linked_list_append(((ioopm_list_t *) lt), ((entry_t *)entry)->value);
    }
}




/* Helper function: when needing to pass function that does nothing */
static void do_nothing(entry_t *x)
{
    ;
}




/* Helper function:  Remove all values in hash table, without freeing memory */
static void hash_table_non_free_clear(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < (ht->capacity); ++i)
    {
        *(ht->buckets + i) = NULL; // Reset first pointer for each bucket
    }
}




/* Helper function for any/all: Compares if entry has searched for for key */
bool test_func(int key, char *value, void *x)
{
    //printf("Now testing: %i vs %i...",key,*((int *)x));
    return key == *((int *)x);
}




/************************************************************/
/*              FUNCTIONS                                   */




/* Gathers all enties in a hash table */
static void entry_gatherer(ioopm_hash_table_t *ht, void *arr, f_entry_collector f, char* flag )
{
    entry_t *entry;
    int acc = 0;
  
    for (int i=0; i < ht->capacity; i++)
    {
        entry = *(ht->buckets + i);     // first entry in each bucket
        while (entry != NULL)           // While not at end of bucket
        {
            f(arr, entry, acc, flag);   // Gather all entries in bucket
            entry = entry->next;
            acc++;
        }
    }
}




/* Create and allocate memory for hash table and buckets */
ioopm_hash_table_t *ioopm_hash_table_create(hash_func f, int init_cap)
{
    ioopm_hash_table_t *result;
    entry_t **buckets;
    buckets = calloc(1, init_cap * sizeof(entry_t *));
    result = calloc(1, sizeof(ioopm_hash_table_t));
    result->capacity = init_cap;
    result->buckets = buckets;
    result->hash_function = f;
    return result;
}




/* Doubles size and rehashed entries if hash table depth is to big */
static void check_load(ioopm_hash_table_t *ht)
{
    float our_load_factor = ((float) ioopm_hash_table_size(ht)) / ((float) ht->capacity);
    if (Load_Factor_HT < our_load_factor)
    {
        size_t size = ioopm_hash_table_size(ht);
        entry_t *all_entries[size];     // How many elements there are
        entry_gatherer(ht, all_entries, &entry_gath_aux_entries, "_" );
      
        // Set new capacity for hash table and reallocate memory
        size_t new_capacity = ht->capacity * 2;
        ht->buckets = realloc(ht->buckets, new_capacity * sizeof(entry_t));
        ht->capacity = new_capacity;
        hash_table_non_free_clear(ht);              // temporerely remove entries
        rehash_hash_table(ht, size, all_entries);   // re-insert entries in resized hash table
    }
}  




/* Calculates the bucket to insert entries */
static int ioopm_hash_func(ioopm_elem_t key, hash_func f, int buckets)
{
    int hash_code;

    // If no conversion, hash_code is the integrer
    if (f == NULL)
    {
        hash_code = key.i;
    }
    else
    {
        hash_code =  f(key);
    }

    // If hash_code is negative, convert to positive modulo
    if (hash_code < 0)
    {
        hash_code = neg_modulo(hash_code, buckets);
    }
  
    return hash_code % buckets;
}




/* Free an hash table and all its entries */
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_clear(ht);
    free(ht->buckets);
    free(ht);
    puts("Bye bye entire hashtable");
}




/* Removes one entry form hash table */
ioopm_elem_t *ioopm_hash_table_remove(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f)
{
    int bucket = ioopm_hash_func(key, ht->hash_function, ht->capacity);
    // Find previous entry for key
    entry_t **tmp = find_entry_for_key((ht->buckets + bucket), key, f);
    entry_t *entry_to_destroy = *tmp;

    // find the searched value and fix so the next pointer still works
    if (*tmp != NULL) // Same statement as in lookup
    { 
        ioopm_elem_t *value = &(*tmp)->value;   // get value of entry we want to remove
        *tmp = (*tmp)->next;                    // Link entry before
        entry_destroy(entry_to_destroy);        // free entry
        return value;
    }
    
    return NULL;
}




/* Finds if any entry has a given value */
ioopm_elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f)
{
    int bucket = ioopm_hash_func(key,ht->hash_function,ht->capacity);
    entry_t **tmp = find_entry_for_key(ht->buckets + bucket, key, f);
    if ( *tmp )
    {
        return &(*tmp)->value;
    }
    
    return NULL;
}




/* Creates new entry and allocates memory */
static entry_t *entry_create(ioopm_elem_t key, ioopm_elem_t value, cmp_element_fun f, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  // Add the new values to entry
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  new_entry->cmp_fun = f;

  return new_entry;
}




/* Insert entries into hash table */
void ioopm_hash_table_insert(ioopm_hash_table_t *ht,ioopm_elem_t key, ioopm_elem_t value,cmp_element_fun f)
{  
    // Calculate which bucket the item will go into
    int bucket = ioopm_hash_func(key, ht->hash_function, ht->capacity);
    // Search for an existing entry for a key
    entry_t **entry = find_entry_for_key((ht->buckets + bucket), key, f);
  
    if ((*entry) != NULL)
    {
        // entry with same value was found. Update it with new value
        (*entry)->value = value;
    }
    else
    {
        //Create new entry and link it to the other entries in that bucket
        *entry = entry_create(key, value, f , NULL);
    }
    
    check_load(ht);
}




/* Finds number of entries in hash table */
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    // The current number of buckets
    int no_buckets = ht->capacity;
    size_t size = 0;
    for ( int i = 0; i < no_buckets; ++i)
    {
        // Add the total number of all entries
        entry_t *entry = *(ht->buckets + i);
        size += apply_changer_all_entries(entry, &do_nothing);
    }
    
    return size;
}




/* Checks if hash table has no entries */
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}


/* Removes all entries but keeps the hash table */
void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < ht->capacity; ++i)
    {
        // Reset first pointer to each entru and remove all entries
        entry_t *bucket = *(ht->buckets + i);
        *(ht->buckets + i) = NULL;
        apply_changer_all_entries(bucket, &entry_destroy);
    }
}




/* Returns array with all keys in hash table */
/* IMPORTANT! Dealocate memory after usage! */
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    ioopm_list_t *lt = ioopm_linked_list_create();
    entry_gatherer(ht, lt, &entry_gath_aux_list, "key");
    return lt;
}
    



/* Returns array with all values in hash table */
/* IMPORTANT! Dealocate memory after usage! */
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    ioopm_list_t *lt = ioopm_linked_list_create();
    entry_gatherer(ht, lt, &entry_gath_aux_list, "value");
    return lt;
}




/* Finds if a given key exists in hash table */
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, ioopm_elem_t key, cmp_element_fun f)
{
    return ioopm_hash_table_lookup(ht, key, f);
}




/* Finds if a given value exists in hash table */
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, ioopm_elem_t value, cmp_element_fun f)
{
    entry_t *entry; // Current entry
    for (int i=0; i < ht->capacity; i++)
    {
        entry = *(ht->buckets + i);
        while (entry != NULL)
        {
            if (f(entry->value, value))
            {
                return true;
            }
            entry = entry->next;
        }
    }
    
    return false;
}




/* Tester function: Helper function: Applies test to all entries */
/* Apply a test-function pred to all entries */
static bool apply_test_func_to_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg, char *str)
{
    entry_t *entry;
    for (int i=0; i < ht->capacity; i++)
    {
        entry = *(ht->buckets + i);
        while (entry != NULL)
        {
            // Check if an attribute is shared
            if (pred(entry->key, entry->value, arg))
            {
                // Only one case needed to return if condition is "any"
                if (strcmp(str,"any")== 0 )
                {
                    return true;
                }
            }
            else
            {
                // Only one false case required if condition is "all"
                if (strcmp(str,"all")== 0 )
                {
                    return false;
                }
            }
            
            entry = entry->next;
        }
    }
    /// ADDED!!! - Used to just be: return false;
    if (strcmp(str,"any") == 0)
    {
        return false;
    }
    
    // Defaults to true if "ALL" entries shared common attribute
    else {
        return true;
    }
}




/* Test function: Apply a Test-function pred to all entries. */
/* True if all entries satisfies condition */
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg)
{
  return apply_test_func_to_all(ht, pred, arg, "all");
}




/* Test function: Apply a Test-function pred to all entries. */
/* True if any entries satisfies condition */
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg)
{
  return apply_test_func_to_all(ht, pred, arg, "any");
}


