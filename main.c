#include <stdio.h>
#include "utils.h"
#define webstore_list_len 14

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

static int webstore_menu_ui() {
  char * list[] = {"Add Merchandise", "List Merchandise", "Remove Merchandise", "Edit Merchandise", "Show Stock", "Replenish", "Create Cart", "Remove Cart", "Add To Cart", "Remove From Cart", "Calcute Cost", "Checkout", "Undo", "Quit", NULL};
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

void webstore_menu(){
  int menu = webstore_menu_ui();
  switch(menu) {
    case 1 :
      webstore_add_merch();
      webstore_menu();
      break;
    case 2 :
      webstore_list_merch();
      webstore_menu();
      break;
    case 3 :
      webstore_remove_merch();
      webstore_menu();
      break;
    case 4 :
      webstore_edit_merch();
      webstore_menu();
      break;
    case 5 :
      webstore_show_merch();
      webstore_menu();
      break;
    case 6 :
      webstore_replenish();
      webstore_menu();
      break;
    case 7 :
      webstore_create_cart();
      webstore_menu();
      break;
    case 8 :
      webstore_remove_cart();
      webstore_menu();
      break;
    case 9 :
      webstore_add_to_cart();
      webstore_menu();
      break;
    case 10 :
      webstore_remove_from_cart();
      webstore_menu();
      break;
    case 11 :
      webstore_calculate_cost();
      webstore_menu();
      break;
    case 12 :
      webstore_checkout();
      webstore_menu();
      break;
    case 13 :
      webstore_undo();
      webstore_menu();
      break;
    case 14 :
      break;
  }
}
int main() {
webstore_menu();
 return 0; 
}
