#pragma once
#include "hash_table.h"
#include "common.h"
typedef struct stock webstore_stock_t;
typedef struct merch webstore_merch_t;
typedef struct webstore webstore_t;
typedef struct cart_item webstore_cart_item_t;
typedef struct cart webstore_cart_t;



/// @brief Adds merch to webstore based on unique name
/// @param webstore, the webstore where all merch is stored
/// @param name, name of the new merchendise to be added
/// @param desc, description of the new merchendise to be added
/// @param price, price of the new merchendise to be added
/// @param price, price of the new merchendise to be added
void webstore_add_merch(webstore_t *webstore, char *name, char *desc, int price);


/// @brief Removes merch based on name
/// @param webstore, the webstore where all merch is stored
/// @param remove, name of the chosen merchendise to be removed
void webstore_remove_merch(webstore_t *webstore, char *remove);


/// @brief Edits an existing merchendise based on name
/// @param webstore, the webstore where all merch is stored
/// @param merch_to_edit, name of existing merchendise that should be edited
/// @param name, updated name of the edited merchendise
/// @param desc, updated description of the edited merchendise
/// @param price, updated price of the edited merchendise 
void webstore_edit_merch(webstore_t *webstore, char *merch_to_edit, char *name, char *desc, int price);


/// @brief Lists all places a given merch is loacted and how much
/// @param webstore, the webstore where all merch is stored
void show_stock_aux(webstore_t *webstore);


/// @brief Replenishes merchendise based on name and loaction
/// @param merch_to_update, the name of the merchendise to update the amount 
/// @param location, location of the to be updatet
///        If location is added where no previous merchendise was loacted, it will add it there
///        There can be same merchendise at multiple locations
/// @param amount, amount to be added of the merchendise to the given location
void webstore_replenish(webstore_t *webstore, char *merch_to_update, char *location, int amount);


/// @brief Helper functon for listing all merch
/// @param webstore, the webstore where all merch is stored
/// @return pointer to a list of where all merchendise is located
webstore_merch_t **get_merch(webstore_t *webstore);


/// @brief Lists all merchandise names, descriptions and prices
/// @param merch, pointer to a pointer to where all the merch is stored
void list_merch_aux(webstore_merch_t **merch);


/// @brief Creates a cart to hold items
/// @param webstore, the webstore where all items and carts are stored
int webstore_create_cart(webstore_t *webstore);


/// @brief Removes merch based on name
/// @param webstore, the webstore where all items and carts are stored
/// @param cart_to_remove, specifies a cart to remove, which could already hold items
///        If the cart holds items, all items are removed
bool webstore_remove_cart(webstore_t *webstore, int cart_to_remove);


/// @brief Adds items to a cart 
/// @param webstore, the webstore where all items and carts are stored
/// @param item, the item to be added to the cart based on name
/// @param amount, amount of the item to be added to the cart
/// @param cart_select, the selected cart to store the item in 
/// @return An integer value based on how in went to add items into the cart:
///         1 - Sucessfully added the item
///         0 - Item didn't exist in cart
///         2 - Item was not available yet
///         3 - The chosen cart had not been created yet
int webstore_add_to_cart(webstore_t *webstore, char *item, int amount, int cart_select);


/// @brief Removes an item form a given cart
/// @param webstore, the webstore where all items and carts are stored
/// @param item_to_remove, name of the item to removed 
/// @param amount, amount of the item to be removed 
/// @param cart_selected, the cart from where to remove the item 
/// @return An integer value based on how in went to remove items into the cart:
///         1 - Sucessfully removed the item
///         0 - Item didn't exist in cart
///         2 - Item was not available yet
///         3 - The chosen cart had not been created yet
int webstore_remove_from_cart(webstore_t *webstore, char *item_to_remove, int amount, int cart_selected);


/// @brief Calculate cost of all items in a given cart
/// @param webstore, the webstore where all items and the carts are stored
/// @param cart_selected, the selected cart with all the items
/// @return An integer value based on how it went to calculate the cost of all items in a given cart
///         0 - The given cart had no items and could not calculate a cost
///        -1 - The given cart did not exist yet and could not calculate a cost
///         1 - Prints the total cost of all item in the given cart
int webstore_calculate_cost(webstore_t *webstore, int cart_selected);


/// @brief Removes merch based on name
/// @param webstore, the webstore where all items and the carts are stored
/// @param cart_selected, cart to checkout and buy all wares from
/// @return True if valid checkout, otherwise false
bool webstore_checkout(webstore_t *webstore, int cart_selected);


/// TODO - NOT YET IMPLIMENTED
/// @brief Undoes the previous command
/// @param webstore, the webstore where all items and the carts are stored
void webstore_undo(webstore_t *webstore);


/// @brief Initializes the entire webstore and allocates memory
/// @return An entire webstore
webstore_t *webstore_init();


/// @brief Removes the entire webstore
/// @param webstore, the webstore to be removed
void webstore_remove(webstore_t *webstore);


/// @brief Finds if the webstore already has a given merchendise
/// @param name, name of the ware searched for
/// @param webstore, the webstore where all wares are stored
/// @param searched_for_ware, the type of ware searched for as a string: "merch" or "item".
/// @return True if  a ware already exists in the webstore with a given name
bool webstore_is_already_item(char *name, webstore_t *webstore, char *searched_for_ware); 


/// @brief Finds if the webstore has no merchendise with a given name
/// @param name, name of the ware searched for
/// @param webstore, the webstore where all wares are stored
/// @param searched_for_ware, the type of ware searched for as a string: "merch" or "item".
/// @return True if no wares exists with the given name
bool webstore_is_no_item(char *name, webstore_t *webstore,  char *searched_for_ware);


/// @brief Creates the UI for the webstore menu
/// @param Webstore, the webstore the users can interact with
void webstore_menu(webstore_t *webstore);




////////TODO!!!!!!



/// @brief Creates the UI for the webstore menu
/// @param Webstore, the webstore the users can interact with
elem_t *webstore_hash_lookup(webstore_t *webstore, elem_t elem);


/// @brief Creates the UI for the webstore menu
/// @param Webstore, the webstore the users can interact with
int webstore_amount_in_stock(webstore_t *webstore, char *name);


/// @brief Creates the UI for the webstore menu
/// @param Webstore, the webstore the users can interact with
bool webstore_is_not_cart(webstore_t *webstore, int index);



