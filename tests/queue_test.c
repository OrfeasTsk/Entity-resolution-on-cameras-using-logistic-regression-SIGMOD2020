#include "acutest.h"
#include "structs.h"



void test_qcreate(void){	// elegxoume an h QueueInit douleuei kai arxikopoiei swsta ta values

	Queue queue;
	QueueInit( &queue );
	TEST_ASSERT( QueueEmpty( &queue ) );
	TEST_ASSERT(queue.head==NULL);
	TEST_ASSERT(queue.tail==NULL);
	

}


void test_qinsert(void){
	
	Queue queue;
	QueueInit( &queue );
	
	struct QueueNode* temp,*curr;
	
	//tha eleksoume an h queue douleuei me thn xrhsh integer
	int **array=(int**)malloc(100*sizeof(int*));
	int i,*p;
	for( i = 0 ; i<100 ; i++){
		
		
		array[i]=(int*)malloc(sizeof(int));
		*array[i] = i;
		
		QueueInsert( &queue , (void**) &array[i] );
		
		// tha elegksoyme an auksithike to megethos ths listas
		TEST_ASSERT(queue.count == (i + 1));
		
		//elegxoume an sto telos mpainei to swsto value
		p=(int*)(queue.tail->data);
		TEST_ASSERT(*p == *array[i]);
	}
	
	//diagrafh komvwn
	for( i = 0 ; (i < 100 && queue.head != NULL) ; i++ ){
		temp=queue.head;
		free(temp->data);
		if(queue.head == queue.tail)
			queue.tail = queue.head->next;
		queue.head=queue.head->next;
		free(temp);
		queue.count--;
	}
	
	//elegxoume an diagrafthke h lista
	TEST_ASSERT(QueueEmpty(&queue));
	TEST_ASSERT(queue.head==NULL);
	TEST_ASSERT(queue.tail==NULL);
	free(array);
	
}

















//Pinakas me tests
TEST_LIST = {
	{ "queue_create", test_qcreate },
	{ "queue_insert_next", test_qinsert },
	/*{ "list_remove_next", test_remove_next },
	{ "list_find", test_find },
	{ "list_find_node", test_find_node },*/
	{ NULL, NULL } // NULL sto telos
};
