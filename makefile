inc = -I ./include/


all: findSameItems queue_test stack_test rbt_test

findSameItems : main.o structs.o
	gcc main.o structs.o -o findSameItems
	
queue_test : queue_test.o structs.o
	gcc queue_test.o structs.o -o queue_test
	
stack_test : stack_test.o structs.o
	gcc stack_test.o structs.o -o stack_test
	
rbt_test : rbt_test.o structs.o
	gcc rbt_test.o structs.o -o rbt_test
	
	
queue_test.o : ./tests/queue_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/queue_test.c $(inc)
	
stack_test.o : ./tests/stack_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/stack_test.c $(inc)
	
	
rbt_test.o : ./tests/rbt_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/rbt_test.c $(inc)

main.o : main.c ./include/structs.h
	gcc -c main.c $(inc)

structs.o : structs.c ./include/structs.h
	gcc -c structs.c $(inc)





clean:
	rm findSameItems queue_test stack_test rbt_test main.o structs.o rbt_test.o stack_test.o queue_test.o 
