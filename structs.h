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
