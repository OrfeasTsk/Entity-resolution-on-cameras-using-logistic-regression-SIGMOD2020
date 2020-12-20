#include <stdio.h>
#include <stdlib.h>
#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"



void test_htcreate(void){
	int i;
	HashTable ht;
	z = NULL;
	
	ht.buckets = NULL;
	
	RBinit();
	HTinit(&ht);
	TEST_ASSERT( ht.buckets != NULL ); //Dhmiourgithikan ta buckets? 
	for( i = 0; i < numBuckets; i++)
		TEST_ASSERT( ht.buckets[i] == z ); //Deixnoun oloi oi deiktes twn dentrwn ston dummy komvo?
	HTdestr(&ht, NULL, 'n');
	TEST_ASSERT( ht.buckets == NULL);
	RBdestr();
	
	
	
}


void test_htinsert(void){
	int i ,*value;
	char* key;
	char buff[10];
	HashTable ht;
		
	RBinit();
	HTinit(&ht);

	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"item%d",i);
		
		key = (char*)malloc(strlen(buff) + 1 );
		strcpy(key,buff);
		value = (int*)malloc(sizeof(int));
		*value = i;
		
		HTinsert(&ht,key,(void*)value);		
 		value = NULL;
 		key = NULL;
 		
		key = (char*)HTfind(&ht,buff,'k');
		value = (int*)HTfind(&ht,buff,'v');
		
		
		TEST_ASSERT( key != NULL ); //Yparxei to key sto hashtable?
		TEST_ASSERT( !strcmp(key,buff)); //Vrethike to idio key?
		TEST_ASSERT( value != NULL ); //Yparxei to value sto hashtable?
		TEST_ASSERT( *value == i); //Vrethike to idio value?
		
	}
	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"item%d",i);
		
		key = (char*)malloc(strlen(buff) + 1 );
		strcpy(key,buff);
		value = (int*)malloc(sizeof(int));
		*value = i;
		
		HTinsert(&ht,key,(void*)value);		

		TEST_ASSERT( key != (char*)HTfind(&ht,buff,'k')); //Yparxei to key hdh sto hashtable?
		TEST_ASSERT( value != (int*)HTfind(&ht,buff,'v')); //Yparxei to value hdh sto hashtable?
	
		free(key);
		free(value);
	}
	
	 
	HTdestr(&ht,NULL,'b');
	TEST_ASSERT( ht.buckets == NULL );	
	RBdestr();
}



void test_htmerge(void){
	int i;
	char buff[15];
	Pair* pair;
	HashTable ht1,ht2;
		
	RBinit();
	HTinit(&ht1);
	HTinit(&ht2);
	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"item%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		QueueInit(&(pair->item->specs));
		strcpy(pair->item->id,buff);
		
		HTinsert(&ht1,pair->item->id,(void*)pair);		
				
	}
	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"newItem%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		QueueInit(&(pair->item->specs));
		strcpy(pair->item->id,buff);
		
		HTinsert(&ht2,pair->item->id,(void*)pair);				
	}
	
	HTmerge(&ht1,&ht2);
	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"newItem%d",i);
		
		pair = (Pair*)HTfind(&ht1,buff,'v');
		TEST_ASSERT( pair != NULL ); //Yparxei to pair sto h1?
		TEST_ASSERT( !strcmp(pair->item->id,buff)); //Vrethike to swsto pair?				
	}
	
	 
	HTdestr(&ht1,&PairDestroy,'v');
	TEST_ASSERT( ht1.buckets == NULL );
	TEST_ASSERT( ht2.buckets == NULL );		
	RBdestr();
	
}


