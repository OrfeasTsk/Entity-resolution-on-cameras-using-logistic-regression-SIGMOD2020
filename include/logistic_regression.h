#define maxIters 100
#define lrate 0.01
#define epsilon 0.0001
#define dBoundary 0.5
#define nthreads 12
#define batchSize 1024

typedef struct{
	double * weights;
	double tol;
	double learning_rate;
	double dec_boundary;
	int epochs;
} LogisticRegression;


void LRinit(LogisticRegression* , double , double  ,double ,int );
void LRtrain(LogisticRegression* ,Queue* ,int ,char,int,int );
double LRtest(LogisticRegression* ,Queue* ,int ,char,int,int );
double LRpred(LogisticRegression* ,double* ,Record* , int, char );
void UpdateWeights(LogisticRegression* , double* , double* , double ,int, int );
void CalculateF(LogisticRegression* , double* , double* , double , int );
void SparseIteration(Link , LogisticRegression*  ,double* ,double*  ,int , char , int);