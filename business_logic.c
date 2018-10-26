#include <stdio.h>
#include "utils.h"
#include "business_logic.h"
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1

static void delete_merch(webstore_merch_t *merch) {
  free(merch->name);
  free(merch->description);
  free(merch);
}

static void remove_item_from_carts(webstore_t *webstore, webstore_merch_t *merch){
   webstore_cart_t **cart = &webstore->cart;
  while (*cart)
    {
        webstore_cart_item_t **item = &(*cart)->items;
         while (*item) {
           if ((*item)->merch == merch) {
               webstore_cart_item_t *rm = *item;
               *item = (*item)->next;
               free(rm);
             }
           else item = &(*item)->next;
  }
      cart = &(*cart)->next;
    }
}

void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price){
  elem_t key = {.p = strdup(name)};
  if (ioopm_hash_table_lookup(webstore->hash, key))
    {
      puts("\nItem already exists!");
      free(key.p);
      return;
    }
   webstore_merch_t *new_merch = malloc(sizeof(webstore_merch_t));
   new_merch->name = strdup(name);
   new_merch->description = strdup(desc);
   new_merch->price = price;
  webstore_merch_t **merch = &webstore->merch;
  
  while ((*merch) && strcmp((*merch)->name, new_merch->name) <= 0)merch = &(*merch)->next;
  new_merch->next = (*merch);
   *merch = new_merch;
  elem_t value = {.p = merch};
  ioopm_hash_table_insert(&webstore->hash, key, value);
}

void webstore_remove_merch(webstore_t *webstore, char *remove){
  elem_t key = {.p = remove};
   elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
   if (!elem) {
     puts("\nDoes not exist!");
       return;
   }
  webstore_merch_t **merch = (webstore_merch_t**)elem->p;
  webstore_merch_t *merch_rm = *merch;
  remove_item_from_carts(webstore, *merch);
  webstore_stock_t **stock = &(*merch)->stock;
  while (*stock) {
    free((*stock)->location);
    webstore_stock_t *rm = *stock;
    stock = &(*stock)->next;
    free(rm);
  }
  *merch = (*merch)->next;
  delete_merch(merch_rm);
  ioopm_hash_table_remove(webstore->hash, key);
}
void webstore_edit_merch(webstore_t *webstore, char *edit, char *name, char *desc, int price){
  elem_t key = {.p = edit};
   elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
   if (!elem) {
     puts("\nDoes not exist!");
       return;
   }
  webstore_merch_t **merch = (webstore_merch_t**)elem->p;
  elem_t value = {.p = merch};
  ioopm_hash_table_remove(webstore->hash, key);
  key.p = strdup(name);
  ioopm_hash_table_insert(&webstore->hash, key, value);
  free((*merch)->name);
  free((*merch)->description);
  (*merch)->name = strdup(name);
  (*merch)->description = strdup(desc);
  (*merch)->price = price;
  
}

void webstore_replenish(webstore_t *webstore, char *edit, char *location, int amount){
elem_t key = {.p = edit};
   elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
   if (!elem) {
     puts("\nDoes not exist!");
       return;
   }
  webstore_merch_t **merch = (webstore_merch_t**)elem->p;
  (*merch)->available += amount;
  webstore_stock_t **stock = &(*merch)->stock;
    while ((*stock) && strcmp((*stock)->location, location) < 0) stock = &(*stock)->next; {
      if ((*stock) && strcmp((*stock)->location, location) == 0) (*stock)->amount += amount;
    else {
     webstore_stock_t *new_stock = malloc(sizeof(webstore_stock_t));
     new_stock->amount = amount;
     new_stock->location = strdup(location);
      new_stock->next = (*stock);
   *stock = new_stock;
    }
  }
}
int webstore_create_cart(webstore_t *webstore){
  webstore_cart_t *new_cart = calloc(1, sizeof(webstore_cart_t));
  webstore_cart_t **cart = &webstore->cart;
  int index = 0;
  while (*cart)
    {
      index = (*cart)->index;
      cart = &(*cart)->next;
    }
  *cart = new_cart;
  new_cart->index = ++index;
  return index;
}
static void delete_cart(webstore_cart_t *cart) {
  webstore_cart_item_t **item = &cart->items;
   webstore_cart_item_t *rm;
  while (*item) {
    rm = *item;
    ((webstore_merch_t*)(*item)->merch)->available += (*item)->amount;
    item = &(*item)->next;
    free(rm);
  }
  free(cart);
}
bool webstore_remove_cart(webstore_t *webstore, int rm){ 
   webstore_cart_t **cart = &webstore->cart;
   webstore_cart_t *cart_rm;
  while (*cart)
    {
      if ((*cart)->index == rm) {
        cart_rm = *cart;
        *cart = (*cart)->next;
         delete_cart(cart_rm);
        return true;
      }
      cart = &(*cart)->next;
    }
  return false;
}
int webstore_add_to_cart(webstore_t *webstore, char *edit, int amount, int cart_sel){
  elem_t key = {.p = edit};
   elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
   if (!elem) return 0;
  webstore_merch_t **merch = (webstore_merch_t**)elem->p;
  if ((*merch)->available < amount) return 2;
   webstore_cart_t **cart = &webstore->cart;
  while (*cart)
    {
      if ((*cart)->index == cart_sel) {
         (*merch)->available -= amount;
        webstore_cart_item_t **item = &(*cart)->items;
         while (*item) {
           if ((*item)->merch == (*merch)) {
             (*item)->amount += amount;
             return 1;
           }
           item = &(*item)->next;
  }
        
        webstore_cart_item_t *new_item = calloc(1, sizeof(webstore_cart_item_t));
        new_item->amount = amount;
        new_item->merch = *merch;
        *item = new_item;
        return 1;
      }
      cart = &(*cart)->next;
    }
  return 3;
}
int webstore_remove_from_cart(webstore_t *webstore, char *edit, int amount, int cart_sel){
  elem_t key = {.p = edit};
   elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
   if (!elem) return 0;
  webstore_merch_t **merch = (webstore_merch_t**)elem->p;
   webstore_cart_t **cart = &webstore->cart;
  while (*cart)
    {
      if ((*cart)->index == cart_sel) {
        webstore_cart_item_t **item = &(*cart)->items;
         while (*item) {
           if ((*item)->merch == (*merch)) {
             if ((*item)->amount >= amount)
               {
                 (*item)->amount -= amount;
             (*merch)->available += amount;
             if ((*item)->amount == 0) {
               webstore_cart_item_t *rm = *item;
               *item = (*item)->next;
               free(rm);
             }
             return 1; 
               }
             return 2;
           }
           item = &(*item)->next;
  }
      }
      cart = &(*cart)->next;
    }
  return 3;
}
int webstore_calculate_cost(webstore_t *webstore, int cart_sel){
     webstore_cart_t **cart = &webstore->cart;
  while (*cart)
    {
      if ((*cart)->index == cart_sel) {
        webstore_cart_item_t *item = (*cart)->items;
        int cost = 0;
        while (item) {
          cost += item->merch->price * item->amount;
          item = item->next;
        }
        return cost;
      }
      cart = &(*cart)->next;
    }
  return -1;
}
bool webstore_checkout(webstore_t *webstore, int cart_sel){
       webstore_cart_t **cart = &webstore->cart;
  while (*cart)
    {
      if ((*cart)->index == cart_sel) {
        webstore_cart_item_t *item = (*cart)->items;
        while (item) {
          int amount = item->amount;
          webstore_stock_t **stock = &item->merch->stock;
          while (amount>0)
            {
              if ((*stock)->amount <= amount) {
                free((*stock)->location);
                webstore_stock_t *rm = (*stock);
                amount -= (*stock)->amount;
                *stock = (*stock)->next;
                free(rm);
              }
              else {
                (*stock)->amount -= amount;
                amount = 0;
              }
            }
          item = item->next;
        }
        webstore_cart_t *cart_rm = *cart;
        *cart = (*cart)->next;
        delete_cart(cart_rm);
        return true;
      }
      cart = &(*cart)->next;
    }
  return false;
}
void webstore_undo(webstore_t *webstore){
  
}

static unsigned long string_sum_hash(const elem_t str2)
{
  int result = 0;
  char *str = (char *)str2.p;
  do
    {
      result +=  *str;
    }
  while (*++str != '\0'); 
  return result;
}

static bool elem_t_cmp (elem_t a, elem_t b)
{
  return ((char *)a.p == (char *)b.p);  
}

webstore_t *webstore_init() {
  webstore_t *webstore = calloc(1, sizeof(webstore_t));
  webstore->hash = ioopm_hash_table_create(string_sum_hash, elem_t_cmp, 17);
  return webstore;
}

void webstore_remove(webstore_t *webstore) {
  webstore_merch_t **merch = &webstore->merch;
  webstore_merch_t *rm;
  while(*merch) {
    rm = *merch;
    delete_merch(rm);
    merch = &(*merch)->next;
  }
  free(webstore);
}
