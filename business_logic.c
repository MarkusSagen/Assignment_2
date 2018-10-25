#include <stdio.h>
#include "utils.h"
#include "business_logic.h"
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1

void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price){
   webstore_merch_t *new_merch = malloc(sizeof(webstore_merch_t));
   new_merch->name = strdup(name);
   new_merch->description = strdup(desc);
   new_merch->price = price;
  webstore_merch_t **merch = &webstore->merch;
  
  while ((*merch) && strcmp((*merch)->name, new_merch->name) <= 0)merch = &(*merch)->next;
  new_merch->next = (*merch);
   *merch = new_merch;
   }

void webstore_remove_merch(webstore_t *webstore, char *remove){
  
}
void webstore_edit_merch(webstore_t *webstore, char *edit, char *name, char *desc, int price){
  
}

void webstore_replenish(webstore_t *webstore, char *edit, int amount){
  
}
void webstore_create_cart(webstore_t *webstore){
  
}
void webstore_remove_cart(webstore_t *webstore){
  
}
void webstore_add_to_cart(webstore_t *webstore){
  
}
void webstore_remove_from_cart(webstore_t *webstore){
  
}
int webstore_calculate_cost(webstore_t *webstore){
  return 0;
}
void webstore_checkout(webstore_t *webstore){
  
}
void webstore_undo(webstore_t *webstore){
  
}
webstore_t *webstore_init() {
  return calloc(1, sizeof(webstore_t));
}

void webstore_remove(webstore_t *webstore) {
  webstore_merch_t **merch = &webstore->merch;
  webstore_merch_t *rm;
  while(*merch) {
    rm = *merch;
    free(rm->name);
    free(rm->description);
    free(rm);
    merch = &(*merch)->next;
  }
  free(webstore);
}
