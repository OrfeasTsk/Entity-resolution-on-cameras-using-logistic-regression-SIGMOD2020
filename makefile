all: findSameItems queue_test stack_test rbt_test

findSameItems : main.o structs.o
	gcc main.o structs.o -o findSameItems
	
queue_test : queue_test.o structs.o
	gcc queue_test.o structs.o -o queue_test
	
stack_test : stack_test.o structs.o
	gcc stack_test.o structs.o -o stack_test
	
rbt_test : rbt_test.o structs.o
	gcc rbt_test.o structs.o -o rbt_test
	
	
queue_test.o : queue_test.c structs.h acutest.h
	gcc -c queue_test.c
	
stack_test.o : stack_test.c structs.h acutest.h
	gcc -c stack_test.c
	
	
rbt_test.o : rbt_test.c structs.h acutest.h
	gcc -c rbt_test.c

main.o : main.c structs.h
	gcc -c main.c

structs.o : structs.c structs.h
	gcc -c structs.c





clean:
	rm findSameItems queue_test stack_test rbt_test main.o structs.o rbt_test.o stack_test.o queue_test.o 
