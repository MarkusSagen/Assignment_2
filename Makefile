webstore:
	gcc main.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c
	./a.out

memwebstore:
	gcc main.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c
	valgrind ./a.out


test:
	gcc test.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c -lcunit
	./a.out


memtest:
	gcc test.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c -lcunit
	valgrind ./a.out
