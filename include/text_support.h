#define lim 1000000
#define maxIters 100
#define lrate 0.01
#define epsilon 0.0001
#define maxSplit 20




Item* parse(char*);
void read_csv(HashTable* ,char*);
void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  , FileStats* ,int* );
void read_stopwords(HashTable* ,char*  );
void CreateDictionary(FileStats* , HashTable* ,HashTable*,int* );
void InsertWord(HashTable* , HashTable*   , char* ,FileStats* ,int*  );
void CutOffDictionary( HashTable*, HashTable* , int );
void DatasetSplit(Queue * , Queue *, Queue *, Record*  );
void LRtrain(LogisticRegression* ,Queue* ,int ,char );
double LRtest(LogisticRegression* ,Queue* ,int ,char );
double LRpred(LogisticRegression* ,Record* , int, char );
void UpdateWeights(LogisticRegression* , double* , double ,int, int );
void CalculateF(LogisticRegression* , double* , double , int );