#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"


void check_parse(void){			// elegxoume an h parse douleuei swsta
	
	Item* item;				
	char* tmp = "2013_camera_specs/buy.net/4233.json";		// anoigoume ena json arxeio to opoio uparxei apo to dataset
	item = parse(tmp);
		
	// elegxoume an h parse douleuei swsta kai oi times exoume mpei swtsa
	TEST_ASSERT(item!=NULL);
	TEST_ASSERT(item->id!="buy.net//4233");
	TEST_ASSERT( item->specs.head != NULL );
	TEST_ASSERT( item->specs.count == 22 );
	
	ItemDestroy(item);
}



// den uparxei
void check_CutOffDictionary(void){				// elegxoume an h CutOffDictionary xwrizei tis lekseis kai krataei tis shmantikoteres mexri to orio pou theloume
	
	HashTable words;
	HashTable stopwords;

	int limit=2;
	
	// arxikopoioume tis lekseis 
	char* str1="First";
	char* str2="Word";
	char* str3="Is";
	char* str4="This";
	
	RBinit();
	HTinit(&words);
	HTinit(&stopwords);
	

	char* curr1 = malloc(strlen(str1)+1);
	char* curr2 = malloc(strlen(str2)+1);
	char* curr3 = malloc(strlen(str3)+1);
	char* curr4 = malloc(strlen(str4)+1);
	
	strcpy(curr1,str1);
	strcpy(curr2,str2);
	strcpy(curr3,str3);
	strcpy(curr4,str4);
	
	// bazoume lekseis
	InsertWord(&words, &stopwords,  curr1);
	InsertWord(&words, &stopwords,  curr1);
	InsertWord(&words, &stopwords,  curr1);
	InsertWord(&words, &stopwords,  curr2);
	InsertWord(&words, &stopwords,  curr2);
	InsertWord(&words, &stopwords,  curr3);
	InsertWord(&words, &stopwords,  curr4);
	
	// kratame tis 2 shmantikoteres
	CutOffDictionary( &words, limit);
	// kanoumetous analogous elegxous an emeinan oi swstes lekseis
	TEST_ASSERT(HTfind(&words,curr1,'k') != NULL);
	TEST_ASSERT(HTfind(&words,curr2,'k') != NULL);
	TEST_ASSERT(HTfind(&words,curr3,'k') == NULL);
	TEST_ASSERT(HTfind(&words,curr4,'k') == NULL);
	
	free(curr1);
	free(curr2);
	free(curr3);
	free(curr4);

}



void check_textcleaning(void){			// elegxoume an ginetai swsta o katharismos keimenou se diafores periptwseis
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


void check_InsertWord(void){				// thelei allagh
	HashTable words;
	HashTable stopwords;
	
	char* temp1="First";
	char* temp2="Word";
	char* temp3="Is";
	char* temp4="This";
	char* temp5="Not";
	// Trees initialise
	RBinit();
	HTinit(&words);
	HTinit(&stopwords);
	
	// bazoume lekseis sto keimeno kai elegxoume an autes oi lekseis mphkan kai uparxoyn 
	
	InsertWord(&words, &stopwords,  temp1);
	InsertWord(&words, &stopwords,  temp2);
	InsertWord(&words, &stopwords,  temp3);
	InsertWord(&words, &stopwords,  temp4);
	TEST_ASSERT(HTfind(&words,temp1,'k') != NULL);
	TEST_ASSERT(HTfind(&words,temp2,'k') != NULL);
	TEST_ASSERT(HTfind(&words,temp3,'k') != NULL);
	TEST_ASSERT(HTfind(&words,temp4,'k') != NULL);
	TEST_ASSERT(HTfind(&words,temp5,'k') == NULL);
	
}

void check_read_stopwords(void){		// elegxos an mpainoun swsta ta stopwords apo to arxeio
	HashTable stopwords;
	
	// ta stopwords ta opoia kseroume oti einai mesa sto arxeio 
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
	HTinit(&stopwords);
	
	char* tmp="include/stopwords.txt";
	
	
	read_stopwords( &stopwords , tmp  );
	// edw elegxoume an exoun bei ontws me ta aparaithta tests
	TEST_ASSERT(HTfind(&stopwords,curr1,'k') != NULL);
	TEST_ASSERT(HTfind(&stopwords,curr2,'k') != NULL);
	TEST_ASSERT(HTfind(&stopwords,curr3,'k') != NULL);


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
