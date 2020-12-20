#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"



void test_stcreate(void){	// Elegxoume an h StackInit douleuei kai arxikopoiei swsta ta values

	Stack stack;
	StackInit( &stack );
	TEST_ASSERT( StackEmpty( &stack ) );
	TEST_ASSERT(stack.head==NULL);
	
}

void test_stpush(void){

	Stack stack;
	StackInit( &stack );
	
	char* str="This is a string";
	int i;
	struct StackNode* temp;
	
	//Elegxos me thn xrhsh char
	for( i=0 ; str[i]!='\0' ;  i++){
		
		push( &stack , str[i] );
		
		//Auksithike to megethos ths stoivas?
		TEST_ASSERT(stack.count == (i + 1));
		
		//Sthn arxh mpainei to swsto value?
		TEST_ASSERT(str[i] == stack.head->data);
	}
	
	//Diagrafh komvwn
	for( i=0; (str[i] != '\0' && stack.head != NULL) ; i++ ){
		temp=stack.head;
		stack.head=stack.head->next;
		free(temp);
		stack.count--;
	}
	
	//Diagrafthke h lista?
	TEST_ASSERT(StackEmpty(&stack));
	TEST_ASSERT(stack.head == NULL);

}

void test_stcheck(void){
	
	Stack stack;
	StackInit( &stack );
	
	char* str="{[\"This is a string\"]}";
	int i , flag=0, count=0;
	
	
	for( i=0 ; str[i]!='\0' ;  i++){
		
		
		// Auksithike to megethos ths stoivas otan prepei kai an meiwthike otan ekleisan oi antistoixes paretheseis?
		
		if(str[i]==']' || str[i]=='}' || (str[i]=='"' && flag==1)){
			check( &stack , str[i] );
			TEST_ASSERT(stack.count == --count);
		}
		else if (str[i]=='[' || str[i]=='{' || (str[i]=='"' && flag==0)){
			check( &stack , str[i] );
			TEST_ASSERT(stack.count == ++count);
			//Sthn arxh mpainei to swsto value?
			TEST_ASSERT(str[i] == stack.head->data);
			if(str[i]=='"' && flag==0 )
				flag=1;
			
		}
		
	}
	//H stoiva einai kenh?
	TEST_ASSERT(StackEmpty(&stack));
	TEST_ASSERT(stack.head == NULL);

	
}


	

