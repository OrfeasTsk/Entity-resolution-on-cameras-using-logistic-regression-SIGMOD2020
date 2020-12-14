#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"


void test_heapnodecreate(void){
	Details* details1;
	struct heapNode* temp;
	char name1[10]="First";
	
	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);

	temp=newNode(details1);
	TEST_ASSERT( temp->left == NULL );
	TEST_ASSERT( temp->right == NULL );
	TEST_ASSERT( strcmp( temp->data->name , name1 ) == 0  );
	TEST_ASSERT( temp->data->count == 5 );
	
	free(details1->name);
	free(details1);
	free(temp);
}


void test_swap(void){
	
	Details* details1, *details2;
	int result;	
	struct heapNode* temp1, *temp2;

	char name1[10]="First";
	char name2[10]="Second";
	
	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);
	
	details2 = (Details*)malloc(sizeof(Details));
	details2->name = (char*)malloc(strlen(name2) + 1);
	details2->count = 10;
	strcpy(details2->name,name2);
	
	temp1=newNode(details1);
	temp2=newNode(details2);
	
	result=swap(temp1, temp2);
	
	TEST_ASSERT( result == 1 );
	TEST_ASSERT( temp1->data->count == 10 );
	TEST_ASSERT( temp2->data->count == 5 );
	TEST_ASSERT( strcmp( temp1->data->name , name2 ) == 0);
	TEST_ASSERT( strcmp( temp2->data->name , name1 ) == 0);
	
	free(details1->name);
	free(details2->name);
	free(details1);
	free(details2);
	free(temp1);
	free(temp2);
	
	
}



void test_heapcreate(void){	// Elegxoume an h QueueInit douleuei kai arxikopoiei swsta ta values

	Heap heap;
	HeapInit(&heap);

	TEST_ASSERT( heap.head == NULL );
	TEST_ASSERT( heap.nodes == 0 );
	TEST_ASSERT( heap.height == 0);
	
	HeapDestroy(&heap);
	
}

void test_heapinsert(void){
	
	Details* details1, *details2;
	Heap heap;
	char name1[10]="First";
	char name2[10]="Second";
	
	HeapInit(&heap);

	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);
	
	HeapInsert(&heap,details1);	// insert first item
	
	TEST_ASSERT( heap.nodes == 1 );
	TEST_ASSERT( heap.height == 1);
	TEST_ASSERT( strcmp( heap.head->data->name , name1 ) == 0 );
	TEST_ASSERT( heap.head->data->count == 5 );
	
	details2 = (Details*)malloc(sizeof(Details));
	details2->name = (char*)malloc(strlen(name2) + 1);
	details2->count = 10;
	strcpy(details2->name,name2);
	
	HeapInsert(&heap,details2);	// insert second item
	
	free(details1->name);
	free(details2->name);
	free(details1);
	free(details2);

	HeapDestroy(&heap);

	
	
}


void test_heapifywords(void){
	int numBuckets = 5, i;
	
	
	Heap heap;
	HeapInit(&heap); 
	
	HashTable words;
	HashTable stopwords;
	HTinit(&words,numBuckets);
	HTinit(&stopwords, numBuckets);

	
	RBinit();
	
	char* temp1="First";
	char* temp2="Word";
	char* temp3="Is";
	char* temp4="This";
	char* temp5="Not";
	
	//add 4 times temp1
	InsertWord(&words, &stopwords, numBuckets,  temp1);
	InsertWord(&words, &stopwords, numBuckets,  temp1);
	InsertWord(&words, &stopwords, numBuckets,  temp1);
	InsertWord(&words, &stopwords, numBuckets,  temp1);
	//add 1 times temp2
	InsertWord(&words, &stopwords, numBuckets,  temp2);
	//add 4 times temp3
	InsertWord(&words, &stopwords, numBuckets,  temp3);
	InsertWord(&words, &stopwords, numBuckets,  temp3);
	InsertWord(&words, &stopwords, numBuckets,  temp3);
	InsertWord(&words, &stopwords, numBuckets,  temp3);
	//add 1 times temp4
	InsertWord(&words, &stopwords, numBuckets,  temp4);
	//add 3 times temp5
	InsertWord(&words, &stopwords, numBuckets,  temp5);
	InsertWord(&words, &stopwords, numBuckets,  temp5);
	
	
	for(i = 0 ; i < numBuckets; i++)
		HeapifyWords(&(words.buckets[i]),&heap);

	TEST_ASSERT(heap.nodes == 5); 

}







//Pinakas me tests
TEST_LIST = {
	{ "heap_create", test_heapcreate },
	{ "heap_insert", test_heapinsert},
	{ "heapnode_create", test_heapnodecreate },
	{ "swap_heapnodes", test_swap },
	{ "heapify_words", test_heapifywords },
	{ NULL, NULL } // NULL sto telos
};
