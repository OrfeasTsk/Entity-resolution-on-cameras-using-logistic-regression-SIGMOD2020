#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include "./include/structs.h"
#include "./include/text_support.h"






int main(int argc, char* argv[]){
	int i, j, id = 0 , numBuckets = -1 ,fIndex = 0 ,wIndex = 0;
	char* datasetX=NULL, *datasetW=NULL, *stopwordsFile=NULL, *tmpdir1, *json, *tmp;
	char buff[200];
	DIR* dir_ptr1,*dir_ptr2;
	FILE* output;
	struct dirent* dirent_ptr;
	Item* item;
	Stats* fileStats;
	Pair *pair;
	HashTable pairs;
	HashTable cliques;
	HashTable words;
	HashTable stopwords;
	HashTable stats;
	
	
	if(argc != 9){
		printf("Argument error\n");
			return 1;
	}
	
	for(i = 1 ; i < argc ; i += 2){ //Den mas endiaferei h seira pou dinontai kai den epitrepei tis epanalhpseis twn parametrwn

		if(!strcmp("-x",argv[i]) && datasetX == NULL)
			datasetX=argv[i+1];
		else if(!strcmp("-w",argv[i]) && datasetW == NULL)
			datasetW=argv[i+1];
		else if(!strcmp("-b",argv[i]) && numBuckets == -1)
			numBuckets = atoi(argv[i+1]);
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
	HTinit(&cliques, numBuckets);
	HTinit(&pairs,numBuckets);
	HTinit(&stopwords,numBuckets);
	HTinit(&words,numBuckets);
	HTinit(&stats,numBuckets);

	
	//Read Stopwords file
	read_stopwords(&stopwords , stopwordsFile, numBuckets);




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
									
						fileStats = (Stats*)malloc(sizeof(Stats)); //Dhmiourgia stats tou arxeiou
						fileStats->item = item;
						fileStats->index = fIndex++;
						CreateDictionary(fileStats, &words, &stopwords, numBuckets);
						HTinsert(&stats, numBuckets, item->id , (void*)fileStats);


						pair = (Pair*)malloc(sizeof(Pair));
						pair->item = item;
						
						pair->cliq = (Clique*) malloc(sizeof(Clique));
						sprintf(buff,"%d",id);
						tmp = (char*)malloc(strlen(buff) + 1 );
						strcpy(tmp,buff);
						pair->cliq->id = tmp;
						id++;
						
						pair->cliq->related = (Queue*)malloc(sizeof(Queue));
						HTinit(&(pair->cliq->unrelated),numBuckets);
						
						QueueInit(pair->cliq->related);
						QueueInsert(pair->cliq->related, (void**)&pair); // Sthn arxh h related oura exei mono to idio to pair 
						
							
	 					HTinsert(&pairs,numBuckets,item->id,(void*)pair);
	 					
	 					
					}
						
					free(json);
				}
			free(tmpdir1);
			closedir(dir_ptr2);
		}
			
	closedir(dir_ptr1);
	
	
	// CSV READ
	
	read_csv(&pairs,datasetW,numBuckets);
	
	for( i = 0; i < numBuckets; i++)
		MakeCliqueHT(pairs.buckets[i],&cliques,numBuckets);
	
	for( i = 0; i < numBuckets; i++)
		ChangeUnrelated(cliques.buckets[i],&cliques,numBuckets);
	
	
	output = fopen("unrelated.csv","w");
	for( i = 0; i < numBuckets; i++)
		printUnrelated(cliques.buckets[i],output,buff,numBuckets);
	fclose(output);
	
	output = fopen("related.csv","w");
	sprintf(buff,"left_item , right_item\n");
	fwrite(buff,sizeof(char),strlen(buff),output);
	for( i = 0; i < numBuckets; i++)
		printOutput(pairs.buckets[i],output,buff,numBuckets);
	fclose(output);
	
	
	CutOffDictionary(&words,numBuckets ,1000);
	
	
	//Bow Array
	double** array = (double**)malloc( sizeof(double*) * (fIndex));
	for( i = 0 ; i < fIndex ; i++ )
		array[i] = (double*)malloc( sizeof(double) * 1000 ); 
	
	// Arxikopoihsh me 0		
	for( i = 0 ; i < fIndex ; i++ )
		for( j = 0 ; j < 1000 ; j++ )
			array[i][j] = 0.0;
			
	for( i = 0; i < numBuckets; i++)
		CreateArray( stats.buckets[i], &words, numBuckets, array );		
		

	HTdestr(&cliques,numBuckets,&RBTdestrC);
	HTdestr(&pairs,numBuckets,&RBTdestrP);
	RBdestr();
	
	return 0;
	
}


