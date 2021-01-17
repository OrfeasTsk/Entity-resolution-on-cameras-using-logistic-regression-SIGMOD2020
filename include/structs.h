#include <pthread.h>
#define RED 0
#define BLACK 1
#define numBuckets 50


typedef struct RBnode* Link;
typedef struct HeapItem Details;
typedef struct RelItems Clique;

extern Link z;
Link z;



/*##################                  START OF QUEUE                                        ##########################*/

struct QueueNode{
        void* data;
        struct QueueNode* next;
        
};

typedef struct{
        struct QueueNode* head;
        struct QueueNode* tail;
        int count;
        
}Queue;

void QueueInit(Queue*);
void QueueInsert(Queue*,void **);
int QueueEmpty(Queue* );
void QueueConcat(Queue*, Queue*,Clique*);
void QueueDelete(Queue*,char);


/*##################                  END OF QUEUE                                     ##########################*/




/*##################               START OF STACK                         ##########################*/



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

/*##################                  END OF STACK                           ##########################*/






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
void HeapDestroyW(Heap*);
void HeapifyWords(Link* ,Heap*,int);
struct heapNode* newNode(Details* );
int swap(struct heapNode* ,struct heapNode*  );



/*##################                  End OF HEAP                             ##########################*/



/*##################                  START OF RED-BLACK TREES                        ##########################*/


typedef struct{ //Antikeimeno komvou tou red-black tree
	char* id;
	void* obj;
	int valid;
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


/*##################                  END OF RED-BLACK TREES                        ##########################*/


/*##################                  START OF HASHTABLES                          ##########################*/

typedef struct{
	Link * buckets;
	int count;
} HashTable;


int hashFunction(char* , int ) ;
void HTinit( HashTable*  );
void HTinsert( HashTable*  , char* , void* );
void* HTfind(HashTable*  , char* , char);
void HTmerge( HashTable* , HashTable*  );
void HTdestr(HashTable*  ,void (*del_fun)(void*),char);

/*##################                  END OF HASHTABLES                              ##########################*/

/*##################                  START OF SOME OTHER STRUCTS                             ##########################*/

typedef struct{		
	char* name;
	char* value;
}Spec; 

typedef struct{
	char* id;
	Queue specs;
	
}Item;

struct RelItems{
	char* id;
	Queue* related;
	HashTable unrelated;
};


typedef struct{
	Item* item;
	Clique* cliq;
	int printed;
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


struct HeapItem{
	void* stats;
	double count;
};

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




/*##################                  END OF SOME OTHER STRUCTS                             ##########################*/

/*##################              START OF DESTROY FUNCTIONS                         ##########################*/

void ItemDestroy(Item*);
void PairDestroy(void*);
void CliqueDestroy(void*);
void WordsDestroy(void*);
void FilesDestroy(void*);

/*##################              END OF DESTROY FUNCTIONS                         ##########################*/



/*##################              START OF HELPER FUNCTIONS                         ##########################*/

void MakeCliqueHT(Link, HashTable* );
void CliqueConcat(Pair*, Pair*, int );
void ChangeUnrelated(Link );
void printRelated(Link, FILE*, char*,Queue * , Queue *, Queue * ,HashTable*,HashTable* );
void printUnrelated(Link ,FILE* ,char*,Queue * , Queue *, Queue *, HashTable*,HashTable*  );
void CreateTFIDF( Link, int );
void SumTFIDF( Link , Details* );
void AdjustMStats(Link ,HashTable* );
void RestorePairs(Link,int*,char*);
/*##################              END OF HELPER FUNCTIONS                         ##########################*/


/*##################              START OF THREADS                         ##########################*/


typedef struct{
	struct QueueNode* ptr;
}BuffItem;


typedef struct{ //Domh kyklikou buffer
	BuffItem* items;
	int start;
	int end;
	int count;
}CircularBuffer;

typedef struct{
	int num_threads; 
	int buffer_size;
	pthread_t* tids;
	CircularBuffer* circular_buff;  
	pthread_mutex_t mux;
	pthread_mutex_t struct_mux;
	pthread_cond_t cond_nonempty;
	pthread_cond_t cond_nonfull;
	pthread_cond_t cond_finished;

}JobScheduler;

void initialize_schelduler(JobScheduler* ,int,int, void* (*thread_fun)(void*),int* );
void add_job(JobScheduler* , struct QueueNode*);
void get_job(JobScheduler*, struct QueueNode**);
void destroy_schelduler(JobScheduler*);



