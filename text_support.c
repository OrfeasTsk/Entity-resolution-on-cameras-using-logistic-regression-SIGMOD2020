#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./include/structs.h"
#include "./include/text_support.h"



void CreateStats(Stats* fileStats , HashTable* words ,HashTable* stopwords ,int numBuckets,int* index){

	struct QueueNode* curr;
	Spec* spec;

	//printf("%s\n",fileStats->item->id);

	for( curr = fileStats->item->specs.head; curr != NULL ; curr = curr->next){
		spec = (Spec*)(curr->data);
		textCleaning(spec->name);
		textCleaning(spec->value);
		//if(!strcmp(fileStats->item->id,"buy.net//4233"))
		tokenize(spec->name, &(fileStats->words), words, stopwords, numBuckets, index );
		tokenize(spec->value, &(fileStats->words), words, stopwords, numBuckets, index );
		


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

void tokenize(char* text ,HashTable* fwords, HashTable* words,HashTable* stopwords ,int numBuckets,int* index){

	int i = 0,start,count = 0,j;
	char temp[100], *token;
	int* num;
	
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
					
					if(HTfind(stopwords,numBuckets,temp,'k') == NULL){
						
						if( (token = (char*)HTfind(words, numBuckets, temp ,'k')) == NULL ){
							num = (int*)malloc(sizeof(int));
							*num = (*index)++;
							token = (char*)malloc(strlen(temp) + 1);
							strcpy(token,temp);
							HTinsert(words, numBuckets, token, (void*) num);
						}

						if( num = (int*)HTfind(fwords, numBuckets, temp ,'v'))
							++*num;
						else{
							num = (int*)malloc(sizeof(int));
							*num = 1;
							HTinsert(fwords, numBuckets, token,(void*) num );
						}

						
					}



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
