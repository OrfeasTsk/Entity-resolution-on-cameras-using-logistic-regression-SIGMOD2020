#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>


int parse(char* json){
	char* tmp,c,prev = ' ';
	int i, start=0,flag=0,count=0;
	FILE* fd;
	
	
	fd=fopen(json,"r");	//Anoigma tou json
	if(fd == NULL) 
		return 1;
		
		
	while(!feof(fd)){
		
		c = fgetc(fd);
		
		if( c == '"' && flag == 0){
			start = count;
			flag = 1 ;
		}
		else if ( c == '"' && prev != '\\' && flag == 1){
			tmp = (char*)malloc((count - start - 1)*sizeof(char) + 1);
			fseek(fd,start + 1,SEEK_SET);
			for( i = 0; i < count - start - 1; i++)
				tmp[i] = fgetc(fd);
			tmp[count - start - 1] = '\0';
			fseek(fd,count + 1,SEEK_SET);
			printf("%s\n",tmp);
			flag = 0;
		}  
			
		count++;
		prev = c;
	}
	
	fclose(fd);
	return 0;
	
		
}




int main(int argc, char* argv[]){
	int i;
	char* datasetX=NULL,*datasetW=NULL,*tmpdir1,*json;
	DIR* dir_ptr1,*dir_ptr2;
	struct dirent* dirent_ptr;
	
	
	if(argc != 5){
		printf("Argument error\n");
			return 1;
	}
	
	for(i = 1 ; i < argc ; i += 2){ //Den mas endiaferei h seira pou dinontai kai den epitrepei tis epanalhpseis twn parametrwn

		if(!strcmp("-x",argv[i]) && datasetX == NULL)
			datasetX=argv[i+1];
		else if(!strcmp("-w",argv[i]) && datasetW == NULL)
			datasetW=argv[i+1];
		else{
			printf("Argument error\n");
			return 1;
		}
	}
	

	
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
					printf("%s\n",json);
					parse(json);
					
				}
			free(tmpdir1);
			closedir(dir_ptr2);
		}
			
	closedir(dir_ptr1);

	return 0;
	
}


