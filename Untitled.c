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