#define TEST_NO_MAIN
#include "../include/acutest.h"
#include "../include/structs.h"
#include "../include/text_support.h"


int count;
JobScheduler* schelduler;

void * thread_testing1( void* args ){
	pthread_mutex_lock(&(schelduler->struct_mux));
	count++;
	pthread_mutex_unlock(&(schelduler->struct_mux));
	pthread_exit(NULL);
}

void * thread_testing2( void* args ){
	
	struct QueueNode *curr1;
	
	get_job(schelduler,&curr1);
	pthread_mutex_lock(&(schelduler->struct_mux));
	if(curr1 == NULL)
		count++;
	pthread_mutex_unlock(&(schelduler->struct_mux));
	pthread_exit(NULL);
}


void test_initializeSchelduler(void){
	
	int i;
	int numThreads=10;
	count=0;
	
	schelduler = (JobScheduler*)malloc(sizeof(JobScheduler));
	
	initialize_schelduler(schelduler ,numThreads, numThreads, &thread_testing1, NULL);
	for( i = 0; i < numThreads; i++)
		pthread_join(schelduler->tids[i],NULL);
	
	TEST_ASSERT( schelduler->num_threads == numThreads );
	TEST_ASSERT( schelduler->buffer_size == numThreads );
	TEST_ASSERT( schelduler->circular_buff->start == 0 );
	TEST_ASSERT( schelduler->circular_buff->end == -1 );
	TEST_ASSERT( schelduler->circular_buff->count == 0);
	TEST_ASSERT( numThreads == count );
	
	destroy_schelduler(schelduler);
	free(schelduler);
	
}

void test_jobs(void){
	
	int i;
	int numThreads=10;
	count=0;
	
	schelduler = (JobScheduler*)malloc(sizeof(JobScheduler));
	
	initialize_schelduler(schelduler ,numThreads, numThreads, &thread_testing2, NULL);
	
	for( i = 0; i < numThreads; i++) //Stelnei sta threads oti den exoun allo job
		add_job(schelduler,NULL);

	for( i = 0; i < numThreads; i++)
		pthread_join(schelduler->tids[i],NULL);
		
		
	TEST_ASSERT( numThreads == count );	
	
	destroy_schelduler(schelduler);
	free(schelduler);

	
}

