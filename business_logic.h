#pragma once
#include "hash_table.h"
typedef struct stock webstore_stock_t;
typedef struct merch webstore_merch_t;
typedef struct webstore webstore_t;
typedef struct cart_item webstore_cart_item_t;
typedef struct cart webstore_cart_t;
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

void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price);

void webstore_remove_merch(webstore_t *webstore, char *remove);
void webstore_edit_merch(webstore_t *webstore, char *edit, char *name, char *desc, int price);

void webstore_replenish(webstore_t *webstore, char *edit, char *location, int amount);
int webstore_create_cart(webstore_t *webstore);
bool webstore_remove_cart(webstore_t *webstore, int rm);
int webstore_add_to_cart(webstore_t *webstore, char *merch, int amount, int cart_sel);
int webstore_remove_from_cart(webstore_t *webstore, char *edit, int amount, int cart_sel);
int webstore_calculate_cost(webstore_t *webstore, int cart_sel);
bool webstore_checkout(webstore_t *webstore, int cart_sel);
void webstore_undo(webstore_t *webstore);
webstore_t *webstore_init();
void webstore_remove(webstore_t *webstore);
