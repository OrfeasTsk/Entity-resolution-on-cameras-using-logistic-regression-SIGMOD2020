#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include "./include/structs.h"


int getNumId(char* fullId){
	int count;
	
	for( count = 0; count < 2 ; fullId++)		// Mono o arithmos
		if(*fullId == '/')
			count++;			
						
	return atoi(fullId);
	
}


Item* parse(char* json){
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


void read_csv(HashTable* ht,char* datasetW,int numBuckets){
	
	int i,hashnum;
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
				pairA = HTfindPair(ht,numBuckets,token); //Euresh tou left item	
			}
			if(i == 1){
				pairB = HTfindPair(ht,numBuckets,token);  //Euresh tou right item
			}
			if( i == 2)
				if(pairA != NULL && pairB != NULL)
					if(atoi(token) == 1){ //An tairiazoun 
						if(pairA->cliq->related != pairB->cliq->related) //An den exoun enwthei ksana
							CliqueConcat(pairA, pairB, 1,numBuckets);
					}
					else{				// alliws sthn periptwsh tou 0 (dld dn tairiazoun)
						CliqueConcat(pairA, pairB, 0,numBuckets);
					}
			
			
			token = strtok(NULL, ",");			// continue to tokenize the string we passed first
		}
	}

	fclose(csv_file);
	
}




int main(int argc, char* argv[]){
	int i, id = 0 , numBuckets = -1;
	char* datasetX=NULL,*datasetW=NULL,*tmpdir1,*json,*tmp;
	char buff[200];
	DIR* dir_ptr1,*dir_ptr2;
	FILE* output;
	struct dirent* dirent_ptr;
	Item* item;
	Pair *pair;
	HashTable pairs;
	HashTable cliques;
	
	
	if(argc != 7){
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
		else{
			printf("Argument error\n");
			return 1;
		}
	}
	
	// Trees initialise
	RBinit();

	//Hash Table initialise
	HTinit( &cliques, numBuckets );
	HTinit(&pairs,numBuckets);
	




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
	
	HTdestr(&cliques,numBuckets,&RBTdestrC);
	HTdestr(&pairs,numBuckets,&RBTdestrP);
	RBdestr();
	
	return 0;
	
}


