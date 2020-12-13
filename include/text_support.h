#define maxIters 100000
#define lrate 0.01
#define epsilon 0.001

typedef struct{
	double * weights;
} LogisticRegression;



Item* parse(char*);
void read_csv(HashTable* ,char*, int);
void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  ,int , double** , int* );
void read_stopwords(HashTable* ,char* ,int );
void CreateDictionary(Stats* , HashTable* ,HashTable* , int);
void UpdateArray(Stats*  , HashTable*  , int , double** );
double** Bow_To_Tfidf(double** , int , int );
void CutOffDictionary(HashTable*,int , int);
void InsertWord(HashTable* , HashTable*  ,int , char* );

