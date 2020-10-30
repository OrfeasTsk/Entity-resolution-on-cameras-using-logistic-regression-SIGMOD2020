#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void QueueInit(Queue* queue){ 			//Arxikopoihsh ouras
        
        queue->head=NULL;
        queue->tail=NULL;
        queue->count=0;    
}

void QueueInsert(Queue* queue,void ** data){ //Eisagwgh sthn oura
        struct QueueNode *node=(struct QueueNode *)malloc(sizeof(struct QueueNode));
        node->data=*data;
        node->next=NULL;
        
        if(queue->tail == NULL){ 		//Gia na bei o prwtos komvos
        	queue->head=node;
        	queue->tail=node;
    	}
    	else{
            queue->tail->next=node;
            queue->tail=node;
        }
        
        queue->count++;
}


/*void QueuePrint(Queue* queue){ 				//Ektypwsh ouras
        struct QueueNode *Temp;

        if(queue->head == NULL)
                return;
        
        for(Temp = queue->head ; Temp != NULL ; Temp = Temp->next)
                printf("%s",Temp->data);
        
}*/

