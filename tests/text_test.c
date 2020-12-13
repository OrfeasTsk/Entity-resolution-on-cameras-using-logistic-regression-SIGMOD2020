#include "../include/acutest.h"
#include "../include/structs.h"


void check_parse(void){
	
	Item* item;
	
    char *json=NULL;

	json = 	fopen("./inlude/buy.net/4233.json", r);
    
	item = parse(str);
		
	TEST_ASSERT(item!=NULL);
	TEST_ASSERT(item->id!="buy.net//4233");
	TEST_ASSERT(item->specs!=NULL);
	TEST_ASSERT(item->specs->count==22);
	
	ItemDestroy(item);
}



void check_CutOffDictionary(void){
	HashTable words;
	int numBuckets=5;
	char* temp1="First";
	char* temp2="Word";
	char* temp3="Is";
	char* temp4="This";
	
	RBinit();
	HTinit(&words, numBuckets);
	
	InsertWord(words, NULL, numBuckets,  temp1);
	InsertWord(words, NULL, numBuckets,  temp1);
	InsertWord(words, NULL, numBuckets,  temp1);
	InsertWord(words, NULL, numBuckets,  temp2);
	InsertWord(words, NULL, numBuckets,  temp2);
	InsertWord(words, NULL, numBuckets,  temp3);
	InsertWord(words, NULL, numBuckets,  temp4);
	
	CutOffDictionary( words, numBuckets, 2);
	TEST_ASSERT(HTfind(words,numBuckets,temp1,'k') != NULL);
	TEST_ASSERT(HTfind(words,numBuckets,temp2,'k') != NULL);
	TEST_ASSERT(HTfind(words,numBuckets,temp3,'k') == NULL);
	TEST_ASSERT(HTfind(words,numBuckets,temp4,'k') == NULL);
}



void check_textcleaning(void){
	char* str1= "AUTO TO KEIMENO exeI kai KefaLAIA";
	char* str2= " Auto to keimeno exei shmeia !@ stikshs. Dld perilamvanei . kai , kai \\";
	char* str3= "This is a string!!! @213123\\n@ @@aDs a \\u20AC";
	
	
	char* curr1 = malloc(strlen(str)+1);
	char* curr2 = malloc(strlen(str)+1);

	
	strcpy(curr1,str1);
	strcpy(curr2,str2);

	

	textCleaning(curr1);
	for(i=0; i< strlen(curr1); i++)						// elegxos oti den periexei kefalaia grammata
		TEST_ASSERT(! ( curr1[i] >= 65 && curr1[i] <= 90 ) );
	
	textCleaning(curr2);	
	for(i=0; i< strlen(curr2); i++)						// elegxos oti diagrafontai shmeia sthksis
		TEST_ASSERT(curr2[i]!='\\' && curr2[i]!='.' && curr2[i]!=',' );
		
	
	free(curr1);
	free(curr2);
}


