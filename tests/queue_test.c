#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"



void test_qcreate(void){	// Elegxoume an h QueueInit douleuei kai arxikopoiei swsta ta values

	Queue queue;
	QueueInit( &queue );
	TEST_ASSERT( QueueEmpty( &queue ) );
	TEST_ASSERT(queue.head==NULL);
	TEST_ASSERT(queue.tail==NULL);
	

}


void test_qinsert(void){
	
	Queue queue;
	QueueInit( &queue );
	
	
	//Elegxos me thn xrhsh integer

	int i,*p,*ptr;
	for( i = 0 ; i<100 ; i++){
		
		
		ptr=(int*)malloc(sizeof(int));
		*ptr = i;
		
		QueueInsert( &queue , (void**) &ptr );
		
		//Auksithike to megethos ths ouras?
		TEST_ASSERT(queue.count == (i + 1));
		
		//Sto telos mpainei to swsto value?
		p=(int*)(queue.tail->data);
		TEST_ASSERT(*p == *ptr);
	}
	
	//Diagrafh komvwn
	QueueDelete(&queue);
	
	//Diagrafthke h oura?
	TEST_ASSERT(QueueEmpty(&queue));
	TEST_ASSERT(queue.head==NULL);
	TEST_ASSERT(queue.tail==NULL);
	
}



void test_qconcat(void){
	int i;
	Queue* q1, *q2;
	char buff[10];
	Pair* pair;
	struct QueueNode* temp;
	
	q1 = (Queue*)malloc(sizeof(Queue));
	q2 = (Queue*)malloc(sizeof(Queue));
	
	QueueInit(q1);
	QueueInit(q2);
	
	Clique* cliq1 = (Clique*)malloc(sizeof(Clique));
	cliq1->related = q1;
	
	Clique* cliq2 = (Clique*)malloc(sizeof(Clique));
	cliq2->related = q2;
	
	
	for(i = 0; i < 50;  i++){ //Eisagwgh 50 pairs sthn q1
		
		sprintf(buff,"item%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		pair->cliq = cliq1;
		strcpy(pair->item->id,buff);
		QueueInit(&(pair->item->specs));
		QueueInsert(q1,(void**)&pair);
	}
	
	for( ; i < 100;  i++){ //Eisagwgh 50 pairs sthn q2
		
		sprintf(buff,"item%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		pair->cliq = cliq2;
		strcpy(pair->item->id,buff);
		QueueInit(&(pair->item->specs));
		QueueInsert(q2,(void**)&pair);
	}
	
	QueueConcat(q1,q2,cliq1);
	
	for(i = 0 ; (i < 100 && q1->head != NULL) ; i++ ){
		temp = q1->head;
		pair = (Pair*)(temp->data);
		TEST_ASSERT(pair->cliq->related == q1); //Deixnoun ola ta pairs sthn q1?
		PairDestroy(pair);
		if(q1->head == q1->tail)
			q1->tail = q1->head->next;
		q1->head=q1->head->next;
		free(temp);
		q1->count--;
	}
	
	//Diagrafthke h oura?
	TEST_ASSERT(QueueEmpty(q1));
	TEST_ASSERT(q1->head==NULL);
	TEST_ASSERT(q1->tail==NULL);

	
	free(q1);
	free(cliq1);
	free(cliq2);
	
}












