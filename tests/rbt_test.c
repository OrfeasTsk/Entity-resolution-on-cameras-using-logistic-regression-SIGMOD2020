#include <stdio.h>
#include <stdlib.h>
#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"



void test_rbtcreate(void){
	Link treeptr = NULL;
	z = NULL;
	
	RBinit();
	TEST_ASSERT( z != NULL ); //Elegxos gia arxikopoihsh tou dummy komvou
	RBTinit(&treeptr);
	TEST_ASSERT( treeptr == z ); //O deikths deixnei ston dummy komvo?
	RBTdestr(&treeptr,NULL,'n');
	TEST_ASSERT( treeptr == NULL );	
	RBdestr();
	TEST_ASSERT( z == NULL );
	
}


void test_rbtinsert(void){
	int i;
	int flag;
	char buff[10];
	Link treeptr = NULL;
	Pair* pair,*newpair;
	
		
	RBinit();
	RBTinit(&treeptr);

	
	for(i = 0; i < 100;  i++){
		flag = 0;
		newpair = NULL;
		sprintf(buff,"item%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		QueueInit(&(pair->item->specs));
		strcpy(pair->item->id,buff);
		
		treeptr = RBTinsertR(treeptr, pair->item->id , (void*)pair ,&flag); //Eisagwgh tou pair
 		
		newpair = (Pair*)RBTfind(treeptr, buff , 'v' );
		
		TEST_ASSERT(flag == 1); //To pair mphke
		TEST_ASSERT( newpair != NULL ); //Yparxei to pair sto dentro?
		TEST_ASSERT( pair == newpair); //Vrethike to idio pair?
		
	}
	
	for(i = 0; i < 100;  i++){
		flag = 0;
		newpair = NULL;
		sprintf(buff,"item%d",i);
		
		pair = (Pair*)malloc(sizeof(Pair)); //Dhmiourgia pair
		pair->item = (Item*)malloc(sizeof(Item)); // Dhmiourgia item
		pair->item->id = (char*)malloc(strlen(buff) + 1);
		QueueInit(&(pair->item->specs));
		strcpy(pair->item->id,buff);
		
		treeptr = RBTinsertR(treeptr, pair->item->id , (void*)pair,&flag); //Eisagwgh tou pair
 		
		newpair = (Pair*)RBTfind(treeptr, buff , 'v' );
		
		TEST_ASSERT(flag == 0); //To pair den bhke (den epitrepontai diplotypa)
		TEST_ASSERT( newpair != NULL ); //Yparxei to pair sto dentro?
		TEST_ASSERT( pair != newpair); //Vrethike allo pair? (Afou den epitrepontai diplotypa)
		PairDestroy(pair);
	}
	
	 
	RBTdestr(&treeptr,&PairDestroy,'v');
	TEST_ASSERT( treeptr == NULL );	
	RBdestr();
	TEST_ASSERT( z == NULL );
	

}







