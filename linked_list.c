#include "linked_list.h"
#include <stdlib.h>

struct list
{
  elem_t value;
  int size;
  ioopm_list_t *next;
  ioopm_list_t *last;
  ioopm_eq_function fun;
};








// Creates a new empty list
ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function fun)
{
  ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
  list->fun = fun;
  return list;
}




// Tear down the linked list and return all its memory 
void ioopm_linked_list_destroy(ioopm_list_t *list) {
  ioopm_list_t *tmp = list->next;
  free(list);
  if (tmp != NULL) ioopm_linked_list_destroy(tmp);
}




// Insert at the end of a linked list 
void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{
  ioopm_list_t *tmp = ioopm_linked_list_create(NULL);
  tmp->value = value;
  tmp->next = list->next; 
  list->next = tmp;
  list->size += 1;
}




// Insert at the start of a linked list
void ioopm_linked_list_append(ioopm_list_t *list, elem_t value) {
  ioopm_list_t *tmp = ioopm_linked_list_create(NULL);
  tmp->value = value;
  if (list->last == NULL) { 
    list->last = tmp;
    list->next = tmp;
  }
  else {
    list->last->next = tmp;
    list->last = tmp;
  }
  list->size += 1;
}




// Insert an element into a linked list at valid index [0, n] for a list of n elements
void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value)
{
  ioopm_list_t *insert = ioopm_linked_list_create(NULL);
  insert->value = value;
  ioopm_list_t *prev = list;
  if (list->next == NULL) {
    list->next = insert;
    list->last = insert;
  }
  else {
    for (int i = 0; i < index; ++i)
      {
        prev = prev->next;
      }
    insert->next = prev->next;
    if (prev->next == NULL) list->last = insert;
    prev->next = insert;
  }
  list->size += 1;
}




//  Retrieve an element from a linked list
elem_t *ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  ioopm_list_t *tmp = list->next;
  for (int i = 0; i < index; ++i)
    {
    if (tmp == NULL) return NULL;
      tmp = tmp->next;
    }
  return &(tmp->value);
}


// Remove an element from a linked list
elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index) {
  ioopm_list_t **previous = &list;
  while (index > 0) {
    previous = &(*previous)->next;
    index -= 1;
  }
  elem_t removed = (*previous)->next->value;
  ioopm_list_t *tmp = (*previous)->next;
  (*previous)->next = (*previous)->next->next;
  free(tmp);
  list->size -= 1;
  if ((*previous)->next == NULL) list->last = *previous;
  return removed;
}




// Test if an element is in the list
bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
  ioopm_list_t **test = &list;
  while ((*test)->next != NULL) {
    if (list->fun((*test)->next->value, element)) return true;
    test = &((*test)->next);
  }
  return false;
}




// Looksup the number of elements in the linked list 
int ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->size;  
}




// Tests whether a list is empty or not
bool ioopm_linked_list_is_empty(ioopm_list_t *list) {
  if (list->next == NULL) return true;
  else return false;
}




// Removes all elements from a linked list
void ioopm_linked_list_clear(ioopm_list_t *list) {
  ioopm_list_t *tmp = list->next;
  ioopm_list_t *tmp_rm;
  list->next = NULL;
  bool loop = (tmp != NULL);
  while (loop) {
  tmp_rm = tmp;
  tmp = tmp->next;
  free(tmp_rm);
  if (tmp == NULL) return;
  }
}




// Tests if a supplied property holds for all elements in a list
bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x)
{
  ioopm_list_t **test = &(list->next);
  while (*test != NULL) {
    if (!prop((*test)->value, *(elem_t *)x)) return false;
    test = &((*test)->next); 
  }
  return true;  
}




// Tests if a supplied property holds for any element in a list
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(elem_t, elem_t), void *x)
{
  ioopm_list_t **ptr_to_list = &(list->next);
  while (*ptr_to_list != NULL) {
    if (prop((*ptr_to_list)->value, *(elem_t *)x)) return true;
    ptr_to_list = &((*ptr_to_list)->next); 
  }
  return false;   
}




// Applies a supplied function to all elements in a list
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(elem_t *, elem_t *), void *x)
{
  ioopm_list_t **ptr_to_list = &(list->next);
  while (*ptr_to_list != NULL) {
    fun(&(*ptr_to_list)->value, (elem_t *)x);
    ptr_to_list = &((*ptr_to_list)->next); 
  }  
}
