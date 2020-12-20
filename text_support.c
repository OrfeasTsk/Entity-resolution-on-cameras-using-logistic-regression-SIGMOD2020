#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./include/structs.h"
#include "./include/text_support.h"



/*##################              START OF FUNCTIONS ABOUT DICTIONARY CONSTRUNCTION            ##########################*/


void CutOffDictionary( HashTable* words, HashTable* files , int limit ){  //Apokoph shmantikoterwn leksewn apo to leksilogio
	
	int i;
	Heap heap;
	Details* details;
	
	HeapInit(&heap);
	
	for(i = 0 ; i < numBuckets; i++)
		HeapifyWords(&(words->buckets[i]),&heap,files->count);

	free(words->buckets);
	HTinit(words);

		
	for(i = 0; i < limit; i++)  //Eksagwgh twn top limit leksewn kai dhmiourgia neou leksilogiou
		if( (details = HeapRemoveFirst(&heap))){
			details->wstats->index = i;
			//printf("%s , %f \n",details->wstats->word, details->count );
			HTinsert(words , details->wstats->word, (void*)details->wstats );
			free(details);
		}
		else
			break;

	for(i = 0 ; i < numBuckets; i++)  //Prosarmogh twn leksewn sta filestats
		AdjustMStats(files->buckets[i],words);
	

	HeapDestroy(&heap);
		
}


void CreateDictionary(FileStats* fstats , HashTable* words ,HashTable* stopwords,int* index){ //Dhmiourgia leksilogiou

	struct QueueNode* curr;
	Spec* spec;


	for( curr = fstats->item->specs.head; curr != NULL ; curr = curr->next){
		spec = (Spec*)(curr->data);
		textCleaning(spec->name);  //Katharismos tou onomatos
		textCleaning(spec->value);  //Katharismos ths timhs
		tokenize(spec->name, words, stopwords , fstats , index ); //Tokenize tou onomatos
		tokenize(spec->value, words, stopwords ,fstats ,index );  //Tokenize ths timhs	
	}

}








void InsertWord(HashTable* words, HashTable* stopwords , char* temp,FileStats* fstats,int* index ) //Eisagwgh lekshs
{
	WordStats* wstats;
	ModelStats* mstats;
	
		if(HTfind(stopwords,temp,'k') == NULL){  //An den yparxei sta stopwords
			if((wstats = (WordStats*)HTfind(words, temp ,'v'))){  //An yparxei sto leksilogio
				if((mstats = (ModelStats*) HTfind(&(fstats->words),wstats->word,'v'))){  //An yparxei stis lekseis tou arxeiou
					mstats->bow_val++;
					mstats->tfidf_val++;
					fstats->numOfWords++;
				}
				else{  //Eisagwgh stis lekseis tou arxeiou
					mstats = (ModelStats*)malloc(sizeof(ModelStats));
					mstats->wstats = wstats;
					mstats->bow_val = 1;
					mstats->tfidf_val = 1.0;
					HTinsert(&(fstats->words),wstats->word,(void*)mstats);
					fstats->numOfWords++;
					HTinsert(&(wstats->files),fstats->item->id,(void*)fstats);
				}

			}
			else{ //Eisagwgh sto leksilogio kai stis lekseis tou arxeiou
				
				wstats = (WordStats*)malloc(sizeof(WordStats));
				wstats->word = (char*)malloc(strlen(temp) + 1);
				strcpy(wstats->word,temp);
				wstats->index = (*index)++;
				HTinit(&(wstats->files));

				HTinsert(words, wstats->word, (void*) wstats);
				
				mstats = (ModelStats*)malloc(sizeof(ModelStats));
				mstats->wstats = wstats;
				mstats->bow_val = 1;
				mstats->tfidf_val = 1.0;
				HTinsert(&(fstats->words),wstats->word,(void*)mstats);
				fstats->numOfWords++;
				HTinsert(&(wstats->files),fstats->item->id,(void*)fstats);	
			}
		}
			
}


/*##################              END OF FUNCTIONS ABOUT DICTIONARY CONSTRUNCTION               ##########################*/




/*##################              START OF TEXT PREPROCESSING                   ##########################*/

void textCleaning(char* text){ //Katharismos leksewn

	int i;
	int backslash = 0;

	for( i = 0  ; i < strlen(text) ; i++)
		if( isalnum(text[i]) && backslash)  //An einai alfarithmitiko xwris na yparxei backslash prin
			text[i] = ' ';
    	else if( isalpha(text[i]) && isupper(text[i]) ) //An einai gramma kefalaio
    		text[i] = tolower(text[i]);
    	else if(text[i] == '\\'){ //An einai backslash
    		backslash = 1;
    		text[i] = ' ';
    	}
    	else if( isspace(text[i]) && backslash)  //An einai keno kai prohgeitai backslash
    		backslash = 0;
    	else if ( ispunct(text[i]) || !isprint(text[i]) )  //An einai shmeio stikshs kai mh egkyros xarakthras
    		text[i]=' ';

	
}




void tokenize(char* text, HashTable* words, HashTable* stopwords ,FileStats* fstats,int* index){ //Diaxwrismos twn leksewn

	int i = 0,start,count = 0,j;
	char temp[100];
	
	while(isspace(text[i]))
		i++;
	
	for( ; i < strlen(text) + 1 ; i++){
		if(!isspace(text[i]) && text[i] != '\0'){
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
					
					
					InsertWord( words, stopwords , temp, fstats, index );

				}
				count = 0;
		}
		
	}
		
	
}


/*##################              END OF TEXT PREPROCESSING                   ##########################*/




/*##################              START OF FILE READING AND PARSING                      ##########################*/


Item* parse(char* json){  //Json parser
	char* tmp, c, prev = ' ';
	int i, j, start = 0, flag = 0, count = 0, isValue = 0 ,isPrim = 0;
	FILE* fd;
	Item* item;
	Spec* sp;
	Stack stack;
	
	
	fd = fopen(json,"r");	//Anoigma tou json
	if(fd == NULL) 
		return NULL;
		
		
	item = (Item*) malloc(sizeof(Item)); //Dhmiourgia antikeimenou
	QueueInit(&(item->specs)); //Arxikopoihsh listas stoixeiwn antikeimenou
	
	for( i = 0; json[i] != '/'; i++) //Megethos arxikou katalogou
		count++;
	
	item->id = (char*) malloc(strlen(json) - count - 4 ); //Megethos xwris thn katalhksh .json kai to onoma tou arxikou katalogou
	item->id[strlen(json) - count - 5] = '\0';
	
	for( i = count + 1 , j = 0; i < strlen(json) - 5 ; i++ ){  //Xwris thn katalhksh .json kai to onoma tou arxikou katalogou
		(item->id)[j++] = json[i];
		if(json[i] == '/')
			(item->id)[j++] = '/'; //Diplo slash
	}
		
	count = 0;
	StackInit(&stack);
	while(!feof(fd)){
		
		c = fgetc(fd);
		
		if(!isValue){ // An den einai h seira tou diavasmatos ths timhs(dhladh einai to onoma tou spec)
			if( c == '"' && flag == 0){ //Otan vrethei to arxiko eisagwgiko(")
				start = count; //Apothikeush ths theshs
				flag = 1 ; //To eisagwgiko den exei kleisei
			}
			else if ( c == '"' && prev != '\\' && flag == 1){ //An einai to eisagwgiko(") kleisimatos
				tmp = (char*)malloc((count - start - 1)*sizeof(char) + 1); //Desmeush xwrou gia thn leksh anamesa sta eisagwgika
				fseek(fd,start + 1,SEEK_SET); //Arxh diavasmatos meta to arxiko eisagwgiko
				for( i = 0; i < count - start - 1; i++)
					tmp[i] = fgetc(fd);
				tmp[count - start - 1] = '\0';
				fseek(fd,count + 1,SEEK_SET); //Diavasma meta to eisagwgiko kleisimatos
				sp = (Spec*)malloc(sizeof(Spec)); //Dhmiourgia neou spec
				sp->name = tmp; // Prosthikh onomatos
				isValue = 1; // Seira ths timhs
				start = -1;
				
				flag = 0; //To eisagwgiko exei kleisei
			} 
		}
		else{
			if(start == -1){ //Mexri na vrethei h arxh(start)
				if( c != ':' && c != ' '){
					if( (c == '"'  || c == '{' || c == '[') && prev != '\\'){
						push(&stack,c);
						isPrim = 0;
					}
					else
						isPrim=1;
					start = count;
				}
			}
			else{
				if(!StackEmpty(&stack)){
					if((c == '[' || c == '{'|| c == '"'  || c == ']' || c == '}') && prev != '\\')
						check(&stack,c);
				}
				else if(isPrim == 0){
					tmp = (char*)malloc((count - start)*sizeof(char) + 1); //Desmeush xwrou gia thn timh
					fseek(fd,start,SEEK_SET); //Arxh diavasmatos apo to start
					for( i = 0; i < count - start; i++)
						tmp[i] = fgetc(fd);
					tmp[count - start] = '\0';
					fseek(fd,count + 1,SEEK_SET); //Diavasma apo ekei pou stamathse o elegxos
				//	printf("%s\n",tmp);
					sp->value = tmp; // Prosthikh timhs
					QueueInsert(&(item->specs),(void**)&sp);
					isValue = 0; //Seira tou onomatos
				}
				else{
					if( c == ',' || c ==' '){
						tmp = (char*)malloc((count - start)*sizeof(char) + 3);
						fseek(fd,start,SEEK_SET); //Arxh diavasmatos apo to start
						tmp[0] = '"';
						for( i = 1 ; i < count - start + 1 ; i++)
							tmp[i] = fgetc(fd);
						tmp[count - start + 1] = '"';
						tmp[count - start + 2] = '\0';
						fseek(fd,count + 1,SEEK_SET); //Diavasma apo ekei pou stamathse o elegxos
					//	printf("%s\n",tmp);
						sp->value = tmp; // Prosthikh timhs
						QueueInsert(&(item->specs),(void**)&sp);
						isValue = 0; //Seira tou onomatos
						
					}	
				}	
			}
		}
			
		count++;
		prev = c;
	}
	
	
	fclose(fd);
	return item;
	
		
}


void read_csv(HashTable* ht,char* datasetW){ //Diavasma tou csv arxeiou
	
	int i;
	FILE * csv_file = fopen(datasetW,"r"); 
	char* token;
	char line[400];
	Pair* pairA,* pairB;
	
	if(csv_file == NULL){
		printf("Csv file is empty!\n");
		return;
	}

	fgets(line, sizeof(line), csv_file); //Diavasma twn etiketwn tou csv

			
	while(fgets(line, sizeof(line), csv_file)){
		
		token = strtok(line,",");
		
		for(i = 0; (i < 3 && token != NULL) ; i++ ){
			if( i == 0 ){
				pairA = (Pair*) HTfind(ht,token,'v'); //Euresh tou left item	
			}
			if(i == 1){
				pairB = (Pair*) HTfind(ht,token,'v');  //Euresh tou right item
			}
			if( i == 2)
				if(pairA != NULL && pairB != NULL){
					if(atoi(token) == 1){ //An tairiazoun 
						if(pairA->cliq->related != pairB->cliq->related) //An den exoun enwthei ksana
							CliqueConcat(pairA, pairB, 1);
					}
					else{				// Alliws sthn periptwsh tou 0 (dld dn tairiazoun)
						CliqueConcat(pairA, pairB, 0);
					}
				}
			
			
			token = strtok(NULL, ",");			// Synexeia tou tokenize
		}
	}

	fclose(csv_file);
	
}



void read_stopwords(HashTable* ht, char* stopwordsFile){ //Diavasma twn stopwords
	
	FILE * stopwords_file = fopen(stopwordsFile,"r"); 
	char* token;
	char line[50];
	
	if(stopwords_file == NULL){
		printf("Stopwords file is empty!\n");
		return;
	}
			
	while( fgets( line , sizeof(line) , stopwords_file ) ){
		
		token=(char*)malloc(strlen(line));
		strncpy(token,line,strlen(line));
		token[strlen(line) - 1 ] = '\0';

		HTinsert( ht  , token, (void*) token);

	}
	

	fclose(stopwords_file);
}

/*##################              END OF FILE READING AND PARSING                      ##########################*/


void DatasetSplit(Queue * train, Queue *test, Queue *valid, Record* record ){  //Tyxaios diaxwrismos tou dataset se 60 20 20
	int sum_of_items_in_queue, r;
	double flag_train, flag_test, flag_valid;
	int max_train = maxSplit*60/100;
	int max_test = maxSplit*20/100;
	int max_valid = maxSplit*20/100;
	
	
	sum_of_items_in_queue= train->count + test->count + valid->count; 
	if( sum_of_items_in_queue % 20 == 0 ){			// An einai apo thn arxh 
		
    	r = rand() % 3;
    	if( r == 0 )
    		QueueInsert(train,(void**)&record);
    	else if(r == 1)
    		QueueInsert(test,(void**)&record);
    	else
    		QueueInsert(valid,(void**)&record);
	}
	else{
			r= rand()%3;
			if(r==0){																			// An tuxei to 0(periptwsh train)
				if( train->count % max_train == 0 ){										// An to train diaireitai me to 0, h exei gemisei tis 12 theseis pou tou analogoun h den exei bei kamia
					flag_train = train->count / max_train;								// Ypologizoume thn diairesh
					flag_test = test->count / max_test;
					flag_valid = valid->count / max_valid;
					if( (flag_train < flag_test) || (flag_train < flag_valid) )	// An isxuei ena apo ta duo shmainei oti den exei gemisei (oriakh periptwsh)
						QueueInsert(train,(void**)&record);
					else{															// Diaforetika shmainei oti exei gemisei (oriakh periptwsh)
					
						r= rand() % 2;
						if(r==0){											// An erthei 0 paei sto test
							if( test->count % max_test ==0){		// An to mod einai 0, h exei gemisei tiw 4 theseis pou tou analogoun h einai adeio
								if(flag_test <= flag_valid)				// Shmainei oti den exei gemisei
									QueueInsert(test,(void**)&record);
								else										// Exei gemisei kai bainei sto valid
									QueueInsert(valid,(void**)&record);
							}
							else											// Diaforetika apla mpainei h timh
								QueueInsert(test,(void**)&record);
						}
						else if(r==1){										// Analoga an tuxei to 1 paei sto valid
							if( valid->count % max_valid ==0){
								if(flag_valid <= flag_test)				// Shmainei oti den exei gemisei
									QueueInsert(valid,(void**)&record);
								else
									QueueInsert(test,(void**)&record);
							}
							else
								QueueInsert(valid,(void**)&record);
						}
					}
				}
				else
					QueueInsert(train,(void**)&record);
			}
			else if(r==1){															// An tuxei to 1 (periptwsh test)
				if( test->count % max_test ==0 ){										// An to test diaireitai me to 0, h exei gemisei tis 4 theseis pou tou analogoun h den exei bei kamia
					flag_train = train->count / max_train;									// Ypologizoume thn diairesh
					flag_test = test->count / max_test;
					flag_valid = valid->count / max_valid;
					if( (flag_test < flag_train) || (flag_test < flag_valid) )	// An isxuei ena apo ta duo shmainei oti den exei gemisei (oriakh periptwsh)
						QueueInsert(test,(void**)&record);
					else{															// Diaforetika shmainei oti exei gemisei (oriakh periptwsh)
					
						r= rand() % 2;
						if(r==0){											// An erthei 0 paei sto train
							if( train->count % max_train ==0){				// An to mod einai 0, h exei gemisei tiw 12 theseis pou tou analogoun h einai adeio
								if(flag_train <= flag_valid)				// Shmainei oti den exei gemisei
									QueueInsert(train,(void**)&record);
								else										// Exei gemisei kai bainei sto valid
									QueueInsert(valid,(void**)&record);
							}
							else											// Diaforetika apla mpainei h timh
								QueueInsert(train,(void**)&record);
						}
						else if(r==1){										// Analoga an tuxei to 1 paei sto valid
							if( valid->count % max_valid ==0){
								if(flag_valid <= flag_train)				// Shmainei oti den exei gemisei
									QueueInsert(valid,(void**)&record);
								else
									QueueInsert(train,(void**)&record);
							}
							else
								QueueInsert(valid,(void**)&record);
						}
					}
				}
				else
					QueueInsert(test,(void**)&record);
			}	
			else if(r==2){															// An tuxei to 2 (periptwsh valid)
				if( valid->count % max_valid ==0 ){										// An to valid diaireitai me to 0, h exei gemisei tis 4 theseis pou tou analogoun h den exei bei kamia
					flag_train = train->count / max_train;									// Ypologizoume thn diairesh
					flag_test = test->count / max_test;
					flag_valid = valid->count / max_valid;
					if( (flag_valid < flag_train) || (flag_valid < flag_test) )	// An isxuei ena apo ta duo shmainei oti den exei gemisei (oriakh periptwsh)
						QueueInsert(valid,(void**)&record);
					else{															// Diaforetika shmainei oti exei gemisei (oriakh periptwsh)
						
						r= rand ()% 2;
						if(r==0){											// An erthei 0 paei sto train
							if( train->count % max_train ==0){						// An to mod einai 0, h exei gemisei tiw 12 theseis pou tou analogoun h einai adeio
								if(flag_train <= flag_test)				// Shmainei oti den exei gemisei
									QueueInsert(train,(void**)&record);
								else										// Exei gemisei kai bainei sto test
									QueueInsert(test,(void**)&record);
							}
							else											// Diaforetika apla mpainei h timh
								QueueInsert(train,(void**)&record);
						}
						else if(r==1){										// Analoga an tuxei to 1 paei sto test
							if( test->count % max_test ==0){
								if(flag_test <= flag_train)				// Shmainei oti den exei gemisei
									QueueInsert(test,(void**)&record);
								else
									QueueInsert(train,(void**)&record);
							}
							else
								QueueInsert(test,(void**)&record);
						}
					}
				}
				else
					QueueInsert(valid,(void**)&record);
			}
					
		}
	
	
	
}




