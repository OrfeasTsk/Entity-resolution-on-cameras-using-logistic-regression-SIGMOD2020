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
	int id;
	Queue specs;
	
}Item;
