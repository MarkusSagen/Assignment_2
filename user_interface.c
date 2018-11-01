#include <stdio.h>
#include "business_logic.h"
#include "utils.h"


/**  Function declaration */


/// Prints the UI of the webstore and checks if user chose a valid input
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
      "Checkout", 
      "Undo",
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
  char *choise_made = read_string();
  int choise_made_nr = atoi(choise_made);
  int webstore_list_len = (int)(sizeof(list)/sizeof(list[0])) -1;
  // If the chosen menu choise is valid, show that option
  if (choise_made_nr > 0 && choise_made_nr <= webstore_list_len) {
	  printf("%s\n", list[choise_made_nr - 1]);
	  free(choise_made);
    
	  return choise_made_nr;
  }
  
  // Otwerwise if the user inputs characters, 
  // calculate which choise there are most likely to specify and returns the choise as a question
  else {
	  float calc_likely_choise = 0;
	  int make_choise_from_likely = 0;
	  float score = 0;
	  for (int i = 0; list[i]; ++i) {
	    score = str_cmp(choise_made, list[i]);
	    if (score > calc_likely_choise) {
		    calc_likely_choise = score;
		    make_choise_from_likely = i;
	   	 }
	   }

    // Free the choise for the made choise
    free(choise_made);

    // Chose a most likely choise to make based on the string the user inputed
	  if (calc_likely_choise > 0) {
	    printf("%s?\n", list[make_choise_from_likely]);
	    char *guess_best_choise = read_string();
	    score = str_cmp(guess_best_choise, "y");

	    if (score >= 3 || guess_best_choise[0] == '\0') {
       	  free(guess_best_choise);
          return (make_choise_from_likely + 1);
        } 
           free(guess_best_choise);
	  }

  }

  // If no valid choise were made, print the UI again to the user
  return webstore_menu_ui();
}




/// Show all places a given merch is loacted and how much
static void show_stock(webstore_t *webstore) {
  show_stock_aux(webstore);
}




/// Remove merchandise based on name 
static void remove_merch(webstore_t *webstore) {
  char *merch_to_remove = ask_question("Which merchendise: ", "\nMust enter at least one word!\nWhich merchendise: ", not_empty);	

  // Check if merch exists before removing
  if (webstore_is_no_item(merch_to_remove, webstore, "merch"));
  else webstore_remove_merch(webstore, merch_to_remove);

  free(merch_to_remove);
}




/// Edit merchandise based on name 
static void edit_merch(webstore_t *webstore) {
  char *merch_to_edit = ask_question("Which merchendise: ", "\nMust enter at least one word!\nWhich merchendise: ", not_empty); 
 
  // Check if item exists before editing
  if (webstore_is_no_item(merch_to_edit, webstore, "merch"));
  else {
	  char *name = ask_question("New name for item: ", "\nCan not be empty!\nNew name: ", not_empty);
	  char *desc = ask_question("New description: ", "New description: ", check_true);
	  char *price_str = ask_question("New price: ", "\nCart index must be a number larger than 0!\nNew price: ", is_positive); 
	  int price = atoi(price_str);

    webstore_edit_merch(webstore, merch_to_edit, name, desc, price);
    free(name);
    free(desc);
    free(price_str);
  }
 
  free(merch_to_edit);
}

       


/// Replenish merchandise based on name and location
static void replenish(webstore_t *webstore) {
  char *item_to_replenish = ask_question("Which merchendise:  ", "\nMust enter at least one word!\nWhich merchendise: ", not_empty);
  
  // Check if merch exists before replenishing
  if (webstore_is_no_item(item_to_replenish, webstore, "merch"));
  else {
	  char *location = ask_question("Location: ", "\nMust be formatted \"X00\"!\nLocation: ", is_shelf);
	  char *amount_str = ask_question("Amount: ", "\nCart index must be a number larger than 0!\nAmount: ", is_positive);
	  int amount = atoi(amount_str);

	  webstore_replenish(webstore, item_to_replenish, location, amount);
	  free(location);
	  free(amount_str);
  }
  
  free(item_to_replenish);
}




/// Add merchendise name, description and price
static void add_merch(webstore_t *webstore) { 
  char *merch_name = ask_question("Name of Merchendise: ", "\nMust enter at least one word!\nName of Merchendise:  ", not_empty);
  
  // Check if merch already exists before adding new
  if (webstore_is_already_item(merch_name, webstore, "merch"));
  else {
	  char *desc = ask_question("Description: ", "Description: ", check_true);
	  char *price_str = ask_question("Price: ", "\nCart index must be a number larger than 0!\nPrice: ", is_positive);
	  int price = atoi(price_str);

	  webstore_add_merch(webstore, merch_name, desc, price);
    free(desc);
	  free(price_str);
  }
  
  free(merch_name);
}



/// List all merchandise name, description and price
static void list_merch(webstore_merch_t **merch){
  list_merch_aux(merch);
}





/// Prints a message when creating a cart
static void create_cart(webstore_t *webstore) {
  printf("Cart created with index %d\n", webstore_create_cart(webstore));
}




/// Removes a given cart based on cart index number
static void remove_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart index: ", "\nCart index must be a number greater than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  if (webstore_remove_cart(webstore, cart_index)) printf("Cart %d was successfully removed\n", cart_index);
  else puts("\nCould not find a cart with what index");
  free(cart_str);
}




/// Adds a given item to a given cart
static void add_to_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart index: ", "\nCart index must be a number greater than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);

  // wont add items if no legal cart is selected
  if (webstore_is_not_cart(webstore, cart_index)) puts("\nThe chosen cart does not exist! Please select/add a valid cart!"); 

  else {
    char *item_name = ask_question("Item name: ", "\nCan not be empty!\nName: ", not_empty);
    
    // Check if item exists before adding to cart
    if (webstore_is_no_item(item_name, webstore, "merch"));
    else {
      char *amount_str = ask_question("Amount: ", "\nAmount to add must be more than 0!\nAmount: ", is_positive);
      int amount = atoi(amount_str);
      int result = webstore_add_to_cart(webstore, item_name, amount, cart_index);

      switch(result) {
      case 0 :
        puts("\nThis item does not exist! Please create it first to add it to the cart");
        break;
      case 1 :
        break;
      case 2 :
        puts("\nThis item is not yet available! Please replenish it first");
        break;
      case 3 :
        puts("\nThe chosen cart does not exist! Please select/add a valid cart!");
        break;
      }
    
      free(amount_str); 
    }

    free(item_name); 
  }

  free(cart_str);
}




/// Removes a given item form a given cart
static void remove_from_cart(webstore_t *webstore) {
  char *cart_str = ask_question("Cart index: ", "\nCart index must be a number greater than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);

  // Wont remove items from cart if no cart was found
  if (webstore_is_not_cart(webstore, cart_index))  puts("\nThe chosen cart does not exist! Please select/add a valid cart!"); 

  else {
    char *item_name = ask_question("Item name: ", "\nCan not be empty!\nName: ", not_empty);
    // Check if item exists before removeing from cart
    if (webstore_is_no_item(item_name, webstore, "merch"))	{
      free(cart_str);
      free(item_name);
    }


    else {
      char *amount_str = ask_question("Amount to remove: ", "\nAmount to remove must be more than 0!\nAmount: ", is_positive);
      int amount = atoi(amount_str);
      int result = webstore_remove_from_cart(webstore, item_name, amount, cart_index);
      switch(result) {
        case 0 :
          puts("\nThe selected item does not exist!");
          break;
        case 1 :
          break;
        case 2 :
          puts("\nThere are not enough items in cart to remove to remove that many items!");
          break;
        case 3 :
          puts("\nThe chosen cart does not exist! Please select/add a valid cart!");       
          break;
        }
    
      free(amount_str); 
    }

    free(item_name); 
  }

  free(cart_str);
}




/// Calculates the cost of all items in a given cart
static void calculate_cost(webstore_t *webstore) {
  char *cart_str = ask_question("Cart index: ", "\nCart index must be a number greater than 0!\nCart: ", is_positive);
  int cart_index = atoi(cart_str);
  int price = webstore_calculate_cost(webstore, cart_index);
  switch(price) {
  case 0 :
    puts("\nThis cart is empty. Please add wares to calculate a price!");
    break;
  case -1 :
    puts("\nThe chosen cart does not exist! Please select/add a valid cart!");
    break;
  default :
    printf("The total cost of cart %d comes to: %d SEK\n", cart_index, price);
  }

  free(cart_str);
}




/// Checkout all items in a cart
static void checkout(webstore_t *webstore) {
  char *cart_str = ask_question("Cart index: ", "\nCart index must be a number greater than 0!\nCart: ", is_positive);
  int cart = atoi(cart_str);
  if (!webstore_checkout(webstore, cart)) puts("\nThe chosen cart does not exist! Please select/add a valid cart!");
  else puts("\nCheckout sucessful!");
    
  free(cart_str);
}




/// Does the given action based on the choise from menu
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
      webstore_undo(webstore);  // Not implemented yet
      webstore_menu(webstore);  // Not implemented yet
      break;
    case 14 :
      break;
  }
}








