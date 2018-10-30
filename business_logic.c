#include <stdio.h>
#include "utils.h"
#include "business_logic.h"

/* Declaration of global variables */
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1
#define No_Buckets 17
#define INITIAL_HASH_CONSTANT 5381



/* Declaration of structs */
struct merch
{
  char *name;
  char *description;
  int price;
  webstore_stock_t *stock;
  webstore_merch_t *next;
  int available;
};

struct stock {
  char *location;
  int amount;
  webstore_stock_t *next;
};

struct webstore {
  webstore_merch_t *merch;
  ioopm_hash_table_t *hash;
  webstore_cart_t *cart;
};

struct cart_item {
  webstore_merch_t *merch;
  int amount;
  webstore_cart_item_t *next;
};

struct cart {
  webstore_cart_item_t *items;
  int index;
  webstore_cart_t *next;
};





// Lists all places a given merch is loacted and how much
void show_stock_aux(webstore_t *webstore) {
  // Check if the asked for item is in stock, based on name
  char *name = ask_question("Name: ", "Name: ", check_true);
  elem_t key = {.p = name};
  elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
  
  // Check if item exists before showing stock
  if (!elem) {
    puts("\nThis item does not exist!");
    return;
  }

  // Display where and how many there are in stock of the merch
	webstore_stock_t *stock = (*((webstore_merch_t**)(elem->p)))->stock;

	puts("");
	while (stock){
      printf("%s: %d\n", stock->location, stock->amount);
      stock = stock->next;
	}
  
  free(name);
}





// Deletes a given merchendise
static void delete_merch(webstore_merch_t *merch) {
  free(merch->name);
  free(merch->description);
  free(merch);
}




// Removes a given item from a given cart 
static void remove_item_from_carts(webstore_t *webstore, webstore_merch_t *merch) {
  webstore_cart_t **cart = &webstore->cart;

  while (*cart) {
    webstore_cart_item_t **item = &(*cart)->items;
    while (*item) {
      if ((*item)->merch == merch) {
        webstore_cart_item_t *item_to_remove = *item;
        *item = (*item)->next;
        free(item_to_remove);
      }
      else item = &(*item)->next;
    }

    cart = &(*cart)->next; }
}




// Adds merch to webstore based on unique name
void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price) {
  elem_t key = {.p = strdup(name)};

  if (ioopm_hash_table_lookup(webstore->hash, key) || price<1) free(key.p);
  else {
    webstore_merch_t *new_merch = calloc(1, sizeof(webstore_merch_t));

    new_merch->name = strdup(name);
    new_merch->description = strdup(desc);
    new_merch->price = price;
    webstore_merch_t **merch = &webstore->merch;
    
    while ((*merch) && strcmp((*merch)->name, new_merch->name) <= 0) merch = &(*merch)->next;
    
    new_merch->next = (*merch);
    *merch = new_merch;
    elem_t value = {.p = merch};
    ioopm_hash_table_insert(&webstore->hash, key, value);
  }
}



// Removes merch based on name
void webstore_remove_merch(webstore_t *webstore, char *remove) {
  elem_t key = {.p = remove};
  elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);

  if (!elem) return;
  else {
    webstore_merch_t **merch = (webstore_merch_t**)elem->p;
    webstore_merch_t *merch_to_remove = *merch;
    remove_item_from_carts(webstore, *merch);
    webstore_stock_t **stock = &(*merch)->stock;

    while (*stock) {
      free((*stock)->location);
      webstore_stock_t *stock_to_remove = *stock;
      stock = &(*stock)->next;
      free(stock_to_remove);
    }

    *merch = (*merch)->next;
    delete_merch(merch_to_remove);
    ioopm_hash_table_remove(webstore->hash, key);
  }
}




// Edits an existing merchendise based on name
void webstore_edit_merch(webstore_t *webstore, char *merch_to_edit, char *name, char *desc, int price) {
  elem_t key = {.p = merch_to_edit};
  elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);
  if (!elem) return;
  else {
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
}




// Replenishes merchendise based on name and loaction
void webstore_replenish(webstore_t *webstore, char *merch_to_rep, char *location, int amount) {
  elem_t key = {.p = merch_to_rep};
  elem_t *elem = ioopm_hash_table_lookup(webstore->hash, key);

  if (!elem || amount<1) return;
  else {
    webstore_merch_t **merch = (webstore_merch_t**)elem->p;
    (*merch)->available += amount;
    webstore_stock_t **stock = &(*merch)->stock;

    while ((*stock) && (strcmp((*stock)->location, location) < 0)) stock = &(*stock)->next;

    if ((*stock) && strcmp((*stock)->location, location) == 0) (*stock)->amount += amount;
    else {
      webstore_stock_t *new_stock = calloc(1, sizeof(webstore_stock_t));
      new_stock->amount = amount;
      new_stock->location = strdup(location);
      new_stock->next = (*stock);
      *stock = new_stock;
    }
  }
}




// Helper functon for listing all merch
webstore_merch_t **get_merch(webstore_t *webstore){
  return &webstore->merch;
}




// Lists all merchandise names, descriptions and prices
void list_merch_aux(webstore_merch_t **merch){
  while (*merch) {
	  printf("\nName: %s\nDescription: %s\nPrice: %d SEK\n", (*merch)->name, (*merch)->description, (*merch)->price);
	  merch = &(*merch)->next;
  }
}




// Creates a cart to hold items
int webstore_create_cart(webstore_t *webstore) {
  webstore_cart_t *new_cart = calloc(1, sizeof(webstore_cart_t));
  webstore_cart_t **cart = &webstore->cart;
  int index = 0;

  while (*cart) {
    index = (*cart)->index;
    cart = &(*cart)->next;
  }

  *cart = new_cart;
  new_cart->index = ++index;
  return index;
}


// Checks if a given index of a cart is stored in the webstore
bool webstore_is_not_cart(webstore_t *webstore, int index) {
  webstore_cart_t **cart = &webstore->cart;

  while(*cart) {
    if (index == (*cart)->index) return false;
    cart = &(*cart)->next;
  }

  return true;
}





// Deletes all items and a cart based on index
static void delete_cart(webstore_cart_t *cart) {
  webstore_cart_item_t **item = &cart->items;
  webstore_cart_item_t *item_to_remove;

  while (*item) {
    item_to_remove = *item;
    ((webstore_merch_t*)(*item)->merch)->available += (*item)->amount;
    item = &(*item)->next;
    free(item_to_remove);
  }

  free(cart);
}




// Removes cart based on cart index
bool webstore_remove_cart(webstore_t *webstore, int cart_to_remove) {  
  webstore_cart_t **cart = &webstore->cart;
  webstore_cart_t *cart_index_rm;

  while (*cart) {
    if ((*cart)->index == cart_to_remove) {
      cart_index_rm = *cart;
      *cart = (*cart)->next;
      delete_cart(cart_index_rm);
      return true;
    }

    cart = &(*cart)->next; 
  }

  return false;
}




// Adds items to a cart 
int webstore_add_to_cart(webstore_t *webstore, char *item_to_add, int amount, int cart_selected) {
  elem_t key = {.p = item_to_add};
  elem_t *selected_item = ioopm_hash_table_lookup(webstore->hash, key);

  // if item didn't exist
  if (!selected_item) return 0;
  webstore_merch_t **merch = (webstore_merch_t**)selected_item->p;
  
  // If item was not available
  if ((*merch)->available < amount) return 2;
  webstore_cart_t **cart = &webstore->cart;

  while (*cart) {
    if ((*cart)->index == cart_selected) {
      (*merch)->available -= amount;
      webstore_cart_item_t **item = &(*cart)->items;
      while (*item) {
        // if item exists and is available to add
        if ((*item)->merch == (*merch)) {
          (*item)->amount += amount;
          return 1;
        }

      item = &(*item)->next; }
        
      webstore_cart_item_t *new_item = calloc(1, sizeof(webstore_cart_item_t));
      new_item->amount = amount;
      new_item->merch = *merch;
      *item = new_item;
    
      return 1;  
    }

  cart = &(*cart)->next; }
// If a specified cart did not exist - Invalid cart should not be able to enter
return 3;
}




// Removes an item from a given cart
int webstore_remove_from_cart(webstore_t *webstore, char *item_to_remove, int amount, int cart_selected) {
  elem_t key = {.p = item_to_remove};
  elem_t *selected_item = ioopm_hash_table_lookup(webstore->hash, key);

  if (!selected_item) return 0;
  webstore_merch_t **merch = (webstore_merch_t**)selected_item->p;
  webstore_cart_t **cart = &webstore->cart;

  while (*cart) {
    if ((*cart)->index == cart_selected) {
      webstore_cart_item_t **item = &(*cart)->items;

      while (*item) {
        if ((*item)->merch == (*merch)) {
          if ((*item)->amount >= amount){
            (*item)->amount -= amount;
            (*merch)->available += amount;

            if ((*item)->amount == 0) {
              webstore_cart_item_t *item_to_remove = *item;
              *item = (*item)->next;
              free(item_to_remove);
            }
            // TODO
            return 1; }
            // TODO
          return 2; }
        item = &(*item)->next;
      }
    }

    cart = &(*cart)->next; 
  }
  
  // TODO
  return 3;
}




// Calculates cost of all items in a given cart
int webstore_calculate_cost(webstore_t *webstore, int cart_selected) {
  webstore_cart_t **cart = &webstore->cart;
  while (*cart) {
    if ((*cart)->index == cart_selected) {
      webstore_cart_item_t *item = (*cart)->items;
      int cost = 0;

      while (item) {
        cost += item->merch->price * item->amount;
        item = item->next;
      }
      
      // Returns the cost of all items in the cart
      // If cost is 0 - It will be interpreted as an error message
      return cost; }
    cart = &(*cart)->next; }
  // Returns -1 if no cart selected - Should not happen
  return -1;
}




// Checksout all item in a given cart
bool webstore_checkout(webstore_t *webstore, int cart_selected) {
  webstore_cart_t **cart = &webstore->cart;
  
  while (*cart) {
    if ((*cart)->index == cart_selected) {
      webstore_cart_item_t *item = (*cart)->items;
      
      while (item) {
        int amount = item->amount;
        webstore_stock_t **stock = &item->merch->stock;
        
        while (amount>0) {
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

        item = item->next;  }

      webstore_cart_t *cart_rm = *cart;
      *cart = (*cart)->next;
      delete_cart(cart_rm);
      return true;  }

    cart = &(*cart)->next;  }
  return false;
}




// undoes a previous action in the webstore - Not yet implemented!!!
void webstore_undo(webstore_t *webstore) {
    puts("\nNot yet implemented!");
}




// Calculate hash based on a variation of the hash function "djb2" by Dan Bernstein.
static unsigned long string_sum_hash(const elem_t ware) {
  char *str = (char *)ware.p;
  unsigned long hash = INITIAL_HASH_CONSTANT;
  int c = *str;

  /* The resulting hash will be at first:     5381 * 33 + c */
  while (c != 0) {
      hash = ((hash << 5) + hash) + c;    
      c = *(++str);
  }

  return hash;
}




// Compares if two pointers have the same value
static bool elem_t_cmp (elem_t elem1, elem_t elem2) {
  return ((char *)elem1.p == (char *)elem2.p);  
}




// Initializes an entire webstore and allocates memory
webstore_t *webstore_init() {
  webstore_t *webstore = calloc(1, sizeof(webstore_t));
  webstore->hash = ioopm_hash_table_create(string_sum_hash, elem_t_cmp, No_Buckets);
  return webstore;
}




// Removes an entire webstore and all merch 
void webstore_remove(webstore_t *webstore) {
ioopm_hash_table_destroy(webstore->hash);
  webstore_merch_t **merch = &webstore->merch;
  webstore_merch_t *merch_to_remove;

  while(*merch) {
    webstore_stock_t **stock = &(*merch)->stock;
    while (*stock) {
        webstore_stock_t *stock_rm = *stock;
        stock = &(*stock)->next;
        free(stock_rm->location);
        free(stock_rm);
      }

    merch_to_remove = *merch;
    delete_merch(merch_to_remove);
    merch = &(*merch)->next;
  }

  webstore_cart_t **cart = &webstore->cart;

  while (*cart) {
    webstore_cart_item_t **carts = &(*cart)->items;

    while (*carts) {
      webstore_cart_item_t *carts_rm = *carts;
      carts = &(*carts)->next;
      free(carts_rm);
    }

    webstore_cart_t *cart_rm = *cart;
    cart = &(*cart)->next;
    free(cart_rm);
  }

  free(webstore);
}


// Helper funtion - Prints out if there already exists item with that name
bool webstore_is_already_item(char *name, webstore_t *webstore, char *searched_for_ware) {
  elem_t key = {.p = name};
  if  (ioopm_hash_table_lookup(webstore->hash, key)) {
	  printf("\nThis %s already exists! \n", searched_for_ware);
	  return true;
  }

  return false; 
}




// Helper funtion - Prints out if there is no item with that name
bool webstore_is_no_item(char *name, webstore_t *webstore,  char *searched_for_ware) {
  elem_t key = {.p = name};
  if  (!ioopm_hash_table_lookup(webstore->hash, key)) {
	  printf("\nThis %s doesn't exists! \n", searched_for_ware);
    return true;
  }

  return false; 
}

elem_t *webstore_hash_lookup(webstore_t *webstore, elem_t elem) {
  return ioopm_hash_table_lookup(webstore->hash, elem);
}


int webstore_amount_in_stock(webstore_t *webstore, char *name) {
  int result = 0;
  elem_t elem;
  elem.p = name;
  elem_t *elem2 = ioopm_hash_table_lookup(webstore->hash, elem);

  if (!elem2->p) return result;
  else {
    webstore_merch_t *merch = (webstore_merch_t*)(elem2->p);
    webstore_stock_t **stock = &merch->stock;
    
    while (*stock) {
      result += (*stock)->amount;
      stock = &(*stock)->next;
    }
  }

  return result;
}

