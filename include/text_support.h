#define maxIters 100000
#define lrate 0.01
#define epsilon 0.001

typedef struct{
	double * weights;
} LogisticRegression;



Item* parse(char*);
void read_csv(HashTable* ,char*, int);
void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  ,int , int ** , int* );
void read_stopwords(HashTable* ,char* ,int );
void CreateDictionary(Stats* , HashTable* ,HashTable* , int);
void UpdateArray(Stats*  , HashTable*  , int , int** );
double** Bow_To_Tfidf(int ** , int , int );
void CutOffDictionary(HashTable*,int , int);

