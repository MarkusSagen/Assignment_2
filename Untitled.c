elem_t *webstore_hash_lookup(webstore_t *webstore, elem_t elem) {
  return ioopm_hash_table_lookup(webstore->hash, elem);
}





int webstore_amount_in_stock(webstore_t *webstore, char *name) {
  elem_t elem;
  elem.p = name;
  elem_t *elem2 = ioopm_hash_table_lookup(webstore->hash, elem);
  if (!elem2->p) return 0;
  webstore_merch_t merch = (webstore_merch_t)(elem2->p);
  webstore_stock_t **stock = &merch->stock;
  int result = 0;
  while (*stock) {
    result += (*stock)->amount;
    stock = &(*stock)->next;
  }
  return result;
}
