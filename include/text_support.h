#include "./logistic_regression.h"
#define lim 1000
#define maxSplit 20
#define trhold 0.05
#define step 0.15




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
void CreateNewTrainingSet(LogisticRegression*,HashTable* ,HashTable*  ,Queue* , Heap* ,int , int ,int );
void ResolveTransitivity(HashTable* , Heap* , Queue* );