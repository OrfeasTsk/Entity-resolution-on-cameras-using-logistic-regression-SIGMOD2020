inc = -I ./include/

all: project all_tests

project : main.o structs.o text_support.o logistic_regression.o 
	gcc main.o structs.o text_support.o logistic_regression.o -o project -lm

all_tests : all_tests.o queue_test.o stack_test.o rbt_test.o text_test.o heap_test.o ht_test.o structs.o text_support.o 
	gcc all_tests.o queue_test.o stack_test.o rbt_test.o text_test.o heap_test.o ht_test.o structs.o text_support.o -o all_tests -lm 

all_tests.o : ./tests/all_tests.c ./include/structs.h ./include/acutest.h ./include/all_tests.h
	gcc -Wall -c ./tests/all_tests.c $(inc)

queue_test.o : ./tests/queue_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/queue_test.c $(inc)
	
stack_test.o : ./tests/stack_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/stack_test.c $(inc)
	
rbt_test.o : ./tests/rbt_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/rbt_test.c $(inc)
	
text_test.o : ./tests/text_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/text_test.c $(inc)

heap_test.o : ./tests/heap_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/heap_test.c $(inc)
	
ht_test.o : ./tests/ht_test.c ./include/structs.h ./include/acutest.h
	gcc -Wall -c ./tests/ht_test.c $(inc)

main.o : main.c ./include/structs.h ./include/text_support.h ./include/logistic_regression.h
	gcc -Wall -c main.c $(inc)

structs.o : structs.c ./include/structs.h ./include/text_support.h
	gcc -Wall -c structs.c $(inc) 
	
text_support.o : text_support.c ./include/structs.h ./include/text_support.h
	gcc -Wall -c text_support.c $(inc) 

logistic_regression.o : logistic_regression.c ./include/structs.h ./include/logistic_regression.h
	gcc -Wall -c logistic_regression.c $(inc) 



clean:
	rm project all_tests main.o structs.o rbt_test.o stack_test.o queue_test.o text_test.o heap_test.o ht_test.o text_support.o all_tests.o logistic_regression.o related.csv unrelated.csv
