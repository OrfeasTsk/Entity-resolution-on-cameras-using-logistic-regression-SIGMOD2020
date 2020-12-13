#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"


void check_parse(void){
	
	Item* item;
	char* tmp = "2013_camera_specs/buy.net/4233.json";
	item = parse(tmp);
		
	TEST_ASSERT(item!=NULL);
	TEST_ASSERT(item->id!="buy.net//4233");
	TEST_ASSERT( item->specs.head != NULL );
	TEST_ASSERT( item->specs.count == 22 );
	
	ItemDestroy(item);
}




void check_CutOffDictionary(void){
	
	HashTable words;
	HashTable stopwords;

	int numBuckets=5, limit=2;
	
	char* str1="First";
	char* str2="Word";
	char* str3="Is";
	char* str4="This";
	
	RBinit();
	HTinit(&words, numBuckets);
	HTinit(&stopwords, numBuckets);
	

	char* curr1 = malloc(strlen(str1)+1);
	char* curr2 = malloc(strlen(str2)+1);
	char* curr3 = malloc(strlen(str3)+1);
	char* curr4 = malloc(strlen(str4)+1);
	
	strcpy(curr1,str1);
	strcpy(curr2,str2);
	strcpy(curr3,str3);
	strcpy(curr4,str4);
	
	InsertWord(&words, &stopwords, numBuckets,  curr1);
	InsertWord(&words, &stopwords, numBuckets,  curr1);
	InsertWord(&words, &stopwords, numBuckets,  curr1);
	InsertWord(&words, &stopwords, numBuckets,  curr2);
	InsertWord(&words, &stopwords, numBuckets,  curr2);
	InsertWord(&words, &stopwords, numBuckets,  curr3);
	InsertWord(&words, &stopwords, numBuckets,  curr4);
	
	CutOffDictionary( &words, numBuckets, limit);
	TEST_ASSERT(HTfind(&words,numBuckets,curr1,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,curr2,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,curr3,'k') == NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,curr4,'k') == NULL);
	
	free(curr1);
	free(curr2);
	free(curr3);
	free(curr4);

}



void check_textcleaning(void){
	int i;
	char* str1= "AUTO TO KEIMENO exeI kai KefaLAIA";
	char* str2= " Auto to keimeno exei shmeia !@ stikshs. Dld perilamvanei . kai , kai \\";
	char* str3= "This is a string!!! @213123\\n@ @@aDs a \\u20AC";
	
	
	char* curr1 = malloc(strlen(str1)+1);
	char* curr2 = malloc(strlen(str2)+1);

	
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


void check_InsertWord(void){
	HashTable words;
	HashTable stopwords;
	
	int numBuckets=5;
	char* temp1="First";
	char* temp2="Word";
	char* temp3="Is";
	char* temp4="This";
	char* temp5="Not";
	// Trees initialise
	RBinit();
	HTinit(&words, numBuckets);
	HTinit(&stopwords, numBuckets);
	
	InsertWord(&words, &stopwords, numBuckets,  temp1);
	InsertWord(&words, &stopwords, numBuckets,  temp2);
	InsertWord(&words, &stopwords, numBuckets,  temp3);
	InsertWord(&words, &stopwords, numBuckets,  temp4);
	TEST_ASSERT(HTfind(&words,numBuckets,temp1,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,temp2,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,temp3,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,temp4,'k') != NULL);
	TEST_ASSERT(HTfind(&words,numBuckets,temp5,'k') == NULL);
	
}

void check_read_stopwords(void){
	HashTable stopwords;
	int numBuckets=5;
	
	char* stopword1="able";
	char* stopword2="mon";
	char* stopword3="contains";
	
	
		
	char* curr1 = malloc(strlen(stopword1)+1);
	char* curr2 = malloc(strlen(stopword2)+1);
	char* curr3 = malloc(strlen(stopword3)+1);

	
	strcpy(curr1,stopword1);
	strcpy(curr2,stopword2);
	strcpy(curr3,stopword3);

	
	// Trees initialise
	RBinit();
	HTinit(&stopwords, numBuckets);
	
	char* tmp="include/stopwords.txt";
	
	
	read_stopwords( &stopwords , tmp , numBuckets );
	// these are some values that exists in our stopwords file
	TEST_ASSERT(HTfind(&stopwords,numBuckets,curr1,'k') != NULL);
//	TEST_ASSERT(HTfind(&stopwords,numBuckets,curr2,'k') != NULL);
//	TEST_ASSERT(HTfind(&stopwords,numBuckets,curr3,'k') != NULL);

	
	free(curr1);
	free(curr2);
	free(curr3);
	
}




//Pinakas me tests
TEST_LIST = {
	{ "parse_test", check_parse },
	{ "cutoffdictionary_test", check_CutOffDictionary },
	{ "textcleaning_test", check_textcleaning },
	{ "InsertWord_test", check_InsertWord },
	{ "read_stopwords_test", check_read_stopwords },
	{ NULL, NULL } // NULL sto telos
};
