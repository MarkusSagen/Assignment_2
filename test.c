
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


// Helper funtion - Prints out if there is item stored with that name
bool webstore_is_item_AUX(webstore_t *webstore, char *name) {
  elem_t key = {.p = name};
  if  (webstore_hash_lookup(webstore, key)) {
    return true;
  }
  return false; 
}


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






void webstore_add_merch_test(void)
{
  webstore_t *webstore = webstore_init();
    char *name_exist = "Hej";
    char *desc = "Godis";
    int price = 98281191;


    // Test first insert - check if is in storage
    webstore_add_merch(webstore, name_exist, desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, name_exist));

    // Test second insert - check if is in storage
    webstore_add_merch(webstore, "hjjkhasjkdasdj", desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, "hjjkhasjkdasdj"));


    // Check item in store
    webstore_add_merch(webstore, "", desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, ""));

    // Check item in store
    webstore_add_merch(webstore, "sg2666asd!", desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, "sg2666asd!"));

    // Check item not in store
    webstore_add_merch(webstore, "Grus", desc, price);
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, "Gru"));
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, "Gruss"));
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, "Grs"));
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, "rus"));


    webstore_remove(webstore);
}




void webstore_remove_merch_test(void)
{
   webstore_t *webstore = webstore_init();
    char *name_not_exist = "Grus";
    char *desc = "Godis";
    int price = 98191;


    // Try removing merch that dont exist
    webstore_remove_merch(webstore, name_not_exist);
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, name_not_exist));


    // Test removing a correct item - no longer stored in webstore and then remove
    webstore_add_merch(webstore, "Hej", desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, "Hej"));
    webstore_remove_merch(webstore, "Hej");
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, "Hej"));


    // Try and remove simular items and see that the right item is still there
    webstore_add_merch(webstore,    "hej123456", desc, price);
    webstore_remove_merch(webstore, "hej12345");
    webstore_remove_merch(webstore, "hej12346");
    webstore_remove_merch(webstore, "hej12356");
    webstore_remove_merch(webstore, "hej12456");
    webstore_remove_merch(webstore, "hej13456");
    webstore_remove_merch(webstore, "hej23456");
    webstore_remove_merch(webstore, "he123456");
    webstore_remove_merch(webstore, "hj123456");
    webstore_remove_merch(webstore, "ej123456");
    webstore_remove_merch(webstore, "1hej123456");
    webstore_remove_merch(webstore, "hej1234561");
    webstore_remove_merch(webstore, "hej1234562");
    webstore_remove_merch(webstore, "hej123456h");
    webstore_remove_merch(webstore, "123456");
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, "hej123456"));



    webstore_add_merch(webstore,    "a", desc, price);
    webstore_remove_merch(webstore, "");
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, "a"));


    webstore_remove(webstore);
}




void webstore_edit_merch_test(void)
{
   webstore_t *webstore = webstore_init();
    char *merch_to_edit = "hejsan12345";
    char *new_name = "abc";
    char *desc = "";
    int price = 1;


    // Try edit merch that dont exist
    webstore_edit_merch(webstore, merch_to_edit, new_name, desc, price);
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, new_name));


    // Test edit a correct item - then remove that item
    webstore_add_merch(webstore, merch_to_edit, desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, merch_to_edit));
    webstore_edit_merch(webstore, merch_to_edit, new_name, desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, new_name));
    webstore_remove_merch(webstore, new_name);
    CU_ASSERT_FALSE(webstore_is_item_AUX(webstore, new_name));


    // Test edit merch to same name again
    webstore_add_merch(webstore, merch_to_edit, desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, merch_to_edit));
    webstore_edit_merch(webstore, merch_to_edit, merch_to_edit, desc, price);
    CU_ASSERT_TRUE(webstore_is_item_AUX(webstore, merch_to_edit));


    webstore_remove(webstore);
}




// Cant test removing from stock here, since thats "checkout"
void webstore_replenish_test(void)
{
    webstore_t *webstore = webstore_init();

    char *merch1 = "hej12jaj23";
    char *merch2 = "EnGladAnka";
 
    char *desc = "En rolig beskrivning";
    char *location = "H20";

    int no_item = 0;
    int amount = 10;
    int amount2 = 5;
    int price = 10;


    // test replenich merch not in store
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch1), no_item);

    // test adding item and replenish with zero
    webstore_add_merch(webstore, merch1, desc, price);
    webstore_replenish(webstore, merch1, location, no_item);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch1), no_item);

    // test replenish with negative numbers
    webstore_replenish(webstore, merch1, location, -1);
    CU_ASSERT_NOT_EQUAL(webstore_amount_in_stock(webstore, merch1), -1);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch1), no_item);

    // test replenish when adding amount
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch1), 0);
    webstore_replenish(webstore, merch1, location, amount);           // added 10 
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch1), 10);  // Check if has 10
       
       
    // Test adding to several places 
    webstore_add_merch(webstore, merch2, desc, price);
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch2), 0);
    webstore_replenish(webstore, merch2, "A20", 10);           // added 10 
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch2), 10);  // Check if has 10
    webstore_replenish(webstore, merch2, "A20", 50);           // added 10  
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch2), 60);  // Check if has 10 + 50

    webstore_replenish(webstore, merch2, "G83", 40);           // added 10  
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch2), 100);  // Check if has 100 in total

    webstore_replenish(webstore, merch2, "G83", 0);           // added 10  
    CU_ASSERT_EQUAL(webstore_amount_in_stock(webstore, merch2), 100);  // Check if has 100 in total

    

     webstore_remove(webstore);
}




void webstore_create_cart_test(void)
{
    webstore_t *webstore = webstore_init();
    
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);
    int cart_nr3 = webstore_create_cart(webstore);
    int cart_nr4 = webstore_create_cart(webstore);
    int cart_nr5 = webstore_create_cart(webstore);
    CU_ASSERT_EQUAL(cart_nr1, 1);
    CU_ASSERT_EQUAL(cart_nr2, 2);
    CU_ASSERT_EQUAL(cart_nr3, 3);
    CU_ASSERT_EQUAL(cart_nr4, 4);
    CU_ASSERT_EQUAL(cart_nr5, 5);

    
    webstore_remove(webstore);
}




//TODO 
void webstore_add_to_cart_test(void)
{
    webstore_t *webstore = webstore_init();
    
    char *name = "cola";
    char *item_fail0 = "Ogiltigt";
    char *item_fail2 = "godis1234";
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
    int success = webstore_add_to_cart(webstore, name, take_amount, cart_nr1);
    CU_ASSERT_EQUAL(success, 1);
    
    int fail0 = webstore_add_to_cart(webstore, item_fail0, take_amount, cart_nr1);
    CU_ASSERT_EQUAL(fail0, 0);
    
    //int fail2 = webstore_add_to_cart(webstore, item_fail2, take_amount, cart_nr1);
    //CU_ASSERT_EQUAL(fail2, 2);
    
    
    int fail3 = webstore_add_to_cart(webstore, name, take_amount, cart_select_fail3);
    CU_ASSERT_EQUAL(fail3, 3);

    webstore_remove(webstore);

}





void webstore_remove_cart_test(void)
{
    webstore_t *webstore = webstore_init();
    

    char *merch1 = "hej12jaj23";
    char *merch2 = "EnGladAnka";
 
    char *desc = "En rolig beskrivning";
    char *location = "H20";

    int no_item = 0;
    int amount = 10;
    int amount2 = 5;
    int price = 10;



    // test remove cart that dont exist
    bool no_cart_removed = !webstore_remove_cart(webstore, 1);
    CU_ASSERT_TRUE(no_cart_removed);

    // add cart
    int cart_nr1 = webstore_create_cart(webstore);
    int cart_nr2 = webstore_create_cart(webstore);

    // test removing a cart
    bool cart1_gone = webstore_remove_cart(webstore, cart_nr1);
    CU_ASSERT_TRUE(cart1_gone);

    // add more carts
    int cart_nr3 = webstore_create_cart(webstore);
    int cart_nr4 = webstore_create_cart(webstore);
    CU_ASSERT_EQUAL(cart_nr3, 3);

    // test removing out of order
    bool cart2_gone = webstore_remove_cart(webstore, cart_nr2);
    CU_ASSERT_TRUE(cart2_gone);
    bool cart4_gone = webstore_remove_cart(webstore, cart_nr4);
    CU_ASSERT_TRUE(cart4_gone);
    bool cart3_gone = webstore_remove_cart(webstore, cart_nr3);
    CU_ASSERT_TRUE(cart3_gone);



    // // test removing when cart has wares
    webstore_add_merch(webstore ,merch1, desc, price);
    webstore_add_merch(webstore, merch2, desc, price);
    webstore_replenish(webstore, merch1, "A20", 100);
    webstore_replenish(webstore, merch2, location, 10);

    int cart_nr5 = webstore_create_cart(webstore);
    int cart_nr6 = webstore_create_cart(webstore);
    webstore_add_to_cart(webstore, merch1, 1, cart_nr5); 
    bool cart5_gone = webstore_remove_cart(webstore, cart_nr5);
    CU_ASSERT_TRUE(cart5_gone);

    webstore_add_to_cart(webstore, merch1, 80, cart_nr6);
    webstore_add_to_cart(webstore, merch2, 10, cart_nr6);
    bool cart6_gone = webstore_remove_cart(webstore, cart_nr6);
    CU_ASSERT_TRUE(cart6_gone);
    

    webstore_remove(webstore);
}



//TODO
void webstore_remove_from_cart_test(void)
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
    CU_ASSERT_EQUAL(success, 1);
    
    
    int fail_0 = webstore_remove_from_cart(webstore, item_fail0, take_amount, cart_nr1 );
    CU_ASSERT_EQUAL(fail_0, 0);
    
    int fail_3 =webstore_remove_from_cart(webstore, name, take_amount, cart_fail3 );
    CU_ASSERT_EQUAL(fail_3, 3);
    
    int fail_2 = webstore_remove_from_cart(webstore, name, fail_amount2, cart_nr1 );
    CU_ASSERT_EQUAL(fail_2, 2);
    

    
    webstore_remove(webstore);
}



//TODO
void webstore_calculate_cost_test(void)
{
     webstore_t *webstore = webstore_init();
    
    char *name1 = "abc";
    char *desc1 = "en cola burk";
    int price1 = 1;
    char *location1 = "A20";
    int in_amount1 = 200;
    int get_amount1 = 100;

    
    char *name2 = "def";
    char *desc2 = "en cola burk";
    int price2 = 10;
    char *location2 = "A20";
    int in_amount2 = 200;
    int get_amount2 = 10;
    
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



//TODO
void webstore_checkout_test(void)
{
webstore_t *webstore = webstore_init();
    char *name1 = "cola";
    char *desc1 = "en cola burk";
    int price1 = 1;
    char *location1 = "A20";
    int in_amount1 = 200;
    int get_amount1 = 100;

    
    char *name2 = "cola23678";
    char *desc2 = "en cola burk";
    int price2 = 10;
    char *location2 = "A20";
    int in_amount2 = 200;
    int get_amount2 = 10;

    
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
	webstore_add_to_cart(webstore, name1, 100, cart_nr2);
    webstore_checkout(webstore, cart_nr2);
	bool fail0 = (webstore_add_to_cart(webstore, name1, 100, cart_nr1)) == 2;
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
	(NULL == CU_add_test( pSuiteEntries, "Test add_merch()", webstore_add_merch_test)) ||
	(NULL == CU_add_test( pSuiteEntries, "Test remove_merch()", webstore_remove_merch_test)) ||
	(NULL == CU_add_test( pSuiteEntries, "Test edit_merch()", webstore_edit_merch_test)) ||
	(NULL == CU_add_test( pSuiteEntries, "Test replenish()", webstore_replenish_test)) ||

        (NULL == CU_add_test( pSuiteEntries, "Test create_cart()", webstore_create_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test remove_cart()", webstore_remove_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test add_to_cart()", webstore_add_to_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test remove_from_cart()", webstore_remove_from_cart_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test calculate_cost()", webstore_calculate_cost_test)) ||
        (NULL == CU_add_test( pSuiteEntries, "Test checkout()", webstore_checkout_test)))    
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

