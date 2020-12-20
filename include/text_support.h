#define lim 1000000
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
