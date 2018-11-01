
#include <stdio.h>
#include "business_logic.h"
#include "utils.h"






// Initialize the webstore
// When choosing to leave, the webstore and all content is removed
int main() {
    webstore_t *webstore;
    webstore = webstore_init();
    webstore_menu(webstore);
    webstore_remove(webstore);
    return 0;
}
