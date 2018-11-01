#include "iterator.h"
#include "linked_list.h"
#include "common.h"
#include <stdlib.h>

/** Declaration of structs */

/// A structure of a linked list
struct list {
   /// A link in a linked list iterator has a value that could be a string, number exc. 
  elem_t value;
   /// The size of the linked list to iterate over
   int size;
   /// Pointer to the next entry for the iterator
  ioopm_list_t *next;
   /// Pointer to last link in linked list
  ioopm_list_t *last;  
};


/// A structure for itorator over the linked list
struct ioopm_list_iterator {
   /// The current link the iterator is at
  ioopm_list_t *current;
   /// A pointer to a dummy link for the iterator
  ioopm_list_t *dummy;
};



/** FUNCTION DECLARATION */


/// Creates an linked list itorator
ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list) {
  ioopm_list_iterator_t *iterator = calloc(1, sizeof(ioopm_list_iterator_t));
  iterator->current = list;
  iterator->dummy = list;
  return iterator; 
}




/// Finds if the linked list has a next link
bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter) {
  if (iter->current->next == NULL) return false;
  return iter->current->next->next;
}




/// Returns next item in the list
elem_t *ioopm_iterator_next(ioopm_list_iterator_t *iter) {  
  if (!ioopm_iterator_has_next(iter)) return NULL;
  iter->current = iter->current->next; 
  return &iter->current->value;
}




/// Removes a given item in the list
elem_t ioopm_iterator_remove(ioopm_list_iterator_t *iter) {
  ioopm_list_t *rm = iter->current->next;
  elem_t ret = iter->current->next->value;
  iter->current->next = iter->current->next->next;
  iter->dummy->size += 1;
  
  if (!iter->current->next) iter->dummy->last = iter->current;

  free(rm);
  return ret;
}




/// Inserts a given item wher the cursor of the itorator currently is
void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
  ioopm_list_t *insert = ioopm_linked_list_create(NULL);
  insert->value = element;
  insert->next = iter->current->next;

  if (!ioopm_iterator_has_next(iter)) {
    iter->current->next = insert;
    iter->dummy->last = insert;
  }
  else iter->current->next = insert;
  iter->dummy->size += 1;
}




/// Resets the itorator - Itorator is then at the begining of the linked list
void ioopm_iterator_reset(ioopm_list_iterator_t *iter) {
  iter->current = iter->dummy;  
}




/// Finds the current item the itorator is placed on
elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)  {
  return iter->current->next->value; 
}




/// Destroies the item where the itorator is currently placed
void ioopm_iterator_destroy(ioopm_list_iterator_t *iter) {
  iter->current = NULL;
  iter->dummy = NULL;
  free(iter);  
}
