#include <stdio.h>
#include "utils.h"

void webstore_add_merch(){
  
}
void webstore_list_merch(){
  
}
void webstore_remove_merch(){
  
}
void webstore_edit_merch(){
  
}
void webstore_show_merch(){
  
}
void webstore_replenish(){
  
}
void webstore_create_cart(){
  
}
void webstore_remove_cart(){
  
}
void webstore_add_to_cart(){
  
}
void webstore_remove_from_cart(){
  
}
void webstore_calculate_cost(){
  
}
void webstore_checkout(){
  
}
void webstore_undo(){
  
}
void webstore_quit(){
  
}
void webstore_print_menu(char *list[]) {
  puts("");
  for (int i=0; list[i]; ++i) printf("[%d]\t%s\n", i+1, list[i]);
  puts("");
}

static void webstore_menu() {
  char * list[] = {"Add Merchandise", "List Merchandise", "Remove Merchandise", "Edit Merchandise", "Show Stock", "Replenish", "Create Cart", "Remove Cart", "Add To Cart", "Remove From Cart", "Calcute Cost", "Checkout", "Undo", "Quit", NULL};
  puts("\n\tMENU\n\t________");
   webstore_print_menu(list);
   char *str_in = read_string();
   int int_in = atoi(str_in);
   if (int_in > 0 && int_in<=14) printf("%s?\n", list[int_in - 1]);
   else {
   float best = 0;
   int best_i = 0;
   float score = 0;
  for (int i = 0; list[i]; ++i) {
    score = str_cmp(str_in, list[i]);
    if (score>best) {best = score; best_i = i;}
  }
  printf("%s?\n", list[best_i]);
  }

}

int main() {
  webstore_menu();
  return 0;
}
