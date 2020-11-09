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
	struct StackNode* temp,*curr;
	
	//tha eleksoume an h stack douleuei me thn xrhsh char
	for( i=0 ; str[i]!="\0" ;  i++){
		
		push( &stack , str[i] );
		
		// tha elegksoyme an auksithike to megethos ths stack
		TEST_ASSERT(stack.count == (i + 1));
		
		//elegxoume an sthn arxh mpainei to swsto value
		TEST_ASSERT(str[i] == stack.head->data);
	}
	
	//diagrafh komvwn
	for( i=0, curr=stack.head ; (str[i]!="\0" && curr!=NULL) ; i++ ){
		temp=curr;
		curr=curr->next;
		free(temp);
		stack.count--;
	}
	
	//elegxoume an diagrafthke h lista
	TEST_ASSERT(StackEmpty(&stack));

}
	



//Pinakas me tests
TEST_LIST = {
	{ "stack_create", test_stcreate },
	{ "stack_push", test_stpush },
	/*{ "list_remove_next", test_remove_next },
	{ "list_find", test_find },
	{ "list_find_node", test_find_node },*/
	{ NULL, NULL } // NULL sto telos
};
