


void textCleaning(char*);
void tokenize(char* , HashTable* , HashTable*  ,int , int ** , int* );
void read_stopwords(HashTable* ,char* ,int );
void CreateDictionary(Stats* , HashTable* ,HashTable* , int , int*);
void UpdateArray(Stats*  , HashTable*  , int , int** );
double** Bow_To_Tfidf(int ** , int , int );
