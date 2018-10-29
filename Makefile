











main: main.c user_interface.c business_logic.c business_logic.h utils.c utils.h hash_table.c hash_table.h linked_list.c linked_list.h iterator.c iterator.h common.h
	gcc -Wall -pedantic -g main.c user_interface.c business_logic.c utils.c hash_table.c linked_list.c iterator.c 







CC = gcc
LOADLIBES = -lm
CFLAGS = -Wall -O2 -g -pedantic -std=c11

DIP = common.h hash_table.h iterator.h linked_list.h utils.h business_logic.h



OFILE = user_interface.o business_logic.o utils.o hash_table.o linked_list.o iterator.o 
LIBS = -lm



#################################################################
#
# 1) To build the program with a main-file, just type:
#		make      		or:
#		make all
#
# ---------------------------------------------------------
#	From here you have a few options:
#	a) run the program main program
#	b) run the CUnit tests
#	c) run the freq_counter file
#
# 2a) To build and run the file, just type:
#		make exec 		or:
#		make prog
#		make p
#
# 2bi) To build the test in CUnit, just type:
#		make test
#		make t
#
# 2bii) To build the CUinit test and run through the make file:
#		make run_test	or:
#		make r_t
#
# 2c)  To build and run frequency counter:
#		make freq
#		make f
#
# 3) To clean up the make file, just type:
#		make clear
#		make c
#
# 4) To forcefully clean, type:
#		make remove
#		make f_clean
#		make force_clean
#
################################################################




.SILENT:
.PHONY: prog test_file clean #freq

all: prog test_file clean #freq 

prog: $(OFILE)  main.o
	$(CC) -o prog $(OFILE) main.o

main.o: main.c $(DIP)
	$(CC) $(CFLAGS) -c  main.c

user_interface.o: user_interface.c $(DIP)
	$(CC) $(CFLAGS) -c user_interface.c
	
business_logic.o: business_logic.c $(DIP)
	$(CC) $(CFLAGS) -c business_logic.c

common.o: common.c $(DIP)
	$(CC) $(CFLAGS) -c common.c

hash_table.o: hash_table.c $(DIP)
	$(CC) $(CFLAGS) -c hash_table.c

linked_list.o: linked_list.c $(DIP)
	$(CC) $(CFLAGS) -c linked_list.c

list_iterator.o: list_iterator.c $(DIP)
	$(CC) $(CFLAGS) -c list_iterator.c
	
utils.o: utils.c $(DIP)
	$(CC) $(CFLAGS) -c utils.c




r: run 
run: prog clean
	./prog

.PHONY: run

#################################
#								#
#	       Test files			#
#								#
#################################

test_file:  $(OFILE)  test.o
	$(CC) -o test_file $(OFILE) test.o -lcunit

test.o:  test.c $(DIP)
	$(CC) $(CFLAGS) -c test.c



t: test_r 
test_r: test_file clean
	./test_file

.PHONY: test_r



memtest: test 
test: test_file clean_test
	valgrind --leak-check=full ./test_file
	# valgrind --leak-check=full ./prog
	# valgrind --leak-check=full ./freq

.PHONY: memtest





#################################
#								#
#	       Clean     			#
#								#
#################################


clean_test:
	rm -f *.o

c: clean
clean:
	rm -f *o
	rm -f test_file example_file #freq

.PHONY: clean

fc: force_clean
f_clean: force_clean
clean-f: force_clean
cf: force_clean
clean_f: force_clean
clean_force: force_clean
force_clean:
	rm -f *.o *.txt
	rm -f prog test_file example_file test *.out  freq
	-rm -rf *.dSYM

.PHONY: force_clean
