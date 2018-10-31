
#include <stdio.h>
#include "business_logic.h"
#include "common.h"
#include "utils.h"
#define webstore_list_len (int)(sizeof(list)/sizeof(list[0])) -1







// Helper funtion - Prints out if there is no item with that name
bool webstore_is_no_item_AUX(char *name, webstore_t *webstore) {
  elem_t key = {.p = name};
  if  (!webstore_hash_lookup(webstore, key)) {
    return true;
  }
  return false; 
}



// Initialize the webstore
// When choosing to leave, the webstore and all content is removed
int main() {
    webstore_t *webstore = webstore_init();;
    webstore = webstore_init();
    webstore_menu(webstore);
    webstore_remove(webstore);
    return 0;
}
