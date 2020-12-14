#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"
#define numBuckets 100


void test_heapnodecreate(void){		// Elegxoume an h newNode douleuei kai arxikopoiei swsta ta values
	Details* details1 ;
	struct heapNode* temp ;
	char name1[10] = "First" ;
	
	// dhmiourgoume ta details pou prepei na baloume
	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);

	temp=newNode(details1);
	
	// kanoume ta analoga test kai elegxoume an ola exoun bei swsta
	TEST_ASSERT( temp->left == NULL );
	TEST_ASSERT( temp->right == NULL );
	TEST_ASSERT( strcmp( temp->data->name , name1 ) == 0  );
	TEST_ASSERT( temp->data->count == 5 );
	
	//frees
	free( details1->name );
	free( details1 );
	free( temp );
}


void test_swap(void){		// elegxoume an h swap douleuei kai allazei to periexomeno twn details
	
	Details* details1, *details2;
	int result;	
	struct heapNode* temp1, *temp2;

	char name1[10]="First";
	char name2[10]="Second";
	
	// edw arxikopoioume ta details 
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
	
	// result periexei thn timh 1 an egine h allagh
	result=swap(temp1, temp2);
	
	TEST_ASSERT( result == 1 );			// prepei na epistrepsei 1 afou to count tou deuterou einai megalutero 
	// elegxoume an exei ginei h allagh
	TEST_ASSERT( temp1->data->count == 10 );	
	TEST_ASSERT( temp2->data->count == 5 );
	TEST_ASSERT( strcmp( temp1->data->name , name2 ) == 0);
	TEST_ASSERT( strcmp( temp2->data->name , name1 ) == 0);
	
	//frees
	free(details1->name);
	free(details2->name);
	free(details1);
	free(details2);
	free(temp1);
	free(temp2);
	
	
}



void test_heapcreate(void){	// Elegxoume an h HeapInit douleuei kai arxikopoiei swsta ta values

	Heap heap;
	HeapInit(&heap);		

	TEST_ASSERT( heap.head == NULL );
	TEST_ASSERT( heap.nodes == 0 );
	TEST_ASSERT( heap.height == 0);
	
	HeapDestroy(&heap);
	
}

void test_heapinsert(void){		// Elegxoume an h HeapInsert douleuei kai mpainoun swsta oi times kai allazoun oi analoges times tou heap
	
	Details* details1, *details2;
	Heap heap;
	char name1[10]="First";
	char name2[10]="Second";
	
	HeapInit(&heap);
	
	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);
	
	HeapInsert(&heap,details1);	// eisagoume to prwto item 
	
	TEST_ASSERT( heap.nodes == 1 );
	TEST_ASSERT( heap.height == 1);
	TEST_ASSERT( strcmp( heap.head->data->name , name1 ) == 0 );
	TEST_ASSERT( heap.head->data->count == 5 );
	
	details2 = (Details*)malloc(sizeof(Details));
	details2->name = (char*)malloc(strlen(name2) + 1);
	details2->count = 10;
	strcpy(details2->name,name2);
	
	HeapInsert(&heap,details2);	// eisagoume to deutero item
	TEST_ASSERT( heap.nodes == 2 );
	TEST_ASSERT( heap.height == 2);
	
	HeapDestroy(&heap);

}


void test_heapremovefirst(void){	// elegxoume an h HeapRemoveFirst douleuei kai afairei swsta ta items allazontas tis analoges times tou heap
	
	Details* details1, *details2, *details;
	Heap heap;
	char name1[10]="First";
	char name2[10]="Second";
	
	HeapInit(&heap);

	// dhmiourgia details
	details1 = (Details*)malloc(sizeof(Details));
	details1->name = (char*)malloc(strlen(name1) + 1);
	details1->count = 5;
	strcpy(details1->name,name1);	
	HeapInsert(&heap,details1);	// insert first item
	
	details2 = (Details*)malloc(sizeof(Details));
	details2->name = (char*)malloc(strlen(name2) + 1);
	details2->count = 10;
	strcpy(details2->name,name2);	
	HeapInsert(&heap,details2);	// insert second item
	
	//afairoume to prwto details kai elegxoume an o heap allazei swsta kai an bgazei to item me to megalutero count
	details= HeapRemoveFirst(&heap);
	TEST_ASSERT( heap.nodes == 1 );
	TEST_ASSERT( heap.height == 1);
	TEST_ASSERT( strcmp( details->name , name2 ) == 0 );
	TEST_ASSERT( details->count == 10 );
	
	// afairoume kai to deutero details kanontas paromoious elegxous
	details= HeapRemoveFirst(&heap);
	TEST_ASSERT( heap.nodes == 0 );
	TEST_ASSERT( heap.height == 0 );
	TEST_ASSERT( strcmp( details->name , name1 ) == 0 );
	TEST_ASSERT( details->count == 5 );
	
	
	
}



void test_heapifywords(void){	// Elegxoume an h HeapifyWords douleuei swsta kai bazei swsta sto heap tis lekseis
	
	int i;
	
	RBinit();
	Heap heap;
	HeapInit(&heap); 
	
	HashTable words;
	HashTable stopwords;
	HTinit(&words);
	HTinit(&stopwords);

	char* temp1="First";
	char* temp2="Word";
	char* temp3="Is";
	char* temp4="This";
	char* temp5="Not";
	
	// Arxika bazoume tis lekseis se ena Hash Table
	// prosthetoume 4 fores thn temp1
	InsertWord(&words, &stopwords, temp1);
	InsertWord(&words, &stopwords, temp1);
	InsertWord(&words, &stopwords, temp1);
	InsertWord(&words, &stopwords, temp1);
	// prosthetoume 1 fores thn temp1
	InsertWord(&words, &stopwords, temp2);
	// prosthetoume 4 fores thn temp3
	InsertWord(&words, &stopwords, temp3);
	InsertWord(&words, &stopwords, temp3);
	InsertWord(&words, &stopwords, temp3);
	InsertWord(&words, &stopwords, temp3);
	// prosthetoume 1 fores thn temp4
	InsertWord(&words, &stopwords, temp4);
	// prosthetoume 4 fores thn temp5
	InsertWord(&words, &stopwords, temp5);
	InsertWord(&words, &stopwords, temp5);
	
	// Gia kathe bucket pou exei dhmiourgithei kanoyme Heapify
	for(i = 0 ; i < numBuckets; i++)
		HeapifyWords(&(words.buckets[i]),&heap);

	TEST_ASSERT(heap.nodes == 5); // oi lekseis prepei na einai 5
	TEST_ASSERT(heap.height == 3); // kai to upsos 3


	HeapDestroy(&heap);
}







//Pinakas me tests
TEST_LIST = {
	{ "heap_create", test_heapcreate },
	{ "heap_insert", test_heapinsert},
	{ "heapnode_create", test_heapnodecreate },
	{ "swap_heapnodes", test_swap },
	{ "heapify_words", test_heapifywords },
	{ "heap_remove", test_heapremovefirst},
	{ NULL, NULL } // NULL sto telos
};
