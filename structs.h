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

void QueueInit(Queue*);
void QueueInsert(Queue*,void **);
int QueueEmpty(Queue* );
void QueueConcat(Queue*, Queue*);

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
	Item* item;
	Queue* related;  //Na ginetai free
}Pair;


/*##################                  Start of red-black trees                           ##########################*/


typedef struct{ //Antikeimeno komvou tou red-black tree
	int id;
	Queue pairs;
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
void RBTdestr(Link*);
Link RBTinsertR(Link,int,Pair** );


/*##################                  End of red-black trees                           ##########################*/

Pair* findPair(Link , int , char* );
void printOutput(Link, FILE*, char* );
void PairDestroy(Pair*);

