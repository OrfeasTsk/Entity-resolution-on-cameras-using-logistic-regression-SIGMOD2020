#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "./include/structs.h"
#include "./include/text_support.h"






int main(int argc, char* argv[]){
	int i, j, id = 0 ,fIndex = 0, wIndex = 0, limit;
	char* datasetX=NULL, *datasetW=NULL, *stopwordsFile=NULL, *tmpdir1, *json, *tmp;
	char buff[200];
	DIR* dir_ptr1,*dir_ptr2;
	FILE* output;
	struct dirent* dirent_ptr;
	Item* item;
	FileStats* fstats;
	Pair *pair;
	HashTable pairs;
	HashTable cliques;
	HashTable stopwords;
	HashTable words;
	HashTable files;
	Queue train,test,valid;
	LogisticRegression lr;

	
	
	if(argc != 7){
		printf("Argument error\n");
			return 1;
	}
	
	for(i = 1 ; i < argc ; i += 2){ //Den mas endiaferei h seira pou dinontai kai den epitrepei tis epanalhpseis twn parametrwn

		if(!strcmp("-x",argv[i]) && datasetX == NULL)
			datasetX=argv[i+1];
		else if(!strcmp("-w",argv[i]) && datasetW == NULL)
			datasetW=argv[i+1];
		else if(!strcmp("-s",argv[i]) && stopwordsFile == NULL)
			stopwordsFile = argv[i+1];
		else{
			printf("Argument error\n");
			return 1;
		}
	}
	
	// Trees initialise
	RBinit();

	//Hash Table initialise
	HTinit(&cliques);
	HTinit(&pairs);
	HTinit(&stopwords);
	HTinit(&words);
	HTinit(&files);
	
	//Queues for dataset split
	QueueInit( &train );
	QueueInit( &test );
	QueueInit( &valid );

	
	//Read Stopwords file
	read_stopwords(&stopwords , stopwordsFile);


	srand(time(NULL));

	dir_ptr1 = opendir(datasetX);
	while(dirent_ptr = readdir(dir_ptr1)) //Diavasma twn katalogwn
		if(strcmp(dirent_ptr->d_name,".") && strcmp(dirent_ptr->d_name,"..")){
			tmpdir1 = (char*)malloc(strlen(datasetX) + strlen(dirent_ptr->d_name) + 2);
			strcpy(tmpdir1,datasetX);
			strcat(tmpdir1,"/");
			strcat(tmpdir1,dirent_ptr->d_name);
			dir_ptr2 = opendir(tmpdir1);
			while(dirent_ptr = readdir(dir_ptr2)) //Diavasma twn json arxeiwn
				if(strcmp(dirent_ptr->d_name,".")  && strcmp(dirent_ptr->d_name,"..")){
					json = (char*)malloc(strlen(tmpdir1) + strlen(dirent_ptr->d_name) + 2);
					strcpy(json,tmpdir1);
					strcat(json,"/");
					strcat(json,dirent_ptr->d_name); 
					//printf("%s\n",json);
					if( item = parse(json) ){						// an epistrefetai to item dhmiourgeitai to pair (to opoio prepei na bei sthn domh apothikeushs twn pairs)
									
						fstats = (FileStats*)malloc(sizeof(FileStats)); //Dhmiourgia stats tou arxeiou
						fstats->item = item;
						fstats->index = fIndex++;
						fstats->numOfWords = 0;
						HTinit(&(fstats->words));
						CreateDictionary(fstats, &words, &stopwords,&wIndex);
						HTinsert(&files, item->id , (void*)fstats);


						pair = (Pair*)malloc(sizeof(Pair));
						pair->item = item;
						
						pair->cliq = (Clique*) malloc(sizeof(Clique));
						sprintf(buff,"%d",id);
						tmp = (char*)malloc(strlen(buff) + 1 );
						strcpy(tmp,buff);
						pair->cliq->id = tmp;
						id++;
						
						pair->cliq->related = (Queue*)malloc(sizeof(Queue));
						HTinit(&(pair->cliq->unrelated));
						
						QueueInit(pair->cliq->related);
						QueueInsert(pair->cliq->related, (void**)&pair); // Sthn arxh h related oura exei mono to idio to pair 
						
							
	 					HTinsert(&pairs,item->id,(void*)pair);
	 					
	 					
					}
						
					free(json);
				}
			free(tmpdir1);
			closedir(dir_ptr2);
		}
			
	closedir(dir_ptr1);
	
	
	// CSV READ
	
	read_csv(&pairs,datasetW);
	
	for( i = 0; i < numBuckets; i++)
		MakeCliqueHT(pairs.buckets[i],&cliques);
	
	for( i = 0; i < numBuckets; i++)
		ChangeUnrelated(cliques.buckets[i]);
	
	
	output = fopen("unrelated.csv","w");
	for( i = 0; i < numBuckets; i++)
		printUnrelated(cliques.buckets[i],output,buff, &train, &test, &valid, &files );
	fclose(output);
	
	output = fopen("related.csv","w");
	sprintf(buff,"left_item , right_item\n");
	fwrite(buff,sizeof(char),strlen(buff),output);
	for( i = 0; i < numBuckets; i++)
		printRelated(pairs.buckets[i],output,buff, &train, &test, &valid, &files);
	fclose(output);
	
	
	for( i = 0; i < numBuckets; i++)
		CreateTFIDF(files.buckets[i],fIndex);
	

	if( lim > wIndex)		// gia na mhn kseperasei to orio twn leksewn
		limit = wIndex;
	else 
		limit = lim;
	
	if(limit < wIndex)
		CutOffDictionary(&words, &files, limit);
	
	LRtrain(&lr,&train,2*limit,'t');
	printf("Training finished\n");

	printf("Accuracy: %f\n",LRtest(&lr,&test,2*limit,'t'));


	HTdestr(&pairs,&PairDestroy,'v');
	HTdestr(&cliques,&CliqueDestroy,'v');
	HTdestr(&files,&FilesDestroy,'v');
	HTdestr(&words,&WordsDestroy,'b');
	HTdestr(&stopwords,NULL,'k');
	RBdestr();
	
	return 0;
	
}


