#define RED 0
#define BLACK 1


typedef struct RBnode* Link;
extern Link z;
Link z;



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
void RBTinit(Link*);
void RBTdestrP(Link*);
void RBTdestrC(Link*);
Link RBTinsertR(Link,char*,void*);


/*##################                  End of red-black trees                           ##########################*/

/*##################                  Start of hash tables                             ##########################*/





void printOutput(Link, FILE*, char*,int );
void PairDestroy(Pair*);



void QueueInit(Queue*);
void QueueInsert(Queue*,void **);
int QueueEmpty(Queue* );
void QueueConcat(Queue*, Queue*,Clique*);


void HTinit( HashTable* , int );
void HTinsert( HashTable* , int , char* , void* );
Pair* HTfindPair(HashTable* , int , char* );
void HTmerge( HashTable* , HashTable* , int );
void HTdestr(HashTable* ,int ,void (*del_fun)(Link*));




void MakeCliqueHT(Link, HashTable*, int );
void CliqueConcat(Pair*, Pair*, int,int );
void ChangeUnrelated(Link, HashTable*, int );
void printUnrelated(Link ,FILE* ,char*,int );





