#include <stdio.h>
#include "business_logic.h"
#include "utils.h"
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1



/*  Function declaration */


// Prints the UI of the webstore and checks if user chose a valid input
int webstore_menu_ui() {

  // All choises in menu to chose from
  char *list[] = {
      "Add Merchandise",
      "List Merchandise",
      "Remove Merchandise",
      "Edit Merchandise",
      "Show Stock",
      "Replenish",
      "Create Cart",
      "Remove Cart",
      "Add To Cart",
      "Remove From Cart",
      "Calcute Cost",
      "Checkout", "Undo",
      "Quit",
      NULL
  };
  // Print the Menu for the user interface
  puts("\n\tMENU\n\t――――――――");
  for (int menu_choise=0; list[menu_choise]; ++menu_choise) {
      printf("%d\t%s\n", menu_choise+1, list[menu_choise]);
  }  
  puts("");


  // Get the inputed string form user and insures it's a number
  // Converts the string to a number
  char *str_in = read_string();
  int int_in = atoi(str_in);

  // If the chosen menu choise is valid, show that option
  if (int_in > 0 && int_in <= webstore_list_len) {
	  printf("%s\n", list[int_in - 1]);
	  free(str_in);
	  return int_in;
  }
  
  else {
	  float best = 0;
	  int best_i = 0;
	  float score = 0;
	  for (int i = 0; list[i]; ++i)
		{
	    score = str_cmp(str_in, list[i]);
	    if (score > best)
			{
		    best = score;
		    best_i = i;
	   		 }
	 	 }
	
	  if (best > 0) {
	    printf("%s?\n", list[best_i]);
		free(str_in);
	    char *str_in = read_string();
	    score = str_cmp(str_in, "y");

	    if (score >= 3 || str_in[0] == '\0')
	{
free(str_in);
return best_i + 1;
} 
	  }
  }

  // If no valid choise were made, print the UI again to the user
free(str_in);
  return webstore_menu_ui();
}




// Show all places a given merch is loacted and how much
static void show_stock(webstore_t *webstore) {
  show_stock_aux(webstore);
}




// Remove merchandise based on name 
static void remove_merch(webstore_t *webstore) {
  char *merch_to_remove = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty);	
  // Check if merch exists before removing
	if (webstore_is_no_item(merch_to_remove, webstore, "merch")) 
{
free(merch_to_remove);
return;
}
	else webstore_remove_merch(webstore, merch_to_remove);

  free(merch_to_remove);
}




// Edit merchandise based on name 
static void edit_merch(webstore_t *webstore) {
  char *merch_to_edit = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty); 
  // Check if item exists before editing
  if (webstore_is_no_item(merch_to_edit, webstore, "merch"))
{
free(merch_to_edit);
return;
}
  else {
	  char *name = ask_question("New name: ", "\nCan not be empty!\nNew name: ", not_empty);
	  char *desc = ask_question("New description: ", "New description: ", check_true);
	  char *price_str = ask_question("New price: ", "\nMust be a number larger than 0!\nNew price: ", is_positive); //TODO:: - Changed this from name to price
	  int price = atoi(price_str);

    webstore_edit_merch(webstore, merch_to_edit, name, desc, price);
    free(name);
    free(desc);
    free(price_str);
  }
 
  free(merch_to_edit);
}




// Replenish merchandise based on name and location
static void replenish(webstore_t *webstore) {
  char *item_to_replenish = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty);
  // Check if merch exists before replenishing
  if (webstore_is_no_item(item_to_replenish, webstore, "merch"))
{
free(item_to_replenish);
return;
}
  else {
	  char *location = ask_question("Location: ", "\nMust be formatted \"X00\"!\nLocation: ", is_shelf);
	  char *amount_str = ask_question("Amount: ", "\nMust be a number larger than 0!\nAmount: ", is_positive);
	  int amount = atoi(amount_str);

	  webstore_replenish(webstore, item_to_replenish, location, amount);
	  free(location);
	  free(amount_str);
  }
  
  free(item_to_replenish);
}




// Add merchendise name, description and price
static void add_merch(webstore_t *webstore) {
  char *merch_name = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty);
  // Check if merch alreday exists before adding new
  if (webstore_is_already_item(merch_name, webstore, "merch"))
{
free(merch_name);
return;
}
  else {
	  char *desc = ask_question("Description: ", "Description: ", check_true);
	  char *price_str = ask_question("Price: ", "\nMust be a number larger than 0!\nPrice: ", is_positive);
	  int price = atoi(price_str);

	  webstore_add_merch(webstore, merch_name, desc, price);
    free(desc);
	  free(price_str);
  }
  
  free(merch_name);
}



// List all merchandise name, description and price
static void list_merch(webstore_merch_t **merch){
  list_merch_aux(merch);
}





// Prints a message when creating a cart
static void create_cart(webstore_t *webstore) {
  printf("Cart created with index %d\n", webstore_create_cart(webstore));
}




// Removes a given cart based on cart index number
static void remove_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart: ", "\nMust be a number larger than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  if (webstore_remove_cart(webstore, cart_index)) puts("Cart removed");
  else puts("\nThe chosen item is not in cart!");
  free(cart_str);
}




// Adds a given item to a given cart
static void add_to_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart: ", "\nMust be a number larger than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  char *item_name = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty);
  
  // Check if item exists before adding to cart
  if (webstore_is_no_item(item_name, webstore, "item"))	
{
free(item_name);
free(cart_str);
return;
}
  else {
    char *amount_str = ask_question("Amount: ", "\nMust be a number larger than 0!\nAmount: ", is_positive);
    int amount = atoi(amount_str);
    int result = webstore_add_to_cart(webstore, item_name, amount, cart_index);

    switch(result) {
    case 0 :
      puts("\nThis item does not exist!");
      break;
    case 1 :
      break;
    case 2 :
      puts("\nThis item is not available!");
      break;
    case 3 :
      puts("\nCart does not exist!");
      break;
    }
  
    free(amount_str); }
  free(item_name);
  free(cart_str);
}




// Removes a given item form a given cart
static void remove_from_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart: ", "\nMust be a number larger than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  char *item_name = ask_question("Name: ", "\nCan not be empty!\nName: ", not_empty);
  // Check if item exists before removeing from cart
  if (webstore_is_no_item(item_name, webstore, "item"))	
{
free(cart_str);
free(item_name);
return;
}
  else {
    char *amount_str = ask_question("Amount: ", "\nMust be a number larger than 0!\nAmount: ", is_positive);
    int amount = atoi(amount_str);
    int result = webstore_remove_from_cart(webstore, item_name, amount, cart_index);
    switch(result) {
      case 0 :
        puts("\nItem does not exist!");
        break;
      case 1 :
        break;
      case 2 :
        puts("\nNot enough items in cart!");
        break;
      case 3 :
        puts("\nCart does not exist!");
        break;
      }
  
    free(amount_str); }
  free(item_name);
  free(cart_str);
}




// Calculates the cost of all items in a given cart
static void calculate_cost(webstore_t *webstore) {
  char *cart_str = ask_question("Cart: ", "\nMust be a number larger than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  int price = webstore_calculate_cost(webstore, cart_index);
  switch(price) {
  case 0 :
    puts("\nCart is empty, please add wares to calculate a price!");
    break;
  case -1 :
    puts("\nThe chosen cart does not exist, please choose/add a valid cart!");
    break;
  default :
    printf("Total cost of cart %d: %d SEK\n", cart_index, price);
  }

  free(cart_str);
}




// Checkout all items in a cart
static void checkout(webstore_t *webstore) {
  char *cart_str = ask_question("Cart: ", "\nMust be a number larger than 0!\nCart: ", is_positive);
  int cart = atoi(cart_str);
  if (!webstore_checkout(webstore, cart)) puts("\nThe chosen cart does not exist, please choose/add a valid cart!");
  else puts("\nCheckout sucessful!");
    
  free(cart_str);
}




// Does the given action based on the choise from menu
void webstore_menu(webstore_t *webstore){
  int menu = webstore_menu_ui();
  switch(menu) {
    case 1 :
      add_merch(webstore);
      webstore_menu(webstore);
      break;
    case 2 :
      list_merch(get_merch(webstore)); 
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
      webstore_undo(webstore);    // TODO - To be implimented later
      webstore_menu(webstore);
      break;
    case 14 :
      break;
  }
}








/*
// Initialize the webstore
// When choosing to leave, the webstore and all content is removed
int main() {
  webstore_t *webstore = webstore_init();
  webstore_menu(webstore);
  webstore_remove(webstore);
  return 0; 
}
*/


