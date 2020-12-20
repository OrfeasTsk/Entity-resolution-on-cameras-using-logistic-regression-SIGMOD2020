#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"
#include <string.h>



void check_parse(void){			// elegxoume an h parse douleuei swsta
	
	Item* item;				
	char* tmp = "2013_camera_specs/buy.net/4233.json";		// anoigoume ena json arxeio to opoio uparxei apo to dataset
	item = parse(tmp);
	char* str="buy.net//4233";
		
	// elegxoume an h parse douleuei swsta kai oi times exoume mpei swtsa
	TEST_ASSERT(item!=NULL);
	TEST_ASSERT( !strcmp(item->id,str) );
	TEST_ASSERT( item->specs.head != NULL );
	TEST_ASSERT( item->specs.count == 22 );			// ta stoixeia pou exei to sugkekrimeno file
	
	ItemDestroy(item);
}



void check_CutOffDictionary(void){				// elegxoume an h CutOffDictionary xwrizei tis lekseis kai krataei tis shmantikoteres mexri to orio pou theloume
	
	HashTable words;
	HashTable stopwords;
	HashTable files;
	Item* item1, *item2, *item3, *item4;
	FileStats* fstats1, *fstats2, *fstats3, *fstats4;
	int fIndex = 0, limit=2, wIndex = 0;

	
	RBinit();
	HTinit(&words);
	HTinit(&stopwords);
	HTinit(&files);
	
	
	// arxikopoioume tis lekseis 
	char* str1="First";
	char* str2="Word";
	char* str3="Is";
	char* str4="This";
	
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
	
	
	// kratame tis 2 shmantikoteres
	CutOffDictionary(&words, &files, limit);
	// kanoumetous analogous elegxous an emeinan oi swstes lekseis
	TEST_ASSERT( words.count == 2);		
	
	
	free(item1->id);
	free(item2->id);
	free(item3->id);
	free(item4->id);

	free(item1);
	free(item2);
	free(item3);
	free(item4);

	
	HTdestr(&files,&FilesDestroy,'v');
	HTdestr(&words,&WordsDestroy,'b');
	HTdestr(&stopwords,NULL,'k');
	RBdestr();


}



void check_textcleaning(void){			// elegxoume an ginetai swsta o katharismos keimenou se diafores periptwseis
	int i;
	char* str1= "AUTO TO KEIMENO exeI kai KefaLAIA";
	char* str2= " Auto to keimeno exei shmeia !@ stikshs. Dld perilamvanei . kai , kai \\";
	
	
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
	HashTable files;
	Item* item1, *item2, *item3, *item4, *item5;
	FileStats* fstats1,* fstats2,* fstats3,* fstats4;
	int fIndex = 0, wIndex = 0;

	
	RBinit();
	HTinit(&words);
	HTinit(&stopwords);
	HTinit(&files);
	
	
	// arxikopoioume tis lekseis 
	char* str1="First";
	char* str2="Word";
	char* str3="Is";
	char* str4="This";
	char* str5="not";
	
	
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
	
	
	item5 = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item5->id=malloc(strlen(str5)+1);
	strcpy(item5->id,str5);
	QueueInit(&(item5->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	



	TEST_ASSERT(HTfind(&words,str1,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str2,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str3,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str4,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str5,'v') == NULL);
	
	
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
	HTdestr(&words,&WordsDestroy,'b');
	HTdestr(&stopwords,NULL,'k');
	RBdestr();




	
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
	TEST_ASSERT(HTfind(&stopwords,curr1,'v') != NULL);
	TEST_ASSERT(HTfind(&stopwords,curr2,'v') != NULL);
	TEST_ASSERT(HTfind(&stopwords,curr3,'v') != NULL);


	free(curr1);
	free(curr2);
	free(curr3);
	
}

void check_tokenization(void){
	
	int wIndex=0, fIndex=0 ;
	HashTable stopwords;
	FileStats* fstats;
	Item* item;
	HashTable words;
	char* text="This is a text.";			// to keimeno pou tha kanoume tokenize
	char * temp=malloc(strlen(text)+1);
	strcpy(temp,text);
	textCleaning(temp);

	RBinit();
	HTinit(&stopwords);
	HTinit(&words);
	
	// arxikopoioume tis lekseis 
	char* str1="First";
	char* str2="this";
	char* str3="is";
	char* str4="a";
	char* str5="text";
	
	// bazoume mia leksh sto keimeno

	item = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	item->id=malloc(strlen(str1)+1);
	strcpy(item->id,str1);
	QueueInit(&(item->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	//arxikopoihsh filestats
	fstats = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
	fstats->item = item;
	fstats->index = fIndex++;
	fstats->numOfWords = 0;
	HTinit(&(fstats->words));
	InsertWord(&words, &stopwords, item->id, fstats, &wIndex );
	
	tokenize(temp, &words, &stopwords, fstats, &wIndex);
	
	TEST_ASSERT(words.count == 4);
	TEST_ASSERT(HTfind(&words,str1,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str2,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str3,'v') != NULL);
	TEST_ASSERT(HTfind(&words,str4,'v') == NULL);
	TEST_ASSERT(HTfind(&words,str5,'v') != NULL);
	
	
	
	free(temp);

	HTdestr(&words,&WordsDestroy,'b');
	HTdestr(&stopwords,NULL,'k');
	HTdestr(&(fstats->words),NULL,'v');
	free(fstats);
	free(item->id);
	free(item);
	RBdestr();
	
}





