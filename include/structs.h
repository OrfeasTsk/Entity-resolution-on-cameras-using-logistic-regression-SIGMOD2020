#define RED 0
#define BLACK 1
#define numBuckets 100


typedef struct RBnode* Link;
extern Link z;
Link z;

typedef struct{
	double * weights;
} LogisticRegression;

/*##################                  Start Generic Queue                                        ##########################*/

struct QueueNode{
        void* data;
        struct QueueNode* next;
        
};

typedef struct{
        struct QueueNode* head;
        struct QueueNode* tail;
        int count;
        
}Queue;

typedef struct{			// each node has the name of the spec and it's value
	char* name;
	char* value;
}Spec; 

typedef struct{
	char* id;
	Queue specs;
	
}Item;



/*##################                  End Generic Queue                                        ##########################*/

/*##################               Start Stack For only one char !! Used in Json Parse !!                        ##########################*/



struct StackNode{ //Komvos listas
	char data;
	struct StackNode* next;
};

typedef struct LinkedStack{ //Domh listas
	struct StackNode* head;
	int count;
}Stack;


void StackInit(Stack*);
struct StackNode * push(Stack *, char);
void check(Stack *, char);
int StackEmpty(Stack *);

/*##################                  End Stack                           ##########################*/

typedef struct{
	Link * buckets;
	int count;
} HashTable;
/*##################                  End of hash tables                               ##########################*/



typedef struct{
	char* id;
	Queue* related;
	HashTable unrelated;
}Clique;


typedef struct{
	Item* item;
	Clique* cliq;
}Pair;


typedef struct{
	Item* item;
	int index;
	int numOfWords;
	HashTable words;
}FileStats;

typedef struct{
	char* word;
	int index;
	HashTable files;
}WordStats;




typedef struct{
	WordStats* wstats;
	double count;
}Details;

typedef struct{
	WordStats* wstats;
	int bow_val;
	double tfidf_val;
}ModelStats;

typedef struct{
	FileStats* item1;
	FileStats* item2;
	int value;
}Record;


/*##################                  Start OF HEAP                          ##########################*/

struct heapNode{ //Komvos heap
    Details* data; 
    struct heapNode* left; 
	struct heapNode* right; 
}; 


typedef struct heapTree{  //Domh swrou
	struct heapNode* head;
	int nodes;
	int height;
}Heap;


void HeapInit(Heap*);
void HeapInsert(Heap* ,Details*);
Details* HeapRemoveFirst(Heap*);
void HeapDestroy(Heap*);
void HeapifyWords(Link* ,Heap*,int);
struct heapNode* newNode(Details* );
int swap(struct heapNode* ,struct heapNode*  );



/*##################                  End OF HEAP                             ##########################*/



/*##################                  Start of red-black trees                           ##########################*/


typedef struct{ //Antikeimeno komvou tou red-black tree
	char* id;
	void* obj;
}RBItem;

struct RBnode{ 
	RBItem* rbitem; 
	Link l, r; 
	int color; 
};

void treeprint(Link, int, int, Link);
void RBinit();
void RBdestr();
void RBTdestr(Link*,void (*del_fun)(void*),char);
void RBTinit(Link*);
void* RBTfind(Link,char*,char);
Link RBTinsertR(Link,char*,void*, int*);


/*##################                  End of red-black trees                           ##########################*/

/*##################                  Start of hash tables                             ##########################*/





void printRelated(Link, FILE*, char*,Queue * , Queue *, Queue * ,HashTable* );
void PairDestroy(void*);
void CliqueDestroy(void*);
void WordsDestroy(void*);
void FilesDestroy(void*);



void QueueInit(Queue*);
void QueueInsert(Queue*,void **);
int QueueEmpty(Queue* );
void QueueConcat(Queue*, Queue*,Clique*);


int hashFunction(char* , int ) ;
void HTinit( HashTable*  );
void HTinsert( HashTable*  , char* , void* );
void* HTfind(HashTable*  , char* , char);
void HTmerge( HashTable* , HashTable*  );
void HTdestr(HashTable*  ,void (*del_fun)(void*),char);




void MakeCliqueHT(Link, HashTable* );
void CliqueConcat(Pair*, Pair*, int );
void ChangeUnrelated(Link );
void printUnrelated(Link ,FILE* ,char*,Queue * , Queue *, Queue *, HashTable*  );
void CreateTFIDF( Link, int );
void SumTFIDF( Link , Details* );
void ItemDestroy(Item* );
void AdjustMStats(Link ,HashTable* );

void CreateVector(Link , double * , int , char );



