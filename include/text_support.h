#include "./logistic_regression.h"
#define lim 1000
#define maxSplit 20
#define trhold_init 0.05
#define step1 0.05
#define step2 0.1
#define step3 0.3


Item* parse(char*);
void read_csv(HashTable* ,char*);
void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  , FileStats* ,int* );
void read_stopwords(HashTable* ,char*  );
void CreateDictionary(FileStats* , HashTable* ,HashTable*,int* );
void InsertWord(HashTable* , HashTable*   , char* ,FileStats* ,int*  );
void CutOffDictionary( HashTable*, HashTable* , int );
void DatasetSplit(Queue * , Queue *, Queue *, Record*  );
void TrainingSetStats(HashTable* , Queue* , HashTable* );
void CreateNewTrainingSet(LogisticRegression*,HashTable* ,HashTable*  ,Queue* , Heap* ,int , int ,int,int,int );
void ResolveTransitivity(HashTable* , Heap* , Queue* );