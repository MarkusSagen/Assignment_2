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
void webstore_print_menu() {
  int list_size = 14;
  char * list[] = {"Add Merchandise", "List Merchandise", "Remove Merchandise", "Edit Merchandise", "Show Stock", "Replenish", "Create Cart", "Remove Cart", "Add To Cart", "Remove From Cart", "Calcute Cost", "Checkout", "Undo", "Quit"};
  puts("");
  for (int i=0; i<list_size; ++i) printf("[%d]\t%s\n", i+1, list[i]);
  puts("");
}

int main() {
  webstore_print_menu();

  char *read = read_string();
  puts(read);
  return 0;
}
