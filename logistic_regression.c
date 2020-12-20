#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./include/structs.h"
#include "./include/logistic_regression.h"


/*##################              START OF LOGISTIC REGRESSION MODEL                    ##########################*/

double sigmoid(double f){

	return 1.0/(1.0 + exp(-f));

}


void UpdateWeights(LogisticRegression* lr , double* error, double val, int totalFiles ,int index ){ //Enhmerwsh twn varwn


	lr->weights[index] -= lr->learning_rate * (*error) * val; // wj = wj - learningRate * sum((sigmoid(w^T * xi + b) - yi) * xij)

}

void CalculateF(LogisticRegression* lr, double* f, double  val, int index){ //Enhmerwsh tou eswterikou ginomenou

	
	*f += lr->weights[index] * val; //w^T*xi
	

}


void LRinit(LogisticRegression* lr, double tol, double learning_rate ,double dec_boundary,int epochs){

	lr->weights = NULL;
	lr->tol = tol;
	lr->learning_rate = learning_rate;
	lr->dec_boundary = dec_boundary;
	lr->epochs = epochs;


}


double LRpred(LogisticRegression* lr,Record* record, int size, char type){  //Provlepsh tou montelou
	int j;
	double f = lr->weights[0]; //Arxikopoihsh me ton stathero oro

	for( j = 0; j < numBuckets; j++ ){
		SparseIteration(record->item1->words.buckets[j], lr ,&f, 1 , type , -1);
		SparseIteration(record->item2->words.buckets[j], lr ,&f, size/2 + 1 , type , -1);
	}

	//f += lr->weights[j + 1] * X[j]; 
	
	return sigmoid(f);
}

double LRtest(LogisticRegression* lr,Queue* test,int size,char type){  //Testing me vash to montelo kai epistrofh ths akriveias

	int y, correct = 0;
	struct QueueNode* curr;
	Record* record;


	for(curr = test->head; curr != NULL ; curr = curr->next){
			record = (Record*)(curr->data);
			y = record->value;
					
			if(LRpred(lr, record, size, type) > lr->dec_boundary ){
				if( y == 1 )
					correct++;
			}
			else{
				if( y == 0)
					correct++;
			}
	}


	return (double)correct/test->count;
}



void LRtrain(LogisticRegression* lr,Queue* train,int size,char type){ //Training tou montelou

	int j,t,y;
	double f,error;
	struct QueueNode* curr;
	Record* record;


	if(lr->weights == NULL)
		lr->weights = (double*)malloc(sizeof(double)*(size + 1)); // Dianysma me varh
	double* wtmp = (double*)malloc(sizeof(double)*(size + 1)); //Dianysma me ta prohgoymena varh

	for( j = 0; j < size + 1;  j++){ //Arxikopoihsh dianysmatwn
		lr->weights[j] = 0.0;
		wtmp[j] = 0.0;
	}

	for( t = 0; t < lr->epochs; t++){
		
		for(curr = train->head; curr != NULL ; curr=curr->next){
			record=(Record*)(curr->data);
			y = record->value;

			error = LRpred(lr,record,size,type) - y; // sigmoid(w^T*xi + b) - yi
			
			lr->weights[0] -= lr->learning_rate * error / train->count;

			for( j = 0; j < numBuckets; j++ ){
				SparseIteration(record->item1->words.buckets[j], lr ,&error, 1 , type, train->count);
				SparseIteration(record->item2->words.buckets[j], lr ,&error, size/2 + 1 ,type, train->count);
			}


			//	lr->weights[j + 1] -= lrate * error * X[j]; 

		}

		f = 0.0;
		for( j = 0; j < size + 1 ; j++){
			f += (lr->weights[j] - wtmp[j])*(lr->weights[j] - wtmp[j]);
			wtmp[j] = lr->weights[j];
		}

		if(sqrt(f) < lr->tol)  //||wt+1-wt|| < epsilon
			break;

	}


	free(wtmp);

}



void SparseIteration(Link h, LogisticRegression* lr ,double* p ,int start, char type, int totalFiles){  //Diasxish se araio pinaka


	RBItem* t = h->rbitem;	
    ModelStats* mstats;	
	
	if(h == z)			// Base-case
		return;
	
	SparseIteration(h->l , lr, p , start, type , totalFiles);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		mstats  = (ModelStats*)(t->obj);
		
		if(type == 'b'){	 //Bow
			if(totalFiles != -1)
				UpdateWeights(lr,p,(double)(mstats->bow_val),totalFiles,mstats->wstats->index + start);  
			else
				CalculateF(lr,p,(double)(mstats->bow_val),mstats->wstats->index + start);

		}
		else{ //Tfidf
			if(totalFiles != -1)
				UpdateWeights(lr,p,mstats->tfidf_val,totalFiles,mstats->wstats->index + start);
			else
				CalculateF(lr,p,mstats->tfidf_val,mstats->wstats->index + start);
		}

	}
	
	
	SparseIteration(h->r, lr, p , start, type , totalFiles);	// Anadromika phgainoume aristera

}


/*##################              END OF LOGISTIC REGRESSION MODEL                    ##########################*/