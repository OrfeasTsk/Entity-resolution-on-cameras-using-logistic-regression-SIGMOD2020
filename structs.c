#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/*##################                  Start Generic Queue                                        ##########################*/

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

void QueueConcat(Queue* q1 , Queue* q2){
	struct QueueNode* curr = q2->head,*prev;
	Pair* pair;
	
	while( curr != NULL ){
		pair = (Pair*)(curr->data);
		pair->related = q1; //Ola ta items exoun ws related oura thn q1
		QueueInsert(q1,(void**)&pair); //Eisagwgh tous apo thn q2 sthn q1
		prev = curr;
		curr = curr->next;
		free(prev); //Apodesmeush tou komvou ouras ths q2
	}
	
	free(q2); //Apodesmeush ths q2
	
}



/*void QueuePrint(Queue* queue){ 				//Ektypwsh ouras
        struct QueueNode *Temp;

        if(queue->head == NULL)
                return;
        
        for(Temp = queue->head ; Temp != NULL ; Temp = Temp->next)
                printf("%s",Temp->data);
        
}*/

/*##################                  End Generic Queue                                        ##########################*/


/*##################     Start Stack For only one char !! Used in Json Parse !!                ##########################*/


void StackInit(Stack * stack){ //Arxikopoihsh ths listas
	
	stack->head=NULL;
	stack->count=0;
	
}

struct StackNode * push(Stack * stack, char data){//Eisagwgh sthn arxh
	
	struct StackNode * Temp=(struct StackNode *)malloc(sizeof(struct StackNode));
	Temp->next=stack->head;
    Temp->data=data;
    stack->head=Temp;
    stack->count++;
	
	return Temp;
	
}

void check(Stack * stack, char c ){ // Diagrafh prwtou item elegxontas an prepei na diagraftei(auto to blepoume apo ta analoga tou [ me ], { me } kai " me " ), alliws push tou item
	
/*	if(stack->count == 0){
		printf("\nStack is empty!!\n");
	}*/
	
	struct StackNode * Temp;
	
	if(c==']'){					//Elegxoume an sthn korufh uparxei to analogo char
		if(stack->head->data == '['){
			Temp=stack->head;
    		stack->head=stack->head->next;
    		stack->count--;
    		free(Temp);
		}
	}	
	else if(c=='}'){				//Elegxoume an sthn korufh uparxei to analogo char
		if(stack->head->data == '{'){
			Temp=stack->head;
    		stack->head=stack->head->next;
    		stack->count--;
    		free(Temp);
		}
	}
	else if(c=='"'){				//Elegxoume an sthn korufh uparxei to analogo char
		if(stack->head->data == '"'){
			Temp=stack->head;
    		stack->head=stack->head->next;
    		stack->count--;
    		free(Temp);
		}
		else						// Giati tha exei elegxtei hdh to " 
			push(stack,c);
	}
	else							// diaforetika kanoume push to stoixeio
		push(stack,c);
	
}

int empty(Stack * stack){
	if(stack->count==0)
		return 1;
	else
		return 0;
}


/*
void ListDestroyLN(List * list){//Katastrofh ths listas

	struct ListNode * Temp;
	
	while(list->head != NULL){
       Temp=list->head;
       list->head=list->head->next;
       free(Temp);
    }

}
*/
/*##################              End Stack                            ##########################*/







//RED-BLACK





void treeprint(Link p, int indent,int type,Link head) /* Pretty print tree */
{ int i;
if (p != z) { /* If tree is not empty */
treeprint(p->r, indent+4,1,head);
/* Print right subtree 4 places right of root node */
for (i=0 ; i < indent ; i++)
printf(" "); /* Take care for indentation */
if(type==1 && p!=head)
printf("/");
if (type==2)
printf("\\");
printf("%d\n", p->rbitem->id); /* Print root node */
treeprint(p->l, indent+4,2,head);
/* Print left subtree 4 places right of root node */
}
} 


Link rotR(Link h) //Deksia peristrofh
  { Link x = h->l; h->l = x->r; x->r = h;
    return x; }

Link rotL(Link h) //Aristerh peristrofh
  { Link x = h->r; h->r = x->l; x->l = h;
    return x; }


Link NEW(int id,Pair** pair, Link l, Link r, int color){ 
	Link x =(Link)malloc(sizeof(struct RBnode));
  	x->l = l; x->r = r; 
	x->color=color;
	if( id != -1 && pair != NULL){
		x->rbitem = (RBItem*)malloc(sizeof(RBItem));
    	QueueInit(&(x->rbitem->pairs)); //Arxikopoihsh ths ouras
		QueueInsert(&(x->rbitem->pairs),(void **)pair);	//Eisagwgh sthn lista tou komvou
		x->rbitem->id=id;
	}
    return x;
  }

 
void RBinit() //Arxikopoihsh tou kenou komvou
	{ z = NEW( -1 ,NULL, NULL, NULL, BLACK); }
  
void RBdestr()
{
	free(z);
}
  
void RBTinit(Link* head)//Arxikopoihsh tou deikth tou dentrou
  { *head = z; }

/*void RBTdestr(Link* head)//Katastrofh tou dentrou
{
    if (*head==z)
		return;
    RBTdestr(&((*head)->l));
    RBTdestr(&((*head)->r));
    free((*head)->rbitem->date);
    ListDestroyLN(&((*head)->rbitem->list));
    free((*head)->rbitem);
	free(*head);
}*/


Link MakeRBTree(Link h,Link head){  //Synarthsh pou ftiaxnei to red-black tree 
Link leftchild=h->l , rightchild=h->r ;
if(leftchild->color==RED && rightchild->color==RED) //Periptwsh pou to deksi kai to aristero paidi einai kokkina
		if(rightchild->l->color != BLACK || rightchild->r->color != BLACK  || leftchild->l->color != BLACK || leftchild->r->color != BLACK){ //An yparxei kokkino eggoni
			if(h!=head)//Kanoume recoloring ektos ths rizas
				h->color=RED;
				leftchild->color=BLACK;
				rightchild->color=BLACK;
				return h;
}
			
if(leftchild->color==BLACK && rightchild->color==RED){ //Periptwsh pou to aristero paidi einai mauro kai to deksi kokkino
	if( rightchild->r->color == RED ){ //Periptwsh pou to aristero eggoni apo ta deksia einai mauro kai to deksi eggoni apo deksia kokkino 
		h->color=RED; //Allagh xrwmatos
		rightchild->color=BLACK; //Allagh xrwmatos
		h=rotL(h); //Peristrofh ston patera
		return h;
		}
	if(rightchild->l->color == RED){ //Periptwsh pou to aristero eggoni apo ta deskia einai kokkino kai to deksi eggoni apo deksia mauro
		h->color=RED; //Allagh xrwmatos
		rightchild->l->color=BLACK; //Allagh xrwmatos
		h->r=rotR(rightchild); // Peristrofh sto paidi
		h=rotL(h); //Peristrofh ston patera
		return h;
		}
}


if(leftchild->color==RED && rightchild->color==BLACK){ //Periptwsh pou to deksi paidi einai mauro kai to aristero kokkino
	if(leftchild->l->color == RED /*&& leftchild->r->color == BLACK*/ ){//Periptwsh pou to aristero eggoni apo ta aristera einai kokkino kai to deksi eggoni apo aristera mauro
		h->color=RED; //Allagh xrwmatos
		leftchild->color=BLACK; //Allagh xrwmatos
		h=rotR(h); //Peristrofh ston patera
		return h;
		}
	if( leftchild->r->color == RED ){ //Periptwsh pou to aristero eggoni apo ta aristera einai mauro kai to deksi eggoni apo deksia kokkino
		h->color=RED; //Allagh xrwmatos
		leftchild->r->color=BLACK; //Allagh xrwmatos
		h->l=rotL(leftchild); //Peristrofh sto paidi
		h=rotR(h); // Peristrofh ston patera
		return h;
		}
}

return h;

}

Link insertR(Link h, int id,Pair** pair ,Link head)
{   int v = id;
    RBItem* t = h->rbitem;
    if (h == z) //Base case
	    if(h != head)
	    	return NEW(id,pair, z, z, RED);  //Kathe neos komvos prepei na einai kokkinos
	    else 
			return NEW(id,pair, z , z , BLACK); // Ektos apo thn riza pou einai maurh
    if(v < t->id){ //Psaxnoume thn thesh gia na valoume ton neo komvo
        h->l = insertR(h->l, id,pair,head);
        if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo aristera (afou to paidi exei bei aristera)
	    	h=MakeRBTree(h,head);
	}
    else if(t->id < v) {
		h->r = insertR(h->r, id,pair,head);
		if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo deksia (afou to paidi exei bei deksia)
			h=MakeRBTree(h,head);
	}
	else
		QueueInsert(&(h->rbitem->pairs),(void **)pair);	//Eisagwgh sthn oura tou komvou
		
	return h;
  }
  
Link RBTinsertR(Link head,int id,Pair** pair)
{ head = insertR(head,id,pair,head);
  return head; 
}


Pair* findPair(Link h, int id, char* fullId){
   
    RBItem* t = h->rbitem;
    struct QueueNode* curr;
    Pair* pair;
    
    if(h == z)
		return NULL;
    
    if( id < t->id )
		return findPair(h->l, id, fullId);
	else if (t->id < id)
		return findPair(h->r, id, fullId);
	else{
		for( curr = t->pairs.head ; curr != NULL ; curr = curr->next){
			pair  = (Pair*)(curr->data);
			if(!strcmp(fullId,pair->item->id))
				return pair;
		}
		
		return NULL;
	}
    
    
	
}







