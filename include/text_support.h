#define lim 1000000
#define maxIters 10000
#define lrate 0.01
#define epsilon 0.001
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
void LRtrain(LogisticRegression* ,Queue* ,int ,int );
double LRtest(LogisticRegression* ,Queue* ,int ,int );
double LRpred(LogisticRegression* ,double* , int );