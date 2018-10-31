webstore:
	gcc -Wall -pedantic -g main.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c 
	./a.out

memwebstore:
	gcc -Wall -pedantic -g main.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c  
	valgrind --leak-check=full ./a.out


test:
	gcc -Wall -pedantic -g test.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c -lcunit
	./a.out


memtest:
	gcc -Wall -pedantic -g test.c business_logic.c hash_table.c linked_list.c utils.c user_interface.c -lcunit
	valgrind ./a.out
