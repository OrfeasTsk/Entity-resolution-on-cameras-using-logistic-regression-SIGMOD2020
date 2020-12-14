#define lim 1000
#define maxIters 100000
#define lrate 0.01
#define epsilon 0.001

typedef struct{
	double * weights;
} LogisticRegression;



Item* parse(char*);
void read_csv(HashTable* ,char*);
void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  , double** , int* );
void read_stopwords(HashTable* ,char*  );
void CreateDictionary(Stats* , HashTable* ,HashTable* );
void UpdateArray(Stats*  , HashTable*   , double** );
double** Bow_To_Tfidf(double** , int , int );
void CutOffDictionary(HashTable*,int );
void InsertWord(HashTable* , HashTable*   , char* );

