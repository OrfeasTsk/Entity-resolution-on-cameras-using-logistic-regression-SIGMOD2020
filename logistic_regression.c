#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./include/structs.h"
#include "./include/logistic_regression.h"

JobScheduler* schelduler;
int weightSize, tp, numThreads, threadsFinished,bSize,lastFinished,totalCorrect;
double* weights;
LogisticRegression* model;



/*##################              START OF LOGISTIC REGRESSION MODEL                    ##########################*/

double sigmoid(double f){

	return 1.0/(1.0 + exp(-f));

}


void UpdateWeights(LogisticRegression* lr , double* w ,double* error, double val, int totalFiles ,int index ){ //Enhmerwsh twn varwn


	w[index] -= lr->learning_rate * (*error) * val/totalFiles; // wj = wj - learningRate * sum((sigmoid(w^T * xi + b) - yi) * xij)

}

void CalculateF(LogisticRegression* lr, double* w ,double* f, double  val, int index){ //Enhmerwsh tou eswterikou ginomenou

	
	*f += w[index] * val; //w^T*xi
	

}


void LRinit(LogisticRegression* lr, double tol, double learning_rate ,double dec_boundary,int epochs){

	lr->weights = NULL;
	lr->tol = tol;
	lr->learning_rate = learning_rate;
	lr->dec_boundary = dec_boundary;
	lr->epochs = epochs;


}


double LRpred(LogisticRegression* lr,double* w,Record* record, int size, char type){  //Provlepsh tou montelou
	int j;
	double f = w[0]; //Arxikopoihsh me ton stathero oro

	for( j = 0; j < numBuckets; j++ ){
		SparseIteration(record->item1->words.buckets[j], lr, w ,&f, 1 , type , -1);
		SparseIteration(record->item2->words.buckets[j], lr, w ,&f, size/2 + 1 , type , -1);
	}

	//f += lr->weights[j + 1] * X[j]; 
	
	return sigmoid(f);
}


void* LRthreadTest(void* args){
	int i, y, correct;
	int times = *(int*)args;
	struct QueueNode* ptr;
	Record* record;

	while(1){

		get_job(schelduler,&ptr);

		if(ptr == NULL)
			break;

		correct = 0;

		for( i = 0; i < times && ptr != NULL; i++ , ptr = ptr->next ){
			record = (Record*)(ptr->data);
			y = record->value;
					
			if(LRpred(model,model->weights,record, weightSize, tp) > model->dec_boundary ){
				if( y == 1 )
					correct++;
			}
			else{
				if( y == 0)
					correct++;
			}
		}

	
		pthread_mutex_lock(&(schelduler->struct_mux));
		totalCorrect+= correct;
		pthread_mutex_unlock(&(schelduler->struct_mux));

	}
	
	pthread_exit(NULL);
}


double LRtest(LogisticRegression* lr,Queue* test,int size,char type,int thNum,int batSize){  //Testing me vash to montelo kai epistrofh ths akriveias

	int count,j;
	struct QueueNode* curr;
	totalCorrect = 0;
	weightSize = size;
	schelduler = (JobScheduler*)malloc(sizeof(JobScheduler));
	model = lr;
	tp = type;
	numThreads = thNum;
	bSize = batSize;

	initialize_schelduler(schelduler ,numThreads,numThreads, &LRthreadTest, &bSize );

	for(curr = test->head, count = 0; curr != NULL ; curr=curr->next,count++)
		if(count % bSize == 0)
			add_job(schelduler,curr);

	for( j = 0; j < numThreads; j++) //Stelnei sta threads oti den exoun allo job
		add_job(schelduler,NULL);

	for( j = 0; j < numThreads; j++)
		pthread_join(schelduler->tids[j],NULL);

	destroy_schelduler(schelduler);
	free(schelduler);	


	return (double)totalCorrect/test->count;
}



void* LRthreadTrain(void* args){
	int i,j,y;
	double error;
	int times = *(int*)args;
	struct QueueNode* ptr;
	Record* record;
	double* currWeights = (double*)malloc(sizeof(double)*(weightSize + 1)); // Dianysma me varh


	while(1){

		get_job(schelduler,&ptr);

		if(ptr == NULL)
			break;

		for( j = 0; j < weightSize + 1;  j++)
			currWeights[j] = 0.0;



		for( i = 0; i < times && ptr != NULL; i++ , ptr = ptr->next ){

			record=(Record*)(ptr->data);
			y = record->value;

			error = LRpred(model,model->weights,record,weightSize,tp) - y; // sigmoid(w^T*xi + b) - yi
			
			currWeights[0] -= model->learning_rate * error/bSize ;

			

			for( j = 0; j < numBuckets; j++ ){
				SparseIteration(record->item1->words.buckets[j], model,currWeights ,&error, 1 , tp, 1);
				SparseIteration(record->item2->words.buckets[j], model,currWeights ,&error, weightSize/2 + 1 ,tp, 1);
			}

			//	lr->weights[j + 1] -= lrate * error * X[j]; 
		}

		pthread_mutex_lock(&(schelduler->struct_mux));
		for( j = 0; j < weightSize + 1;  j++) //Kathe dianysma enos thread prostithetai se ena dianysma
			weights[j] += currWeights[j];
		threadsFinished++;
		if(threadsFinished == numThreads)
			pthread_cond_signal(&(schelduler->cond_finished)); //Epeidh teleiwse kai to teleutaio thread		
		else if(ptr == NULL){ // Epeidh einai to teleutaio genika
			lastFinished = 1;
			pthread_cond_signal(&(schelduler->cond_finished)); //Epeidh teleiwse kai to teleutaio thread	
		}
		pthread_mutex_unlock(&(schelduler->struct_mux));

	}

	free(currWeights);
	pthread_exit(NULL);

}



void LRtrain(LogisticRegression* lr,Queue* train,int size,char type,int thNum,int batSize){ //Training tou montelou

	int j,t,count,jobsAdded = 0;
	double f;
	struct QueueNode* curr;
	weightSize = size;
	schelduler = (JobScheduler*)malloc(sizeof(JobScheduler));
	model = lr;
	tp = type;
	numThreads = thNum;
	bSize = batSize;
	threadsFinished = 0;
	lastFinished = 0;



	if(lr->weights == NULL)
		lr->weights = (double*)malloc(sizeof(double)*(size + 1)); // Dianysma me varh
	double* wtmp = (double*)malloc(sizeof(double)*(size + 1)); //Dianysma me ta prohgoymena varh
	weights = (double*)malloc(sizeof(double)*(size + 1)); // Dianysma me varh

	for( j = 0; j < size + 1;  j++){ //Arxikopoihsh dianysmatwn
		lr->weights[j] = 0.0;
		weights[j] = 0.0;
		wtmp[j] = 0.0;
	}


	initialize_schelduler(schelduler ,numThreads,numThreads, &LRthreadTrain, &bSize );


	for( t = 0; t < lr->epochs; t++){
		
		for(curr = train->head, count = 0; curr != NULL ; curr=curr->next,count++){
			
			if(count % bSize == 0){
				add_job(schelduler,curr);
				jobsAdded++;
			}

			if(jobsAdded == numThreads){
				pthread_mutex_lock(&(schelduler->struct_mux));
				while(threadsFinished != numThreads)
					pthread_cond_wait(&(schelduler->cond_finished), &(schelduler->struct_mux));
				threadsFinished = 0;
				for( j = 0; j < size + 1 ; j++){
					lr->weights[j] += weights[j]/numThreads;
					weights[j] = 0.0; 
				}
				pthread_mutex_unlock(&(schelduler->struct_mux));
				jobsAdded = 0;				
			}
		}
		
		
		if(jobsAdded){ //An exoun meinei jobs sto telos
			pthread_mutex_lock(&(schelduler->struct_mux));
			while(!lastFinished)
				pthread_cond_wait(&(schelduler->cond_finished), &(schelduler->struct_mux));
			lastFinished = 0;
			for( j = 0; j < size + 1 ; j++){
				lr->weights[j] += weights[j]/jobsAdded;
				weights[j] = 0.0; 
			}
			pthread_mutex_unlock(&(schelduler->struct_mux));
		}


		f = 0.0;
		for( j = 0; j < size + 1 ; j++){
			f += (lr->weights[j] - wtmp[j])*(lr->weights[j] - wtmp[j]);
			wtmp[j] = lr->weights[j];
		}

		if(sqrt(f) < lr->tol)  //||wt+1-wt|| < epsilon
			break;

	}

	for( j = 0; j < numThreads; j++) //Stelnei sta threads oti den exoun allo job
		add_job(schelduler,NULL);

	for( j = 0; j < numThreads; j++)
		pthread_join(schelduler->tids[j],NULL);

	destroy_schelduler(schelduler);
	free(schelduler);
	free(weights);
	free(wtmp);

}



void SparseIteration(Link h, LogisticRegression* lr,double* w ,double* p ,int start, char type, int totalFiles){  //Diasxish se araio pinaka


	RBItem* t = h->rbitem;	
    ModelStats* mstats;	
	
	if(h == z)			// Base-case
		return;
	
	SparseIteration(h->l , lr, w, p , start, type , totalFiles);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		mstats  = (ModelStats*)(t->obj);
		
		if(type == 'b'){	 //Bow
			if(totalFiles != -1)
				UpdateWeights(lr,w,p,(double)(mstats->bow_val),totalFiles,mstats->wstats->index + start);  
			else
				CalculateF(lr,w,p,(double)(mstats->bow_val),mstats->wstats->index + start);

		}
		else{ //Tfidf
			if(totalFiles != -1)
				UpdateWeights(lr,w,p,mstats->tfidf_val,totalFiles,mstats->wstats->index + start);
			else
				CalculateF(lr,w,p,mstats->tfidf_val,mstats->wstats->index + start);
		}

	}
	
	
	SparseIteration(h->r, lr, w, p , start, type , totalFiles);	// Anadromika phgainoume aristera

}



/*##################              END OF LOGISTIC REGRESSION MODEL                    ##########################*/
