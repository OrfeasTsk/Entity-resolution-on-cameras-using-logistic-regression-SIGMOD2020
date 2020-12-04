#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/structs.h"



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

int QueueEmpty(Queue* queue){
	
	return queue->count == 0;
}

void QueueConcat(Queue* q1 , Queue* q2,Clique* cliq){
	struct QueueNode* curr = q2->head,*prev;
	Pair* pair;
	
	while( curr != NULL ){
		pair = (Pair*)(curr->data);
		pair->cliq = cliq; //Ola ta items exoun ws related oura thn q1
		QueueInsert(q1,(void**)&pair); //Eisagwgh tous apo thn q2 sthn q1
		prev = curr;
		curr = curr->next;
		free(prev); //Apodesmeush tou komvou ouras ths q2
	}
	
	free(q2); //Apodesmeush ths q2
	
}


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

void check(Stack * stack, char c ){ // Diagrafh prwtou item elegxontas an prepei na diagraftei(auto to blepoume apo ta analoga tou [ me ], { me } kai " me " ), alliws push tou char
	
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
	else if(c == '[' || c == '{')							// diaforetika kanoume push to stoixeio
		push(stack,c);
	
}

int StackEmpty(Stack * stack){
	return stack->count == 0;
}



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
printf("%s\n", p->rbitem->id); /* Print root node */
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


Link NEW(char* id,void* obj, Link l, Link r, int color){ 
	Link x =(Link)malloc(sizeof(struct RBnode));
  	x->l = l; x->r = r; 
	x->color=color;
	if( id != NULL && obj != NULL){
		x->rbitem = (RBItem*)malloc(sizeof(RBItem));
    	x->rbitem->obj = obj;
		x->rbitem->id = id;
	}
    return x;
}

 
void RBinit() //Arxikopoihsh tou kenou komvou
	{ z = NEW( NULL ,NULL, NULL, NULL, BLACK); }
  
void RBdestr()
{
	free(z);
	z = NULL;
}
  
void RBTinit(Link* head)//Arxikopoihsh tou deikth tou dentrou
  { *head = z; }


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

Link insertR(Link h, char* id,void* obj ,Link head)
{   
	char* v = id;
    RBItem* t = h->rbitem;
   
    if (h == z) //Base case
	    if(h != head)
	    	return NEW(id,obj, z, z, RED);  //Kathe neos komvos prepei na einai kokkinos
	    else 
			return NEW(id,obj, z , z , BLACK); // Ektos apo thn riza pou einai maurh
    if( strcmp(v,t->id) < 0 ){ //Psaxnoume thn thesh gia na valoume ton neo komvo
        h->l = insertR(h->l, id,obj,head);
        if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo aristera (afou to paidi exei bei aristera)
	    	h=MakeRBTree(h,head);
	}
    else if( strcmp(t->id,v) < 0 ) {
		h->r = insertR(h->r, id,obj,head);
		if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo deksia (afou to paidi exei bei deksia)
			h=MakeRBTree(h,head);
	}
	else if( t->obj == NULL)
		t->obj = obj;
		
	return h;
  }
  
Link RBTinsertR( Link head , char* id , void* obj ){ 

	head = insertR( head , id , obj , head );
  	return head; 
}


Pair* RBTfindPair(Link h,char* id){
   
    RBItem* t = h->rbitem;
    struct QueueNode* curr;
    Pair* pair;
    
    if(h == z)								// an den brethei timi 
		return NULL;
    
    if( strcmp(id , t->id) < 0 )						// diasxizoume to dentro gia na broume thn timi
		return RBTfindPair(h->l,id);
	else if ( strcmp(t->id , id) < 0)
		return RBTfindPair(h->r, id);
	else{									// otan tin broume elegxoume thn oura twn pairs
			pair  = (Pair*)(t->obj);
			return pair;
	}
    
    
	
}

void printOutput(Link h,FILE* output,char* buff,int numBuckets){			
	
	RBItem* t = h->rbitem;
    struct QueueNode *curr, *prev=NULL, *temp;
 	
		
    Pair* pair;	
	Pair* rel_pair;	
	
	if(h == z)			// base-case
		return;
		
	printOutput(h->l,output,buff,numBuckets);	// anadromika phgainoume aristera
	
	
	pair  = (Pair*)(t->obj);
	curr = pair->cliq->related->head;
	while( curr != NULL ){								// diasxizoume thn related 
		rel_pair  = (Pair*)(curr->data);															// related_pairs	
		if( !strcmp( pair->item->id , rel_pair->item->id ) ){										// an einai to idio item
		
			if (curr == pair->cliq->related->head ){														// an einai o head
				if( curr == pair->cliq->related->tail ){													// an einai to monadiko antikeimeno
					pair->cliq->related->head=NULL;														// diagrafh tou komvou
					pair->cliq->related->tail=NULL;
					pair->cliq->related->count--;
					temp=curr;
					curr = curr->next; 
					free(temp);
					free(pair->cliq->related); //To teleutaio pair katastrefei thn oura
					HTdestr(&(pair->cliq->unrelated),numBuckets,&RBTdestrC); //To teleutaio pair katastrefei to dentro
					free(pair->cliq->id);
					free(pair->cliq);

				}
				else{																				// diaforetika o head tha deiksei ston epomeno komvo
					pair->cliq->related->head=curr->next;
					pair->cliq->related->count--;
					temp=curr;
					curr = curr->next; 
					free(temp);
				}
			}
			else if(curr == pair->cliq->related->tail){													// an einai to teleutaio item
				pair->cliq->related->tail = prev;															// tha metakinithei enan komvo pisw
				prev->next = NULL;
				pair->cliq->related->count--;
				temp = curr;
				curr = curr->next;
				free(temp);
			}
			else{																					// se opoiadhpote allh periptwsh
				prev->next=curr->next;
				pair->cliq->related->count--;
				temp = curr;
				curr = curr->next;
				free(temp);
			}
			
		}
		else{																						// an den einai ta ektypwnoume
			sprintf(buff,"%s , %s \n", pair->item->id , rel_pair->item->id );			
			fwrite(buff,sizeof(char),strlen(buff),output);
			prev = curr;
			curr = curr->next;
		}
		
	}

	
	
	printOutput(h->r,output,buff,numBuckets);	// anadromika phgainoume deksia
	
	
	
	
}





void ItemDestroy(Item* item){
	Spec* spec;
	struct QueueNode* curr = item->specs.head,*Temp;
	
	
	while( curr != NULL ){
		spec = (Spec*)(curr->data);
		free(spec->name);
		free(spec->value);
		free(spec);
		Temp = curr;
		curr = curr->next;
		free(Temp);
	}
	
	free(item->id);
	free(item);
}


void PairDestroy(Pair* pair){
	
	
	ItemDestroy(pair->item);
	free(pair);
	
	
}



void RBTdestrP(Link* head)//Katastrofh tou dentrou zeugariwn
{

	Pair* pair;
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    RBTdestrP(&((*head)->l));
    RBTdestrP(&((*head)->r));
    
    
	pair = (Pair*)((*head)->rbitem->obj);
	PairDestroy(pair);
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}



void RBTdestrC(Link* head)//Katastrofh tou dentrou klikwn
{
	Clique* cliq;
	
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    RBTdestrC(&((*head)->l));
    RBTdestrC(&((*head)->r));
    
       
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}






void RBTmergeHT(Link* head,HashTable* ht, int numBuckets)				//Merge duo dentrwn
{
	Pair* pair;
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    RBTmergeHT(&((*head)->l),ht,numBuckets);
    RBTmergeHT(&((*head)->r),ht,numBuckets);
    

    if((*head)->rbitem->obj != NULL){
		pair = (Pair*)((*head)->rbitem->obj);
		HTinsert(ht,numBuckets,pair->item->id,(void*)pair);
	}
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}




void CliqueConcat(Pair* pair1 , Pair* pair2, int choice, int numBuckets){
	Clique* temp;
	
	
	if(choice == 1){	// dld an tairiazoun
		temp = pair2->cliq;
		HTmerge(&(pair1->cliq->unrelated),&(pair2->cliq->unrelated),numBuckets);
		QueueConcat(pair1->cliq->related,pair2->cliq->related,pair1->cliq);
		free(temp->id);
		free(temp);
		}
	else{				// dld den tairiazoun
		HTinsert(&(pair1->cliq->unrelated),numBuckets,pair2->item->id,(void*)pair2);
		HTinsert(&(pair2->cliq->unrelated),numBuckets,pair1->item->id,(void*)pair1);
	}
	
}


void MakeCliqueHT(Link pairTree, HashTable* ht, int numBuckets){
	
	RBItem* t = pairTree->rbitem;
 			
    Pair* pair;	

	
	if(pairTree == z)			// base-case
		return;
		
	MakeCliqueHT(pairTree->l,ht,numBuckets);	// anadromika phgainoume aristera
	
	if(t->obj != NULL){	
		pair  = (Pair*)(t->obj);
		HTinsert(ht,numBuckets,pair->cliq->id,(void*)(pair->cliq));
	}

	MakeCliqueHT(pairTree->r,ht,numBuckets);	// anadromika phgainoume deksia

}


void MakeCliqueUnrelated(Link* oldTree, HashTable* ht, int numBuckets){
	
	RBItem* t = (*oldTree)->rbitem;
 			
    Pair* pair;	

	
	if(*oldTree == z)			// base-case
		return;
		
	MakeCliqueUnrelated(&((*oldTree)->l),ht,numBuckets);	// anadromika phgainoume aristera
	MakeCliqueUnrelated(&((*oldTree)->r),ht,numBuckets);	// anadromika phgainoume deksia

	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
		pair  = (Pair*)(t->obj);
		HTinsert(ht,numBuckets,pair->cliq->id,(void*)(pair->cliq));
	}


	free((*oldTree)->rbitem);
	free(*oldTree);
	*oldTree = NULL;
	

}



void ChangeUnrelated(Link h, HashTable* ht,int numBuckets){
	
	RBItem* t = h->rbitem;
    int i;		
    Clique* cliq;	
	HashTable* unrelated;
	
	
	if(h == z)			// base-case
		return;
	
	ChangeUnrelated(h->l,ht,numBuckets);	// anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
	
		unrelated =(HashTable*)malloc(sizeof(HashTable));
		HTinit(unrelated,numBuckets);
		
		cliq  = (Clique*)(t->obj);
		
		for( i = 0; i < numBuckets; i++)
			MakeCliqueUnrelated(&(cliq->unrelated.buckets[i]),unrelated,numBuckets);
		
		for( i = 0; i < numBuckets; i++)	
			cliq->unrelated.buckets[i] = unrelated->buckets[i];
		
		free(unrelated->buckets);
		free(unrelated);
	
	}
	
	
	ChangeUnrelated(h->r,ht,numBuckets);	// anadromika phgainoume aristera
	
}






void RemoveUnrelated(Link h , char* id){
	
	
	RBItem* t = h->rbitem;
    Clique* cliq;
    
    if(h == z)								// an den brethei timi 
		return;
    
    if( strcmp(id , t->id) < 0 )						// diasxizoume to dentro gia na broume thn timi
		return RemoveUnrelated(h->l, id);
	else if (strcmp(t->id , id ) < 0)
		return RemoveUnrelated(h->r, id);
	else{									// otan tin broume elegxoume thn oura twn pairs
			if(t->obj != NULL)
				t->obj = NULL;

	
	}
	
}






void VisitUnrelated(Link h, Clique* cliq,FILE* output,char* buff, int numBuckets){
	
	RBItem* t = h->rbitem;
	int hashnum;
    struct QueueNode* ptr,*unrelptr;		
    Clique* unrelc;
	Pair* pair, *unrelp;	
	
	if(h == z)			// base-case
		return;
	
	VisitUnrelated(h->l,cliq,output,buff,numBuckets);	// anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
		unrelc  = (Clique*)(t->obj);
		
		for( ptr = cliq->related->head ; ptr != NULL ; ptr = ptr->next ){
			pair = (Pair*)(ptr->data);
			for( unrelptr = unrelc->related->head ; unrelptr != NULL ; unrelptr = unrelptr->next){
				unrelp = (Pair*)(unrelptr->data);
				sprintf(buff,"%s , %s \n", pair->item->id , unrelp->item->id );
				fwrite(buff,sizeof(char),strlen(buff),output);
			}	
		}
		
		hashnum = hashFunction(cliq->id,numBuckets);
		RemoveUnrelated(unrelc->unrelated.buckets[hashnum], cliq->id);
	
	}
	
	
	VisitUnrelated(h->r,cliq,output,buff,numBuckets);	// anadromika phgainoume aristera
	
}





void printUnrelated(Link h,FILE* output,char* buff, int numBuckets){
	
	RBItem* t = h->rbitem;	
	int i;	
    Clique* cliq;	
	
	if(h == z)			// base-case
		return;
	
	printUnrelated(h->l,output,buff,numBuckets);	// anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		cliq  = (Clique*)(t->obj);
		for( i = 0; i < numBuckets; i++)
			VisitUnrelated(cliq->unrelated.buckets[i],cliq,output,buff,numBuckets);
		
	}
	
	
	printUnrelated(h->r,output,buff,numBuckets);	// anadromika phgainoume aristera
	
}


/*##################                  Start of hash tables                             ##########################*/

void HTinit( HashTable* ht, int numBuckets ){			// initialise of hash table
	
	int i;
	
	ht->buckets=(Link*)malloc(sizeof(Link)*numBuckets); 
	for( i = 0; i < numBuckets; i++ )					// each hash table has a tree
		RBTinit( &(ht->buckets[i]) );
	
}

int hashFunction(char* str,int numBuckets){ //Polynomial hash function for strings
	int hash = 0;
	int constant = 33;
	while(*str != '\0'){
		hash = (constant*hash + *str) % numBuckets;
		str++;
	}
	return hash;
}


void HTinsert( HashTable* ht, int numBuckets, char* key, void* item ){			
	
	int hashnum;
	
	hashnum = hashFunction( key , numBuckets );
	ht->buckets[hashnum] = RBTinsertR( ht->buckets[hashnum] , key , item);
	
}

void HTmerge( HashTable* ht1 , HashTable* ht2, int  numBuckets){
	int i;
	
	for( i = 0; i < numBuckets; i++)
		RBTmergeHT(&(ht2->buckets[i]), ht1, numBuckets);
	
	free(ht2->buckets);
		
}



Pair* HTfindPair(HashTable* ht,int numBuckets,char* id){
	
	int hashnum = hashFunction(id,numBuckets);
	
	return RBTfindPair(ht->buckets[hashnum],id);
	
}

void HTdestr(HashTable* ht,int numBuckets,void (*del_fun)(Link*)){
	int i;
		
	for( i = 0; i < numBuckets; i++)
		(*del_fun)(&(ht->buckets[i]));
		
	free(ht->buckets);
	
}

/*##################                  End of hash tables                               ##########################*/




