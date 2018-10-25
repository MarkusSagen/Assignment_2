#pragma once
typedef struct stock webstore_stock_t;
typedef struct merch webstore_merch_t;
typedef struct webstore webstore_t;
struct merch
{
  char *name;
  char *description;
  int price;
  webstore_stock_t *stock;
  webstore_merch_t *next;
};
struct stock {
  char location[3];
  int amount;
  webstore_merch_t *merch;
  webstore_stock_t *next;
};

struct webstore {
  webstore_merch_t *merch;
};

struct list {
  
  void *next;
};

void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price);

void webstore_remove_merch(webstore_t *webstore, char *remove);
void webstore_edit_merch(webstore_t *webstore, char *edit, char *name, char *desc, int price);

void webstore_replenish(webstore_t *webstore, char *edit, int amount);
void webstore_create_cart(webstore_t *webstore);
void webstore_remove_cart(webstore_t *webstore);
void webstore_add_to_cart(webstore_t *webstore);
void webstore_remove_from_cart(webstore_t *webstore);
int webstore_calculate_cost(webstore_t *webstore);
void webstore_checkout(webstore_t *webstore);
void webstore_undo(webstore_t *webstore);
webstore_t *webstore_init();
void webstore_remove(webstore_t *webstore);
