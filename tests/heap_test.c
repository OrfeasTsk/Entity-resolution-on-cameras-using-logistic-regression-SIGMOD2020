#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"


void test_heapnodecreate(void){		// Elegxoume an h newNode douleuei kai arxikopoiei swsta ta values
	
	WordStats* wstats;
	Details* details1 ;
	struct heapNode* temp ;
	HashTable files;
	char name1[10] = "First" ;
	
	HTinit(&files);
	
	//dhmiourgia wstats
	wstats=(WordStats*)malloc(sizeof(WordStats));
	wstats->word=(char*)malloc(strlen(name1) + 1);
	strcpy(wstats->word,name1);
	wstats->index=0;
//	HTinit(&(wstats->files));
	wstats->files=files;
	
	// dhmiourgoume ta details pou prepei na baloume
	details1 = (Details*)malloc(sizeof(Details));
	details1->wstats= wstats;
	details1->count = 0.0;
	
	temp=newNode(details1);
	
	// kanoume ta analoga test kai elegxoume an ola exoun bei swsta
	TEST_ASSERT( temp->left == NULL );
	TEST_ASSERT( temp->right == NULL );
	TEST_ASSERT( strcmp( temp->data->wstats->word , name1 ) == 0  );
	TEST_ASSERT( temp->data->count == 0.0 );
	
	//frees
	
	HTdestr(&files,&FilesDestroy,'v');
	free(wstats->word);
	free(wstats);
	free(details1);
	free(temp);

}


void test_swap(void){		// elegxoume an h swap douleuei kai allazei to periexomeno twn details
	
	Details* details1, *details2;
	WordStats* wstats1, *wstats2;
	HashTable files;
	int result;	
	struct heapNode* temp1, *temp2;

	char name1[10]="First";
	char name2[10]="Second";
	
	HTinit(&files);
	
	//dhmiourgia wstats1
	wstats1=(WordStats*)malloc(sizeof(WordStats));
	wstats1->word=(char*)malloc(strlen(name1) + 1);
	strcpy(wstats1->word,name1);
	wstats1->index=0;
	wstats1->files=files;
	
	// dhmiourgoume ta details pou prepei na baloume
	details1 = (Details*)malloc(sizeof(Details));
	details1->wstats= wstats1;
	details1->count = 0.0;
	
	
	//dhmiourgia wstats2
	wstats2=(WordStats*)malloc(sizeof(WordStats));
	wstats2->word=(char*)malloc(strlen(name2) + 1);
	strcpy(wstats2->word,name2);
	wstats2->index=0;
	wstats2->files=files;
	
	// dhmiourgoume ta details pou prepei na baloume
	details2 = (Details*)malloc(sizeof(Details));
	details2->wstats= wstats2;
	details2->count = 2.0;
	
	temp1=newNode(details1);
	temp2=newNode(details2);
	
	// result periexei thn timh 1 an egine h allagh
	result=swap(temp1, temp2);
	
	TEST_ASSERT( result == 1 );			// prepei na epistrepsei 1 afou to count tou deuterou einai megalutero 
	// elegxoume an exei ginei h allagh
	TEST_ASSERT( temp1->data->count == 2.0 );	
	TEST_ASSERT( temp2->data->count == 0.0 );
	TEST_ASSERT( strcmp( temp1->data->wstats->word , name2 ) == 0);
	TEST_ASSERT( strcmp( temp2->data->wstats->word , name1 ) == 0);
	
	//frees
	HTdestr(&files,&FilesDestroy,'v');
	free(wstats1->word);
	free(wstats2->word);
	free(wstats1);
	free(wstats2);
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
	WordStats* wstats1, *wstats2;
	Heap heap;
	char name1[10]="First";
	char name2[10]="Second";
	
	HeapInit(&heap);


	
	//dhmiourgia wstats1
	wstats1=(WordStats*)malloc(sizeof(WordStats));
	wstats1->word=(char*)malloc(strlen(name1) + 1);
	strcpy(wstats1->word,name1);
	wstats1->index=0;
	HTinit(&(wstats1->files));
	
	// dhmiourgoume ta details pou prepei na baloume
	details1 = (Details*)malloc(sizeof(Details));
	details1->wstats= wstats1;
	details1->count = 5.0;
	
	HeapInsert(&heap,details1);	// eisagoume to prwto item 
	
	TEST_ASSERT( heap.nodes == 1 );
	TEST_ASSERT( heap.height == 1);
	TEST_ASSERT( strcmp( heap.head->data->wstats->word , name1 ) == 0 );
	TEST_ASSERT( heap.head->data->count == 5.0 );
	
	//dhmiourgia wstats2
	wstats2=(WordStats*)malloc(sizeof(WordStats));
	wstats2->word=(char*)malloc(strlen(name2) + 1);
	strcpy(wstats2->word,name2);
	wstats2->index=0;
	HTinit(&(wstats2->files));
	
	// dhmiourgoume ta details pou prepei na baloume
	details2 = (Details*)malloc(sizeof(Details));
	details2->wstats= wstats2;
	details2->count = 10.0;
	
	HeapInsert(&heap,details2);	// eisagoume to deutero item
	TEST_ASSERT( heap.nodes == 2 );
	TEST_ASSERT( heap.height == 2);
	
	
	HeapDestroy(&heap);

}


void test_heapremovefirst(void){	// elegxoume an h HeapRemoveFirst douleuei kai afairei swsta ta items allazontas tis analoges times tou heap
	
	Details* details1, *details2, *details;
	WordStats* wstats1, *wstats2;
	Heap heap;
	char name1[10]="First";
	char name2[10]="Second";
	
	HeapInit(&heap);

	//dhmiourgia wstats1
	wstats1=(WordStats*)malloc(sizeof(WordStats));
	wstats1->word=(char*)malloc(strlen(name1) + 1);
	strcpy(wstats1->word,name1);
	wstats1->index=0;

	
	// dhmiourgoume ta details pou prepei na baloume
	details1 = (Details*)malloc(sizeof(Details));
	details1->wstats= wstats1;
	details1->count = 5.0;	
	HeapInsert(&heap,details1);	// insert first item
	
	//dhmiourgia wstats2
	wstats2=(WordStats*)malloc(sizeof(WordStats));
	wstats2->word=(char*)malloc(strlen(name2) + 1);
	strcpy(wstats2->word,name2);
	wstats2->index=0;

	
	// dhmiourgoume ta details pou prepei na baloume
	details2 = (Details*)malloc(sizeof(Details));
	details2->wstats= wstats2;
	details2->count = 10.0;	
	HeapInsert(&heap,details2);	// insert second item
	
	//afairoume to prwto details kai elegxoume an o heap allazei swsta kai an bgazei to item me to megalutero count
	details= HeapRemoveFirst(&heap);
	TEST_ASSERT( heap.nodes == 1 );
	TEST_ASSERT( heap.height == 1);
	TEST_ASSERT( strcmp( details->wstats->word , name2 ) == 0 );
	TEST_ASSERT( details->count == 10.0 );
	
	free(details->wstats->word);
	free(details->wstats);
	free(details);
	
	// afairoume kai to deutero details kanontas paromoious elegxous
	details= HeapRemoveFirst(&heap);
	TEST_ASSERT( heap.nodes == 0 );
	TEST_ASSERT( heap.height == 0 );
	TEST_ASSERT( strcmp( details->wstats->word , name1 ) == 0 );
	TEST_ASSERT( details->count == 5.0 );
	

	free(details->wstats->word);
	free(details->wstats);
	free(details);
//	HeapDestroy(&heap);
	
}



void test_heapifywords(void){	// Elegxoume an h HeapifyWords douleuei swsta kai bazei swsta sto heap tis lekseis
	
	
	int i;
	Item* item1, *item2, *item3, *item4, *item5;
	FileStats* fstats1,* fstats2,* fstats3,* fstats4, * fstats5;
	int fIndex = 0, wIndex = 0;
	
	RBinit();
	
	Heap heap;
	HeapInit(&heap); 
	
	HashTable words;
	HashTable stopwords;
	HashTable files;
	HTinit(&words);
	HTinit(&stopwords);
	HTinit(&files);


	char* str1="First";
	char* str2="Word";
	char* str3="Is";
	char* str4="This";
	char* str5="Not";
	
	
	
	// bazoume lekseis sto keimeno kai elegxoume an autes oi lekseis mphkan kai uparxoyn 
	//First one		
	item1 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item1->id=malloc(strlen(str1)+1);
	strcpy(item1->id,str1);
	QueueInit(&(item1->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats1 = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats1->item = item1;
	fstats1->index = fIndex++;
	fstats1->numOfWords = 0;
	HTinit(&(fstats1->words));
	InsertWord(&words, &stopwords, item1->id, fstats1, &wIndex );
	InsertWord(&words, &stopwords, item1->id, fstats1, &wIndex );
	HTinsert(&files, item1->id , (void*)fstats1);
	

	//Second one
		
		
	item2 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item2->id=malloc(strlen(str2)+1);
	strcpy(item2->id,str2);
	QueueInit(&(item2->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats2 = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats2->item = item2;
	fstats2->index = fIndex++;
	fstats2->numOfWords = 0;
	HTinit(&(fstats2->words));
	InsertWord(&words, &stopwords, item2->id, fstats2, &wIndex );
	HTinsert(&files, item2->id , (void*)fstats2);
	
	
	//Third one
			
	item3 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item3->id=malloc(strlen(str3)+1);
	strcpy(item3->id,str3);
	QueueInit(&(item3->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats3 = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats3->item = item3;
	fstats3->index = fIndex++;
	fstats3->numOfWords = 0;
	HTinit(&(fstats3->words));
	InsertWord(&words, &stopwords, item3->id, fstats3, &wIndex );
	InsertWord(&words, &stopwords, item3->id, fstats3, &wIndex );
	HTinsert(&files, item3->id , (void*)fstats3);
	
	
	//Fourth one
		
	item4 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item4->id=malloc(strlen(str4)+1);
	strcpy(item4->id,str4);
	QueueInit(&(item4->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats4 = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats4->item = item4;
	fstats4->index = fIndex++;
	fstats4->numOfWords = 0;
	HTinit(&(fstats4->words));
	InsertWord(&words, &stopwords, item4->id, fstats4, &wIndex );
	HTinsert(&files, item4->id , (void*)fstats4);
	
	
	// Fifth one
	item5 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item5->id=malloc(strlen(str5)+1);
	strcpy(item5->id,str5);
	QueueInit(&(item5->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats5 = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats5->item = item5;
	fstats5->index = fIndex++;
	fstats5->numOfWords = 0;
	HTinit(&(fstats5->words));
	// 5 fores thn pempth
	InsertWord(&words, &stopwords, item5->id, fstats5, &wIndex );
	InsertWord(&words, &stopwords, item5->id, fstats5, &wIndex );
	InsertWord(&words, &stopwords, item5->id, fstats5, &wIndex );
	HTinsert(&files, item5->id , (void*)fstats5);
	
		
	// Gia kathe bucket pou exei dhmiourgithei kanoyme Heapify
	for(i = 0 ; i < numBuckets; i++)
		HeapifyWords(&(words.buckets[i]),&heap, files.count);

	TEST_ASSERT(heap.nodes == 5); // oi lekseis prepei na einai 5
	TEST_ASSERT(heap.height == 3); // kai to upsos 3
	TEST_ASSERT(!strcmp(heap.head->data->wstats->word,str5));	// megaluterh timh
	
	
	free(item1->id);
	free(item2->id);
	free(item3->id);
	free(item4->id);
	free(item5->id);

	// gia oura?
	free(item1);
	free(item2);
	free(item3);
	free(item4);
	free(item5);

	
	HTdestr(&files,&FilesDestroy,'v');
	free(words.buckets);
	HTdestr(&stopwords,NULL,'k');

	HeapDestroy(&heap);
	RBdestr();
}






