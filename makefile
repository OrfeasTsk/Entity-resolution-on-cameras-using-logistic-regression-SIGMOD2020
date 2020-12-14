inc = -I ./include/


all: project queue_test stack_test rbt_test text_test heap_test ht_test

project : main.o structs.o text_support.o 
	gcc main.o structs.o text_support.o -o project -lm

	
queue_test : queue_test.o structs.o text_support.o 
	gcc queue_test.o structs.o text_support.o -o queue_test -lm
	
stack_test : stack_test.o structs.o text_support.o 
	gcc stack_test.o structs.o text_support.o -o stack_test -lm
	
rbt_test : rbt_test.o structs.o text_support.o 
	gcc rbt_test.o structs.o text_support.o -o rbt_test -lm
	
text_test : text_test.o structs.o text_support.o 
	gcc text_test.o structs.o text_support.o -o text_test -lm

heap_test : heap_test.o structs.o text_support.o 
	gcc heap_test.o structs.o text_support.o -o heap_test -lm

ht_test : ht_test.o structs.o text_support.o 
	gcc ht_test.o structs.o text_support.o -o ht_test -lm
	
queue_test.o : ./tests/queue_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/queue_test.c $(inc)
	
stack_test.o : ./tests/stack_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/stack_test.c $(inc)
	
	
rbt_test.o : ./tests/rbt_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/rbt_test.c $(inc)
	
text_test.o : ./tests/text_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/text_test.c $(inc)

heap_test.o : ./tests/heap_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/heap_test.c $(inc)
	
ht_test.o : ./tests/ht_test.c ./include/structs.h ./include/acutest.h
	gcc -c ./tests/ht_test.c $(inc)

main.o : main.c ./include/structs.h ./include/text_support.h
	gcc -c main.c $(inc)

structs.o : structs.c ./include/structs.h ./include/text_support.h
	gcc -c structs.c $(inc) 
	
text_support.o : text_support.c ./include/structs.h ./include/text_support.h
	gcc -c text_support.c $(inc) 




clean:
	rm project queue_test stack_test rbt_test text_test heap_test ht_test main.o structs.o rbt_test.o stack_test.o queue_test.o text_test.o heap_test.o ht_test.o text_support.o 
