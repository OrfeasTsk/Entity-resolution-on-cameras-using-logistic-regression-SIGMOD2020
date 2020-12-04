#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./include/text_support.h"


void textCleaning(char* text){

	int i;

	for( i=0 ; i < strlen(text) ; i++)
    	if( isalpha(text[i]) && isupper(text[i]) )
    		text[i]=tolower(text[i]);
    	else if ( ispunct(text[i]) || !isprint(text[i]))
    		text[i]=' ';

			
    
	printf(" %s ", text);
	
}

void tokenize(char* text){

	int i = 0,start,count = 0,j;
	char* token;
	
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
					token = (char*)malloc(count + 1);
					for(j = start; j < start+count; j++)
						token[j-start] = text[j];
					token[count] = '\0';
					printf("%s\n",token);	
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
		printf("Stopwords File file is empty!\n");
		return;
	}
			
	while( fgets( line , sizeof(line) , stopwords_file ) ){
		
		token=(char*)malloc(strlen(line)+1);
		strcpy(token,line);

		HTinsert( ht , numBuckets , token, (void*) token);
		free(token);
	}
	

	fclose(stopwords_file);
}
