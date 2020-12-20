#define maxIters 100
#define lrate 0.01
#define epsilon 0.0001
#define dBoundary 0.5

typedef struct{
	double * weights;
	double tol;
	double learning_rate;
	double dec_boundary;
	int epochs;
} LogisticRegression;


void LRinit(LogisticRegression* , double , double  ,double ,int );
void LRtrain(LogisticRegression* ,Queue* ,int ,char );
double LRtest(LogisticRegression* ,Queue* ,int ,char );
double LRpred(LogisticRegression* ,Record* , int, char );
void UpdateWeights(LogisticRegression* , double* , double ,int, int );
void CalculateF(LogisticRegression* , double* , double , int );
void SparseIteration(Link , LogisticRegression*  ,double*  ,int , char , int);

