#include "acutest.h"
#include "structs.h"


void test_stcreate(void){	// elegxoume an h StackInit douleuei kai arxikopoiei swsta ta values

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
	
	//Tha eleksoume an h stack douleuei me thn xrhsh char
	for( i=0 ; str[i]!='\0' ;  i++){
		
		push( &stack , str[i] );
		
		// Tha elegksoyme an auksithike to megethos ths stack
		TEST_ASSERT(stack.count == (i + 1));
		
		//Elegxoume an sthn arxh mpainei to swsto value
		TEST_ASSERT(str[i] == stack.head->data);
	}
	
	//Diagrafh komvwn
	for( i=0; (str[i] != '\0' && stack.head != NULL) ; i++ ){
		temp=stack.head;
		stack.head=stack.head->next;
		free(temp);
		stack.count--;
	}
	
	//Elegxoume an diagrafthke h lista
	TEST_ASSERT(StackEmpty(&stack));
	TEST_ASSERT(stack.head == NULL);

}

void test_stcheck(void){
	
	Stack stack;
	StackInit( &stack );
	
	char* str="{[\"This is a string\"]}";
	int i , flag=0, count=0;
	
	struct StackNode* temp;
	
	//Tha eleksoume an h stack douleuei me thn xrhsh char
	for( i=0 ; str[i]!='\0' ;  i++){
		
		
		// Tha elegksoyme an auksithike to megethos ths stack otan prepei kai an meiwthike otan ekleisan oi antistoixes paretheseis
		
		if(str[i]==']' || str[i]=='}' || (str[i]=='"' && flag==1)){
			check( &stack , str[i] );
			TEST_ASSERT(stack.count == --count);
		}
		else if (str[i]=='[' || str[i]=='{' || (str[i]=='"' && flag==0)){
			check( &stack , str[i] );
			TEST_ASSERT(stack.count == ++count);
			//Elegxoume an sthn arxh mpainei to swsto value
			TEST_ASSERT(str[i] == stack.head->data);
			if(str[i]=='"' && flag==0 )
				flag=1;
			
		}
		
	}
	//Elegxoume an h stoiva einai kenh
	TEST_ASSERT(StackEmpty(&stack));
	TEST_ASSERT(stack.head == NULL);

	
}


	



//Pinakas me tests
TEST_LIST = {
	{ "stack_create", test_stcreate },
	{ "stack_push", test_stpush },
	{ "stack_check", test_stcheck },
	{ NULL, NULL } // NULL sto telos
};
