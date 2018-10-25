#include <stdio.h>
#include "business_logic.h"
#include "utils.h"
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1

int webstore_menu_ui() {
  char * const list[] = {"Add Merchandise", "List Merchandise", "Remove Merchandise", "Edit Merchandise", "Show Stock", "Replenish", "Create Cart", "Remove Cart", "Add To Cart", "Remove From Cart", "Calcute Cost", "Checkout", "Undo", "Quit", NULL};
  puts("\n\tMENU\n\t――――――――");
  for (int i=0; list[i]; ++i) printf("%d\t%s\n", i+1, list[i]);
  puts("");
   char *str_in = read_string();
   int int_in = atoi(str_in);
   if (int_in > 0 && int_in<=webstore_list_len) {
     printf("%s\n", list[int_in - 1]);
    return int_in;
   }
   else {
   float best = 0;
   int best_i = 0;
   float score = 0;
  for (int i = 0; list[i]; ++i) {
    score = str_cmp(str_in, list[i]);
    if (score>best) {best = score; best_i = i;}
  }
  if (best>0) {
  printf("%s?\n", list[best_i]);
  char *str_in = read_string();
  score = str_cmp(str_in, "y");
  if (score>=3 || str_in[0]=='\0') return best_i + 1; 
  }
  }
   return webstore_menu_ui();
}

static void show_stock(webstore_t *webstore) {
  char *name = ask_question("Name: ", "Name: ", check_true);
  free(name);
}

static void remove_merch(webstore_t *webstore) {
    char *remove = ask_question("Name: ", "Name: ", check_true);
    webstore_remove_merch(webstore, remove);
    free(remove);
}

static void edit_merch(webstore_t *webstore) {
    char *edit = ask_question("Name: ", "Name: ", check_true);
    char *name = ask_question("New name: ", "New name: ", check_true);
    char *desc = ask_question("New description: ", "New description: ", check_true);
    char *price_str = ask_question("New name: ", "New name: ", check_true);
    int price = atoi(price_str);
    webstore_edit_merch(webstore, edit, name, desc, price);
    free(edit);
    free(name);
    free(desc);
    free(price_str);
}

static void replenish(webstore_t *webstore) {
 char *edit = ask_question("Name: ", "Name: ", check_true);
 char *amount_str = ask_question("Name: ", "Name: ", check_true);
 int amount = atoi(amount_str);
 webstore_replenish(webstore, edit, amount);
 free(edit);
 free(amount_str);
}

static void add_merch(webstore_t *webstore) {
  puts("");
  char *name = ask_question("Name: ", "Name: ", check_true);
  char *desc = ask_question("Description: ", "Description: ", check_true);
  char *price_str = ask_question("Price: ", "Price: ", check_true);
  int price = atoi(price_str);
  webstore_add_merch(webstore, name, desc, price);
  free(name);
  free(desc);
  free(price_str);
}

static void list_merch(webstore_merch_t **merch){
  while (*merch)
    {
      printf("\nName: %s\nDescription: %s\nPrice: %d SEK\n", (*merch)->name, (*merch)->description, (*merch)->price);
      merch = &(*merch)->next;
    }
}

static void create_cart(webstore_t *webstore) {
  webstore_create_cart(webstore);
}

static void remove_cart(webstore_t *webstore) {
  webstore_remove_cart(webstore);
}

static void add_to_cart(webstore_t *webstore) {
  webstore_add_to_cart(webstore);
}

static void remove_from_cart(webstore_t *webstore) {
  webstore_remove_from_cart(webstore);
}

static void calculate_cost(webstore_t *webstore) {
  webstore_calculate_cost(webstore);
}

static void checkout(webstore_t *webstore) {
  webstore_checkout(webstore);
}

void webstore_menu(webstore_t *webstore){
  int menu = webstore_menu_ui();
  switch(menu) {
    case 1 :
      add_merch(webstore);
      webstore_menu(webstore);
      break;
    case 2 :
      list_merch((&webstore->merch));
      webstore_menu(webstore);
      break;
    case 3 :
      remove_merch(webstore);
      webstore_menu(webstore);
      break;
    case 4 :
      edit_merch(webstore);
      webstore_menu(webstore);
      break;
    case 5 :
      show_stock(webstore);
      webstore_menu(webstore);
      break;
    case 6 :
      replenish(webstore);
      webstore_menu(webstore);
      break;
    case 7 :
      create_cart(webstore);
      webstore_menu(webstore);
      break;
    case 8 :
      remove_cart(webstore);
      webstore_menu(webstore);
      break;
    case 9 :
      add_to_cart(webstore);
      webstore_menu(webstore);
      break;
    case 10 :
      remove_from_cart(webstore);
      webstore_menu(webstore);
      break;
    case 11 :
      calculate_cost(webstore);
      webstore_menu(webstore);
      break;
    case 12 :
      checkout(webstore);
      webstore_menu(webstore);
      break;
    case 13 :
      webstore_undo(webstore);
      webstore_menu(webstore);
      break;
    case 14 :
      break;
  }
}

int main() {
  webstore_t *webstore = webstore_init();
  webstore_menu(webstore);
  webstore_remove(webstore);
 return 0; 
}

