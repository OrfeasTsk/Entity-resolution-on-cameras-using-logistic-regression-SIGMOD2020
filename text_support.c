#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "./include/structs.h"
#include "./include/text_support.h"





void CreateDictionary(Stats* fileStats , HashTable* words ,HashTable* stopwords ,int numBuckets, int* index){

	struct QueueNode* curr;
	Spec* spec;

	//printf("%s\n",fileStats->item->id);

	for( curr = fileStats->item->specs.head; curr != NULL ; curr = curr->next){
		spec = (Spec*)(curr->data);
		textCleaning(spec->name);
		textCleaning(spec->value);
		//if(!strcmp(fileStats->item->id,"buy.net//4233"))
		tokenize(spec->name, words, stopwords, numBuckets, NULL , index );
		tokenize(spec->value, words, stopwords, numBuckets, NULL ,index );		
	}

}


void UpdateArray(Stats* fileStats , HashTable* words , int numBuckets, int**  array){

	struct QueueNode* curr;
	Spec* spec;

	//printf("%s\n",fileStats->item->id);

	for( curr = fileStats->item->specs.head; curr != NULL ; curr = curr->next){
		spec = (Spec*)(curr->data);
		//if(!strcmp(fileStats->item->id,"buy.net//4233"))
		tokenize(spec->name, words, NULL, numBuckets, array , &(fileStats->index) );
		tokenize(spec->value, words, NULL, numBuckets, array , &(fileStats->index) );		
	}

}




void textCleaning(char* text){

	int i;

	for( i=0 ; i < strlen(text) ; i++)
    	if( isalpha(text[i]) && isupper(text[i]) )
    		text[i]=tolower(text[i]);
    	else if ( ispunct(text[i]) || !isprint(text[i]) || isdigit(text[i]))
    		text[i]=' ';

	
}

void InsertWord(HashTable* words, HashTable* stopwords ,int numBuckets, int* index, char* temp )
{
	char *token;
	int* num;
	
		if(HTfind(stopwords,numBuckets,temp,'k') == NULL){
			if( HTfind(words, numBuckets, temp ,'k') == NULL ){
				num = (int*)malloc(sizeof(int));
				*num = (*index)++;
				token = (char*)malloc(strlen(temp) + 1);
				strcpy(token,temp);
				HTinsert(words, numBuckets, token, (void*) num);
			}
			
		}
}


void UpdateArrayValue(HashTable* words ,int numBuckets, char* temp, int* index, int ** array )
{
	char *token;
	int* num;
	
		if( num = (int*)HTfind(words, numBuckets, temp ,'v') )
			array[*index][*num]++;
		
}





void tokenize(char* text, HashTable* words, HashTable* stopwords ,int numBuckets, int ** array, int* index){

	int i = 0,start,count = 0,j;
	char temp[100];
	
	while(isspace(text[i]))
		i++;
	
	for( ; i < strlen(text) ; i++){
		if(!isspace(text[i])){
			if(count == 0)
				start = i;				
			count++;		
		}
		else if( count > 0){
				if( count > 1){
					//token = (char*)malloc(count + 1);
					for(j = start; j < start+count; j++)
						temp[j-start] = text[j];
					temp[count] = '\0';
					
					if( stopwords == NULL && array != NULL)
						UpdateArrayValue( words , numBuckets,  temp,  index,  array );
					else if( stopwords != NULL && array == NULL )
						InsertWord( words, stopwords , numBuckets, index, temp );

				}
				count = 0;
		}
		
	}
		
	
}

void read_stopwords(HashTable* ht, char* stopwordsFile, int numBuckets){
	
	int i,hashnum;
	FILE * stopwords_file = fopen(stopwordsFile,"r"); 
	char* token;
	char line[50];
	
	if(stopwords_file == NULL){
		printf("Stopwords file is empty!\n");
		return;
	}
			
	while( fgets( line , sizeof(line) , stopwords_file ) ){
		
		token=(char*)malloc(strlen(line) + 1);
		strcpy(token,line);
		token[strlen(line)- 1] = '\0';

		HTinsert( ht , numBuckets , token, (void*) token);

	}
	

	fclose(stopwords_file);
}




double** Bow_To_Tfidf(int ** array, int rows, int cols){	
	
	int i,j,sum;							
	double idf;
	
	//Array
	double** tfidf = (double**)malloc( sizeof(double*) * (rows));
	for( i = 0 ; i < rows ; i++ )
		tfidf[i] = (double*)malloc( sizeof(double) * (cols) ); 
	
	for( i = 0 ; i < rows ; i++ ){		// upologismos tf
		counter=0;				// mas deixnei poses lekseis uparxoun se kathe row
		for(j = 0 ; j < cols ; j++)
			if( array[i][j] )
				counter += array[i][j];	
		for(j = 0 ; j < cols ; j++)
			if( array[i][j] && counter)
				tfidf[i][j] = (double)array[i][j] / counter;
			else
				tfidf[i][j] = 0.0;
	}
	
	for(j = 0 ; j < cols ; j++){
		counter = 0;					//o arithmos keimenwn ths sulloghs pou periexoun ton sugkekrimeno arithmo
		for( i = 0 ; i < rows ; i++ )
			if( array[i][j] )
				counter ++;
		idf = (double)rows / counter;
		idf = log(idf);
		for( i = 0 ; i < rows ; i++ )
			if( array[i][j] )
				tfidf[i][j] *= idf;
	}
}
