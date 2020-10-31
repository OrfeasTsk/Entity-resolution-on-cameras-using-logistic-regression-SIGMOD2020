#define RED 0
#define BLACK 1

typedef struct STnode* Link;
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
}SpecNode; 

typedef struct{
	char* id;
	Queue specs;
	
}Item;

void QueueInit(Queue* queue);
void QueueInsert(Queue* queue,void ** data);

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

void StackInit(Stack * stack);
struct StackNode * push(Stack * stack, char data);
void check(Stack * stack, char c);
int empty(Stack * stack);

/*##################                  End Stack                           ##########################*/

typedef struct{ //Antikeimeno komvou tou red-black tree
	int id;
	Queue queue;
}RBItem;

struct STnode{ 
	RBItem* rbitem; 
	Link l, r; 
	int color; 
};



