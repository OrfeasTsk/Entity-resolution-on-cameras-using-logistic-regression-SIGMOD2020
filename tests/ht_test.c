#include <stdio.h>
#include <stdlib.h>
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


void test_htinsert (void){
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
		
		
		TEST_ASSERT( key != NULL ); //Yparxei to key sto dentro?
		TEST_ASSERT( !strcmp(key,buff)); //Vrethike to idio key?
		TEST_ASSERT( value != NULL ); //Yparxei to value sto dentro?
		TEST_ASSERT( *value == i); //Vrethike to idio value?
		
	}
	
	for(i = 0; i < 100;  i++){
		
		sprintf(buff,"item%d",i);
		
		key = (char*)malloc(strlen(buff) + 1 );
		strcpy(key,buff);
		value = (int*)malloc(sizeof(int));
		*value = i;
		
		HTinsert(&ht,key,(void*)value);		

		TEST_ASSERT( key != (char*)HTfind(&ht,buff,'k')); //Yparxei to key hdh sto dentro?
		TEST_ASSERT( value != (int*)HTfind(&ht,buff,'v')); //Yparxei to value hdh sto dentro?
	
		free(key);
		free(value);
	}
	
	 
	HTdestr(&ht,NULL,'b');
	TEST_ASSERT( ht.buckets == NULL );	
	RBdestr();
}








//Pinakas me tests
TEST_LIST = {
	{ "ht_create", test_htcreate },
	{ "ht_insert", test_htinsert },
	{ NULL, NULL } // NULL sto telos
};
