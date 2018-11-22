
#include "common.h"
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
#include "business_logic.h"
#include <CUnit/CUnit.h> //install via brew install cunit
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>





//// Asserting initialization

// Test for entries
int init_entries(void)
{
  return 0;
}

int clear_entries(void)
{
  return 0;
}











    
    /// @brief Adds merch to webstore based on unique name
/// @param webstore, the webstore where all merch is stored
/// @param name, name of the new merchendise to be added
/// @param desc, description of the new merchendise to be added
/// @param price, price of the new merchendise to be added
/// @param price, price of the new merchendise to be added
void webstore_add_merch_test(void)
{
  webstore_t *webstore = webstore_init();
    char *name = "hej";
    char *name2 = "";
    char *desc = "";
    int price = 1;
    int price2 = 1;
     webstore_add_merch(webstore, name2, desc, price);
    CU_ASSERT(webstore_is_no_item_AUX(name, webstore));
        webstore_add_merch(webstore, name, desc, price2);
    CU_ASSERT(webstore_is_no_item_AUX(name, webstore));
    webstore_add_merch(webstore, name, desc, price);
    CU_ASSERT(!webstore_is_no_item_AUX(name, webstore));
    webstore_remove(webstore);
}


/// @brief Removes merch based on name
/// @param webstore, the webstore where all merch is stored
/// @param remove, name of the chosen merchendise to be removed
void webstore_remove_merch_test(void)
{
   webstore_t *webstore = webstore_init();
    char *name2 = "";
    char *name = "hej";
    char *desc = "";
    int price = 10;
    webstore_add_merch(webstore, name, desc, price);
    CU_ASSERT(!webstore_is_no_item_AUX(name, webstore));
        webstore_remove_merch(webstore, name2);
    CU_ASSERT(!webstore_is_no_item_AUX(name, webstore));
    webstore_remove_merch(webstore, name);
    CU_ASSERT(webstore_is_no_item_AUX(name, webstore));
     webstore_remove(webstore);
}


/// @brief Edits an existing merchendise based on name
/// @param webstore, the webstore where all merch is stored
/// @param merch_to_edit, name of existing merchendise that should be edited
/// @param name, updated name of the edited merchendise
/// @param desc, updated description of the edited merchendise
/// @param price, updated price of the edited merchendise
void webstore_edit_merch_test(void)
{
   webstore_t *webstore = webstore_init();
    char *merch_to_edit = "hejsan";
    char *name = "abc";
    char *desc = "";
    int price = 1;
    webstore_add_merch(webstore, merch_to_edit, desc, price);
    CU_ASSERT(webstore_is_no_item_AUX(name, webstore));
    webstore_edit_merch(webstore, merch_to_edit, name, desc, price);
     CU_ASSERT(!webstore_is_no_item_AUX(name, webstore));
      webstore_remove(webstore);
}


/// @brief Replenishes merchendise based on name and loaction
/// @param merch_to_update, the name of the merchendise to update the amount
/// @param location, location of the to be updatet
///        If location is added where no previous merchendise was loacted, it will add it there
///        There can be same merchendise at multiple locations
/// @param amount, amount to be added of the merchendise to the given location
void webstore_replenish_test(void)
{
   webstore_t *webstore = webstore_init();
    char *merch_to_update = "hej";
    char *desc = "";
    char *location = "H20";
     char *location2 = "H21";
    int amount = 10;
     int amount2 = 5;
    int price = 10;
    webstore_add_merch(webstore, merch_to_update, desc, price);
    webstore_replenish(webstore, merch_to_update, location, 0);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch_to_update), 0);
    webstore_replenish(webstore, merch_to_update, location, amount);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch_to_update), 10);
        webstore_replenish(webstore, merch_to_update, location, amount);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch_to_update), 20);
            webstore_replenish(webstore, merch_to_update, location2, amount2);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch_to_update), 25)
     webstore_remove(webstore);
}















/// @brief Creates a cart to hold items
/// @param webstore, the webstore where all items and carts are stored
void webstore_create_cart_test(void)
{
    webstore_t *webstore = webstore_init();
    
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);
    CU_ASSERT_PTR_NOT_NULL(cart_nr1);
    CU_ASSERT_PTR_NOT_NULL(cart_nr2);
    CU_ASSERT_EQUAL(cart_nr1, 1);
    CU_ASSERT_EQUAL(cart_nr2, 2);
    
    webstore_remove(webstore);
}


/// @brief Removes merch based on name
/// @param webstore, the webstore where all items and carts are stored
/// @param cart_to_remove, specifies a cart to remove, which could already hold items
///        If the cart holds items, all items are removed
void webstore_remove_cart_test(void)
{
     webstore_t *webstore = webstore_init();
    
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);
    CU_ASSERT_PTR_NOT_NULL(cart_nr);
    CU_ASSERT_EQUAL(cart_nr1, 1);
    CU_ASSERT_EQUAL(cart_nr2, 2);
    
    int cart_to_remove = 1;
    bool cart1_gone = webstore_remove_cart(webstore, cart_to_remove);
    CU_ASSERT_TRUE(cart1_gone);
    
    webstore_remove(webstore);
}


/// @brief Adds items to a cart
/// @param webstore, the webstore where all items and carts are stored
/// @param item, the item to be added to the cart based on name
/// @param amount, amount of the item to be added to the cart
/// @param cart_select, the selected cart to store the item in
/// @return An integer value based on how in went to add items into the cart:
///         1 - Successfully added the item
///         0 - Item didn't exist in cart
///         2 - Item was not available yet
///         3 - The chosen cart had not been created yet
int webstore_add_to_cart_test(void)
{
    webstore_t *webstore = webstore_init();
    
    char *name = "cola";
    char *item_fail0 = "Ogiltigt";
    char *item_fail2 = "godis";
    char *desc = "en cola burk";
    int price = 1;
    char *location = "A20";
    int in_amount = 200;
    int take_amount = 5;
    int cart_select_fail3 = 25;

    
    // Add items
    webstore_add_merch(webstore, name, desc, price);
    webstore_add_merch(webstore, item_fail2, desc, price);
    webstore_replenish(webstore, name, location, in_amount);
    
    
    int cart_nr1 = webstore_create_cart(webstore);
    int success = webstore_add_to_cart(webstore, item, take_amount, cart_nr1);
    CU_ASSERT_EQUAL(success, 1);
    
    int fail0 = webstore_add_to_cart(webstore, item_fail0, take_amount, cart_select);
    CU_ASSERT_EQUAL(fail0, 0);
    
    int fail2 = webstore_add_to_cart(webstore, item_fail2, take_amount, cart_select);
    CU_ASSERT_EQUAL(fail2, 2);
    
    
    int fail3 = webstore_add_to_cart(webstore, item, take_amount, cart_select_fail3);
    CU_ASSERT_EQUAL(fail3, 3);
    
    webstore_remove(webstore);
}


/// @brief Removes an item form a given cart
/// @param webstore, the webstore where all items and carts are stored
/// @param item_to_remove, name of the item to removed
/// @param amount, amount of the item to be removed
/// @param cart_selected, the cart from where to remove the item
/// @return An integer value based on how in went to remove items into the cart:
///         1 - Successfully removed the item
///         0 - Item didn't exist in cart
///         2 - Item was not available yet
///         3 - The chosen cart had not been created yet
int webstore_remove_from_cart_test(void)
{
    
    webstore_t *webstore = webstore_init();
    
    char *name = "cola";
    char *item_fail0 = "Ogiltigt";
    int fail_amount2 = 99999;
    char *desc = "en cola burk";
    int price = 1;
    char *location = "A20";
    int in_amount = 200;
    int get_amount = 100;
    int take_amount = 5;
    int cart_fail3 = 99;

    
    
    // Add items
    webstore_add_merch(webstore, name, desc, price);
    webstore_replenish(webstore, name, location, in_amount);
    
    
    int cart_nr1 = webstore_create_cart(webstore);
    webstore_add_to_cart(webstore, name, get_amount, cart_nr1); // now has 5 colas
    
    
    
    
    int success = webstore_remove_from_cart(webstore, name, take_amount, cart_nr1 );
    CU_ASSERT_EQUAL(success, 0);
    
    
    int fail_0 = webstore_remove_from_cart(webstore, item_fail0, take_amount, cart_nr1 );
    CU_ASSERT_EQUAL(fail_0, 0);
    
    int fail_3 =webstore_remove_from_cart(webstore, name, take_amount, cart_fail3 );
    CU_ASSERT_EQUAL(fail_3, 3);
    
    int fail_2 = webstore_remove_from_cart(webstore, name, fail_amount2, cart_nr1 );
    CU_ASSERT_EQUAL(fail_2, 2);
    

    
    webstore_remove(webstore);
}

/// @brief Calculate cost of all items in a given cart
/// @param webstore, the webstore where all items and the carts are stored
/// @param cart_selected, the selected cart with all the items
/// @return An integer value based on how it went to calculate the cost of all items in a given cart
///         0 - The given cart had no items and could not calculate a cost
///        -1 - The given cart did not exist yet and could not calculate a cost
///         1 - Prints the total cost of all item in the given cart
void webstore_calculate_cost_test(void)
{
     webstore_t *webstore = webstore_init();
    
    char *name1 = "cola";
    char *desc1 = "en cola burk";
    int price1 = 1;
    char *location1 = "A20";
    int in_amount1 = 200;
    int get_amount1 = 100;
    int take_amount1 = 5;
    
    char *name2 = "cola";
    char *desc2 = "en cola burk";
    int price2 = 10;
    char *location2 = "A20";
    int in_amount2 = 200;
    int get_amount2 = 10;
    int take_amount2 = 5;
    
    int cart_fail1 = 99;

    
    // Add items
    webstore_add_merch(webstore, name1, desc1, price1);
    webstore_replenish(webstore, name1, location1, in_amount1);
    
    webstore_add_merch(webstore, name2, desc2, price2);
    webstore_replenish(webstore, name2, location2, in_amount2);
    
    
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);
    webstore_add_to_cart(webstore, name1, get_amount1, cart_nr1); // now has 100 colas
    webstore_add_to_cart(webstore, name2, get_amount2, cart_nr1); // now has 10
    
    
    
    // Assert tests
    
    int success = webstore_calculate_cost(webstore, cart_nr1);
    CU_ASSERT_EQUAL(success, 200);
    
    int fail1 = webstore_calculate_cost(webstore, cart_fail1);
    CU_ASSERT_EQUAL(fail1, -1);
    
    int fail0 = webstore_calculate_cost(webstore, cart_nr2);
    CU_ASSERT_EQUAL(fail0, 0);
    
    
    webstore_remove(webstore);
    
}


/// @brief Removes merch based on name
/// @param webstore, the webstore where all items and the carts are stored
/// @param cart_selected, cart to checkout and buy all wares from
/// @return True if valid checkout, otherwise false
void webstore_checkout_test(void)
{
    char *name1 = "cola";
    char *desc1 = "en cola burk";
    int price1 = 1;
    char *location1 = "A20";
    int in_amount1 = 200;
    int get_amount1 = 100;
    int take_amount1 = 5;
    
    char *name2 = "cola";
    char *desc2 = "en cola burk";
    int price2 = 10;
    char *location2 = "A20";
    int in_amount2 = 200;
    int get_amount2 = 10;
    int take_amount2 = 5;
    
    int cart_fail1 = 99;
    
    
    // Add items
    webstore_add_merch(webstore, name1, desc1, price1);
    webstore_replenish(webstore, name1, location1, in_amount1);
    
    webstore_add_merch(webstore, name2, desc2, price2);
    webstore_replenish(webstore, name2, location2, in_amount2);
    
    
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);
    webstore_add_to_cart(webstore, name1, get_amount1, cart_nr1); // now has 100 colas
    webstore_add_to_cart(webstore, name2, get_amount2, cart_nr1); // has 10
    
    
    
    // Assert tests
    bool success = webstore_checkout(webstore, cart_nr1);
    CU_ASSERT_TRUE(success);
    
    // No cart
    bool fail1 = webstore_checkout(webstore, cart_fail1);
    CU_ASSERT_FALSE(fail1);
    
    // No items
    bool fail0 = webstore_checkout(webstore, cart_nr2);
    CU_ASSERT_FALSE(fail0);
    


    webstore_remove(webstore);
}






int main()
{
    
    //// Initialize initials
    CU_pSuite pSuiteEntries     = NULL;
    
    
    
    //// Initialize and print error messages if errors
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    
    //// Here we start to assert tests
    pSuiteEntries   = CU_add_suite("Test all functions with insertion and removal: ", init_entries, clear_entries);
   
    
    
    
    
    if (NULL == pSuiteEntries)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
   
    
    
    //// Test Hash table
    // Testing hashtable create and destroy
    if (
        (NULL == CU_add_test( pSuiteEntries, "Test create_cart()", webstore_create_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test remove_cart()", webstore_remove_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test add_to_cart()", webstore_add_to_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test remove_from_cart()", webstore_remove_from_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test calculate_cost()", webstore_calculate_cost_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test checkout()", webstore_checkout_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    
    
    
    
    //// Final state:
    // Run test, display errors and clear registry
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
