#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./include/structs.h"
#include "./include/text_support.h"




/*##################              START OF DESTROY FUNCTIONS                         ##########################*/


void ItemDestroy(Item* item){ //Diagrafh Item
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


void PairDestroy(void* obj){ //Diagrafh Pair
	Pair* pair = (Pair*)obj;
	
	ItemDestroy(pair->item);
	free(pair);
	
	
}

void CliqueDestroy(void* obj){ //Diagrafh Clique
	Clique* cliq = (Clique*)obj;
	
	QueueDelete(cliq->related,'n');
	free(cliq->related);
	HTdestr(&(cliq->unrelated),NULL,'n');
	free(cliq->id);
	free(cliq);
	
	
}


void WordsDestroy(void* obj){ //Diagrafh WordStats
	WordStats* wstats = (WordStats*)obj;
	HTdestr(&(wstats->files),NULL,'n');
	free(wstats);

}

void FilesDestroy(void* obj){ //Diagrafh FileStats
	FileStats* fstats = (FileStats*)obj;
	HTdestr(&(fstats->words),NULL,'v');
	free(fstats);

}

/*##################              END OF DESTROY FUNCTIONS                          ##########################*/


/*##################                  START OF HEAP                                  ##########################*/


void heaptreeprint(struct heapNode* p, int indent,int type,struct heapNode* head)  //Pretty print tree 
{ int i;
if (p != NULL) { // If tree is not empty
heaptreeprint(p->right, indent+4,1,head);
// Print right subtree 4 places right of root node 
for (i=0 ; i < indent ; i++)
printf(" "); // Take care for indentation 
if(type==1 && p!=head)
printf("/");
if (type==2)
printf("\\");
printf("%f\n", p->data->count); // Print root node 
heaptreeprint(p->left, indent+4,2,head);
//Print left subtree 4 places right of root node 
}
}


void HeapInit(Heap* h){ //Arxikopoihsh tou heap
	h->head=NULL;
	h->nodes=0;
	h->height=0;
}



struct heapNode* newNode(Details* data){  //Dhmiourgia neou komvou
    struct heapNode* temp =(struct heapNode*)malloc(sizeof(struct heapNode)); 
    temp->data=data; 
    temp->left=NULL;
	temp->right=NULL; 
    return temp; 
} 

int swap(struct heapNode* h1,struct heapNode* h2 ){ //Elegxei kai antallazei ta dedomena metaksy 2 heap komvwn
	Details* temp;
	
	if(h1->data->count < h2->data->count){
		temp=h1->data;
		h1->data=h2->data;
		h2->data=temp;
		return 1;
	}
	return 0;
}


int HeapRecInsert(struct heapNode* h , int level,Details* data){ //Anadromikh eisagwgh me anazhthsh kata epipedo
	
	if(level == 1) { //Teleutaio epipedo
        if(h->left == NULL ){ //An den yparxei aristero paidi
        	h->left=newNode(data);
        	swap(h,h->left);//Elegxos kai antallagh (an xreiazetai) me to aristero paidi
        	return 1;
		}
		if(h->right == NULL){ //An den yparxei deksi paidi
			h->right=newNode(data);
			swap(h,h->right);//Elegxos kai antallagh (an xreiazetai) me to deksi paidi
			return 1;
		}
	
	}
    else if(level > 1) //Anwtera epipeda
    { 
        if(HeapRecInsert(h->left, level-1,data)){ //An exei bei neos komvos apo aristera
        	swap(h,h->left);//Elegxos kai antallagh (an xreiazetai) me to aristero paidi
			return 1;		
		}
        if(HeapRecInsert(h->right, level-1,data)){//AN exei bei neos komvos apo deksia
			swap(h,h->right);//Elegxos kai antallagh (an xreiazetai) me to deksi paidi
        	return 1;
    	}
    } 
		
		return 0;
}


void HeapInsert(Heap* h,Details* data){ //Basikh methodos eisagwghs
	int sum,i;
	
	if(h->head == NULL){ //An den yparxei kapoios komvos sto dentro
		h->head=newNode(data);
		h->nodes=1;
		h->height=1;
	}
	else{
		sum=0;
		for(i = 0 ; i < h->height ; i++)
			sum+=pow(2,i);//Megistos arithmos komvwn mexri to epipedo i sto dentro
		if(sum == h->nodes)//Elegxos gia to ypsos
			h->height++;
		
		HeapRecInsert( h->head,h->height-1,data);
		
		h->nodes++;
	
	}
}

int findLastAndReplace(struct heapNode* h,struct heapNode** temp,struct heapNode* head,int level){ //Vriskei to teleutaio stoixeio kai to bazei sthn arxh(epistrefei 1 gia na "kladeusei")
	
	
	if(level == 1) {//Teleutaio epipedo
    	if(h==head){//Periptwsh pou sto teleutaio epipedo vrisketai h riza
		    if(head->left == NULL){//An den yparxei paidi(den ginetai elegxos gia to deski paidi giati to dentro einai plhres)
				free(head);
				head=NULL;
			}
			else if(head->right == NULL){ //An yparxei aristero paidi kai oxi deksi
				head->data=head->left->data; //Ginetai antallagh twn stoixeiwn me auto kai ths rizas
				free(head->left);
				head->left=NULL;
			}
			else if(head->right != NULL){//An yparxei deksi paidi
				head->data=head->right->data;//Ginetai antallagh twn stoixeiwn me auto kai ths rizas
				free(head->right);
				head->right=NULL;
			}
		   
		}
		else{
	    	if(h->left == NULL ){ //Elegxos gia aristero paidi prwta giati to dentro einai plhres
        		return 1 ;
        	}
        	else{
        		*temp=h; //Krataei ton teleutaio komvo me toulaxiston ena paidi
        	}
			if(h->right == NULL)
				return 1;
		}
	}
    else if(level > 1) //Anwtera epipeda
    { 
        if(findLastAndReplace(h->left,temp,head,level-1)){
			if(h == head){ //An exei stamathsei h anadromh se katwtero epipedo apo thn euresh enos komvou me ena h kanena paidi
				if((*temp)->right==NULL){//An yparxei aristero paidi kai oxi deksi
				head->data=(*temp)->left->data;//Ginetai antallagh twn stoixeiwn tou aristerou paidiou tou komvou me thn riza 
				free((*temp)->left);
				(*temp)->left=NULL;
				}
				else{//An yparxei deksi paidi
					head->data=(*temp)->right->data;//Ginetai antallagh twn stoixeiwn tou deksiou paidiou tou komvou me thn riza 
					free((*temp)->right);
					(*temp)->right=NULL;
				}
			}
			return 1;
		}
		
        if(findLastAndReplace(h->right,temp,head,level-1)){ //Omoiws 
			if(h == head){
				if((*temp)->right==NULL){
				head->data=(*temp)->left->data;
				free((*temp)->left);
				(*temp)->left=NULL;
				}
				else{
					head->data=(*temp)->right->data;
					free((*temp)->right);
					(*temp)->right=NULL;
				}
			}
			return 1;
		}
		else{ //Oriakh periptwsh(otan to teleutaio epipedo einai plhres den exoume vrei NULL paidi opote exei epistrafei 0 sthn riza)
			if(h==head){
					head->data=(*temp)->right->data;
					free((*temp)->right);
					(*temp)->right=NULL;
			}
		}
	}
		return 0;
	
}




void Heapify(struct heapNode* h){ //Synarthsh gia th dhmiourgia swrou
	
	if(h == NULL)
		return; 
	
	if(h->left == NULL) //An den exei paidia
		return;
	
	if(h->right == NULL){ //An exei aristero paidi kai oxi deksi
		if(swap(h,h->left))//An egine antallagh twn stoixeiwn me to aristero paidi
			Heapify(h->left);
	}
	else{//An exei aristero kai deksi paidi
		if(h->left->data->count > h->right->data->count){//Sygkrish twn paidiwn 
			if(swap(h,h->left))//An egine antallagh twn stoixeiwn me to aristero paidi
				Heapify(h->left);
			
		}
		else{
			if(swap(h,h->right))//An egine antallagh twn stoixeiwn me to deksi paidi
				Heapify(h->right);
		}
	}
}


Details* HeapRemoveFirst(Heap* h){//Afairei to megalytero stoixeio tou swrou
	int j,sum;
	Details* data;
	struct heapNode* temp=NULL;
	
	
	
	if(h == NULL)
		return NULL;
	
	if(h->head == NULL) //An den yparxei stoixeio
		return NULL;
		
	if(h->nodes == 1){ //An einai to teleutaio stoixeio
		data=h->head->data;
		free(h->head);
		h->head=NULL;
		h->nodes=0;
		h->height=0;
		return data;
	}
	
	data=h->head->data;//Pairnoume to prwto stoixeio
	findLastAndReplace(h->head,&temp,h->head,h->height-1);
	Heapify(h->head);
	h->nodes--;
	sum=0;
	for(j = 0 ; j < h->height-1 ; j++)
		sum+=pow(2,j);
	if(sum == h->nodes)//Diorthwsh tou ypsous
		h->height--;

	return data;
	
}


void HeapRecDestroyW(struct heapNode* h){//Anadromikh synarthsh gia katastrofh tou swrou
	
	WordStats* wstats; 

	if (h == NULL)
		return;
    HeapRecDestroyW(h->left);
    HeapRecDestroyW(h->right);
	wstats = (WordStats*)(h->data->stats);
    free(wstats->word);
    HTdestr(&(wstats->files),NULL,'n');
    free(wstats);
    free(h->data);
    free(h);
	
}

void HeapDestroyW(Heap* h){
	
	HeapRecDestroyW(h->head);
	h->head=NULL;
}



void HeapifyWords(Link* head,Heap* heap,int totalFiles) //Eisagwgh twn leksewn ston swro
{
	int i;
	Details* details;
	WordStats* wstats; 
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    HeapifyWords(&((*head)->l),heap,totalFiles);
    HeapifyWords(&((*head)->r),heap,totalFiles);
    

    if((*head)->rbitem->obj != NULL){
    	wstats=(WordStats*)((*head)->rbitem->obj);
    	
		details = (Details*)malloc(sizeof(Details));
		details->stats =(void*) wstats;
		details->count = 0.0;
		
		for(i = 0; i < numBuckets; i++ )
			SumTFIDF( wstats->files.buckets[i] , details ); //Euresh tou athroismatos olwn twn TF-IDF timwn
		details->count /= totalFiles;  //Euresh tou mesou TF-IDF ws krithrio eisagwghs ston swro
		HeapInsert( heap , details );
	}
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}




/*##################                  END OF HEAP                             ##########################*/


/*##################                  START OF QUEUE                          ##########################*/

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

void QueueConcat(Queue* q1 , Queue* q2,Clique* cliq){ //Enwsh ourwn
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

void QueueDelete(Queue* queue,char flag){ //Diagrafh ouras

	struct QueueNode* curr = queue->head,*temp;

	while(curr != NULL){
		temp = curr;
		curr = curr->next;
		if(flag == 'b')
			free(temp->data);
		free(temp);
	}

	queue->head = NULL;
	queue->tail = NULL;
	queue->count = 0;

}

/*##################                  END OF QUEUE            ##########################*/


/*##################     START OF STACK               ##########################*/


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
	else if(c == '[' || c == '{')							// Diaforetika kanoume push to stoixeio
		push(stack,c);
	
}

int StackEmpty(Stack * stack){
	return stack->count == 0;
}



/*##################              END OF STACK                         ##########################*/






/*##################              START OF RED-BLACK                        ##########################*/




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


Link NEW(char* id,void* obj, Link l, Link r, int color,int* flag){ 
	Link x =(Link)malloc(sizeof(struct RBnode));
  	x->l = l; x->r = r; 
	x->color=color;
	if( id != NULL && obj != NULL){
		x->rbitem = (RBItem*)malloc(sizeof(RBItem));
    	x->rbitem->obj = obj;
		x->rbitem->id = id;
		x->rbitem->valid = 1;
		*flag = 1; // To stoixeio bhke gia prwth fora
	}
    return x;
}

 
void RBinit() //Arxikopoihsh tou kenou komvou
	{ z = NEW( NULL ,NULL, NULL, NULL, BLACK, NULL); }
  
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
			if(h!=head){//Kanoume recoloring ektos ths rizas
				h->color=RED;
			}
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

Link insertR(Link h, char* id,void* obj ,Link head, int* flag)
{   
	char* v = id;
    RBItem* t = h->rbitem;
   
    if (h == z){ //Base case
	    if(h != head)
	    	return NEW(id,obj, z, z, RED, flag);  //Kathe neos komvos prepei na einai kokkinos
	    else 
			return NEW(id,obj, z , z , BLACK, flag); // Ektos apo thn riza pou einai maurh
	}
    if( strcmp(v,t->id) < 0 ){ //Psaxnoume thn thesh gia na valoume ton neo komvo
        h->l = insertR(h->l, id,obj,head,flag);
        if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo aristera (afou to paidi exei bei aristera)
	    	h=MakeRBTree(h,head);
	}
    else if( strcmp(t->id,v) < 0 ) {
		h->r = insertR(h->r, id,obj,head,flag);
		if(h->color==BLACK) //Kathe fora pou vriskoume mauro komvo pou exei toulaxiston ena "eggoni" apo deksia (afou to paidi exei bei deksia)
			h=MakeRBTree(h,head);
	}
	else if( t->obj == NULL) //An den yparxei timh
		t->obj = obj;
		
	return h;
  }
  
Link RBTinsertR( Link head , char* id , void* obj, int* flag ){ // Eisagwgh sto Red-Black dentro

	head = insertR( head , id , obj , head, flag );
  	return head; 
}


void* RBTfind(Link h,char* id,char type){
   
    RBItem* t = h->rbitem;
 
    
    if(h == z)								// An den brethei timh
		return NULL;
    // Diasxish tou dentrou gia thn euresh ths timhs
    if( strcmp(id , t->id) < 0 )						
		return RBTfind(h->l, id, type);
	else if ( strcmp(t->id , id) < 0)
		return RBTfind(h->r, id, type);
	else{					// Otan vrethei h timh epistrefetai 
			if(type == 'k') //An exei zhththei to key
				return t->id;
			else if( type == 'v' && t->obj != NULL) //An exei zhththei h timh
				return t->obj;
    }

    return NULL;
}


void RBTdestr(Link* head,void (*del_fun)(void*),char flag)//Katastrofh tou dentrou
{
	
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    RBTdestr(&((*head)->l),del_fun,flag);
    RBTdestr(&((*head)->r),del_fun,flag);
    
    if((*head)->rbitem->id != NULL && (flag == 'b' || flag == 'k') ) //An diagrafetai to key logw flag ('b' = both), ('k' = key)
    	free((*head)->rbitem->id);
    if((*head)->rbitem->obj != NULL && (flag == 'b' || flag == 'v')){ //An diagrafetai h timh logw flag ('b' = both), ('v' = value)
    	if(del_fun != NULL)
    		(*del_fun)((*head)->rbitem->obj);  //Synarthsh diagrafhs
    	else
    		free((*head)->rbitem->obj);  //Aplh diagrafh
    }

       
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}







void RBTmergeHT(Link* head,HashTable* ht)		//Eisagwgh stoixeiwn dentrou se neo hashtable
{
	Pair* pair;
	
    if (*head == z){
		*head = NULL;
		return;
	}
		
    RBTmergeHT(&((*head)->l),ht);
    RBTmergeHT(&((*head)->r),ht);
    

    if((*head)->rbitem->obj != NULL){
		pair = (Pair*)((*head)->rbitem->obj);
		HTinsert(ht,pair->item->id,(void*)pair);
	}
    
    free((*head)->rbitem);
	free(*head);
	*head = NULL;
}






/*##################              END OF RED-BLACK                        ##########################*/




/*##################                  START OF HASH TABLES                             ##########################*/

void HTinit( HashTable* ht ){			// Arxikopoihsh hashtable
	
	int i;
	
	ht->buckets=(Link*)malloc(sizeof(Link)*numBuckets); 
	for( i = 0; i < numBuckets; i++ )					// Kathe hashtable exei ws buckets Red-Black dentra
		RBTinit( &(ht->buckets[i]) );
	ht->count = 0;
	
}

int hashFunction(char* str,int nb){ //Polynomial hash function for strings
	int hash = 0;
	int constant = 33;
	while(*str != '\0'){
		hash = (constant*hash + *str) % nb;
		str++;
	}
	return hash;
}


void HTinsert( HashTable* ht, char* key, void* item ){			//Eisagwgh sto hashtable
	
	int hashnum;
	int flag = 0;
	
	hashnum = hashFunction( key , numBuckets );
	ht->buckets[hashnum] = RBTinsertR( ht->buckets[hashnum] , key , item, &flag);
	if(flag)  //An egine epityxws h eisagwgh
		ht->count++;
	
}

void HTmerge( HashTable* ht1 , HashTable* ht2){  //Enwsh dyo hashtables
	int i;
	
	for( i = 0; i < numBuckets; i++)
		RBTmergeHT(&(ht2->buckets[i]), ht1);
	
	free(ht2->buckets);
	ht2->buckets = NULL;
	ht2->count = 0;
		
}



void* HTfind(HashTable* ht,char* id, char type){ //Anazhthsh sto hashtable
	
	int hashnum = hashFunction(id,numBuckets);
	
	return RBTfind(ht->buckets[hashnum],id,type);
	
}

void HTdestr(HashTable* ht,void (*del_fun)(void*),char flag){  //Diagrafh tou hashtable me sygekrimenh synarthsh diagrafhs
	int i;
		
	for( i = 0; i < numBuckets; i++)
		RBTdestr(&(ht->buckets[i]),del_fun, flag);
		
	free(ht->buckets);
	ht->buckets = NULL;
	ht->count = 0;
	
}




/*##################                  END OF HASH TABLES                             ##########################*/




/*##################                  START OF HELPER FUNCTIONS                             ##########################*/




void CliqueConcat(Pair* pair1 , Pair* pair2, int choice){  //Enwsh klikwn
	Clique* temp;
	
	
	if(choice == 1){	// Dhladh an tairiazoun enwsh twn related kai unrelated
		temp = pair2->cliq;
		HTmerge(&(pair1->cliq->unrelated),&(pair2->cliq->unrelated));
		QueueConcat(pair1->cliq->related,pair2->cliq->related,pair1->cliq);
		free(temp->id);
		free(temp);
		}
	else{				// Dhladh an den tairiazoun eisagwgh ths mias stis unrelated ths allhs
		HTinsert(&(pair1->cliq->unrelated),pair2->item->id,(void*)pair2);
		HTinsert(&(pair2->cliq->unrelated),pair1->item->id,(void*)pair1);
	}
	
}


void MakeCliqueHT(Link pairTree, HashTable* ht){  //Dhmiourgia tou hashtable twn klikwn apo to hashtable twn Pairs
	
	RBItem* t = pairTree->rbitem;
 			
    Pair* pair;	

	
	if(pairTree == z)			// Base-case
		return;
		
	MakeCliqueHT(pairTree->l,ht);	// Anadromika phgainoume aristera
	
	if(t->obj != NULL){	
		pair  = (Pair*)(t->obj);
		HTinsert(ht,pair->cliq->id,(void*)(pair->cliq));
	}

	MakeCliqueHT(pairTree->r,ht);	// Anadromika phgainoume deksia

}


void MakeCliqueUnrelated(Link* oldTree, HashTable* ht){ //Dhmiourgia tou hashtable twn unrelated klikwn apo ta unrelated Pairs
	
	RBItem* t = (*oldTree)->rbitem;
 			
    Pair* pair;	

	
	if(*oldTree == z)			// Base-case
		return;
		
	MakeCliqueUnrelated(&((*oldTree)->l),ht);	// Anadromika phgainoume aristera
	MakeCliqueUnrelated(&((*oldTree)->r),ht);	// Anadromika phgainoume deksia

	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
		pair  = (Pair*)(t->obj);
		HTinsert(ht,pair->cliq->id,(void*)(pair->cliq));
	}


	free((*oldTree)->rbitem);
	free(*oldTree);
	*oldTree = NULL;
	

}



void ChangeUnrelated(Link h){
	
	RBItem* t = h->rbitem;
    int i;		
    Clique* cliq;	
	HashTable* unrelated;
	
	
	if(h == z)			// Base-case
		return;
	
	ChangeUnrelated(h->l);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
	
		unrelated =(HashTable*)malloc(sizeof(HashTable)); //Dhmiourgia vohthitikou hashtable
		HTinit(unrelated);
		
		cliq  = (Clique*)(t->obj);
		
		for( i = 0; i < numBuckets; i++)
			MakeCliqueUnrelated(&(cliq->unrelated.buckets[i]),unrelated);
		
		for( i = 0; i < numBuckets; i++)	 //Antigrafh tou vohthitikou hashtable
			cliq->unrelated.buckets[i] = unrelated->buckets[i];
		
		cliq->unrelated.count = unrelated->count;
		
		free(unrelated->buckets);
		free(unrelated);
	
	}
	
	
	ChangeUnrelated(h->r);	// Anadromika phgainoume deksia
	
}






void RemoveUnrelated(Link h , char* id){
	
	
	RBItem* t = h->rbitem;

    
    if(h == z)								// An den brethei timi 
		return;
    
    if( strcmp(id , t->id) < 0 )						// Diasxish tou dentrou gia na brethei h timi
		return RemoveUnrelated(h->l, id);
	else if (strcmp(t->id , id ) < 0)
		return RemoveUnrelated(h->r, id);
	else{									// Otan vrethei h timh afaireitai
			if(t->obj != NULL)
				t->valid = 0;
	}
	
}






void VisitUnrelated(Link h, Clique* cliq,FILE* output,char* buff,Queue* train,Queue* test,Queue* valid, HashTable* files,HashTable* comb){
	
	RBItem* t = h->rbitem;
	int hashnum;
    struct QueueNode* ptr,*unrelptr;		
    Clique* unrelc;
	Pair* pair, *unrelp;	
	Record* record;
	char* tmp;

	if(h == z)			// Base-case
		return;
	
	VisitUnrelated(h->l,cliq,output,buff, train, test, valid, files, comb);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL && t->valid){									// Den yparxoun diplotypa
	
		unrelc  = (Clique*)(t->obj);
		
		for( ptr = cliq->related->head ; ptr != NULL ; ptr = ptr->next ){
			pair = (Pair*)(ptr->data);
			for( unrelptr = unrelc->related->head ; unrelptr != NULL ; unrelptr = unrelptr->next){
				unrelp = (Pair*)(unrelptr->data);
				
				if(output != NULL){
					sprintf(buff,"%s , %s \n", pair->item->id , unrelp->item->id );
					fwrite(buff,sizeof(char),strlen(buff),output);
				}
													
				if(test != NULL && valid != NULL){
					record = (Record*)malloc(sizeof(Record)); //Dhmiourgia record
					record->item1 = (FileStats*) HTfind(files,pair->item->id,'v');
					record->item2 = (FileStats*) HTfind(files,unrelp->item->id,'v');
					record->value = 0;	// 0 logw unrelated
					DatasetSplit(train, test, valid, record );
				}
				else if(comb != NULL){
					tmp = (char*)malloc(strlen(pair->item->id) + strlen(unrelp->item->id) + 1);
					strcpy(tmp , pair->item->id);
					strcat(tmp , unrelp->item->id);
					if( HTfind(comb, tmp, 'k') == NULL){
						strcpy(tmp , unrelp->item->id);
						strcat(tmp , pair->item->id);
						if(HTfind(comb, tmp, 'k') == NULL){ //Den yparxei sto training set
							record = (Record*)malloc(sizeof(Record)); //Dhmiourgia record
							record->item1 = (FileStats*) HTfind(files,pair->item->id,'v');
							record->item2 = (FileStats*) HTfind(files,unrelp->item->id,'v');
							record->value = 0;	// 0 logw unrelated
							QueueInsert(train,(void**)&record);
						}
					}

					free(tmp);
				}
			}	
		}
		
		hashnum = hashFunction(cliq->id,numBuckets);
		RemoveUnrelated(unrelc->unrelated.buckets[hashnum], cliq->id);
	
	}
	
	
	VisitUnrelated(h->r,cliq,output,buff, train, test, valid, files, comb);	// Anadromika phgainoume deksia
	
}





void printUnrelated(Link h,FILE* output,char* buff, Queue* train, Queue* test, Queue* valid, HashTable* files,HashTable* comb){
	
	RBItem* t = h->rbitem;	
	int i;	
    Clique* cliq;	
	
	if(h == z)			// Base-case
		return;
	
	printUnrelated(h->l,output,buff, train, test, valid, files,comb);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		cliq  = (Clique*)(t->obj);
		for( i = 0; i < numBuckets; i++)
			VisitUnrelated(cliq->unrelated.buckets[i],cliq,output,buff, train, test, valid, files,comb);
		
	}
	
	
	printUnrelated(h->r,output,buff, train, test, valid, files,comb);	// Anadromika phgainoume deksia
	
}



void printRelated(Link h,FILE* output,char* buff, Queue* train,Queue* test,Queue* valid,HashTable* files,HashTable* comb){			
	
	RBItem* t = h->rbitem;
    struct QueueNode *curr;
 	Record* record;
 	char* tmp;
		
    Pair* pair;	
	Pair* rel_pair;	
	
	if(h == z)			// base-case
		return;
		
	printRelated(h->l,output,buff, train, test, valid, files, comb);	// Anadromika phgainoume aristera
	
	
	pair  = (Pair*)(t->obj);
	curr = pair->cliq->related->head;
	while( curr != NULL ){								// Diasxizoume thn related 
		rel_pair  = (Pair*)(curr->data);															// Related_pairs	
		if( !strcmp( pair->item->id , rel_pair->item->id ) )								// An einai to idio item
			pair->printed++;
		else if(!rel_pair->printed){																						// An den einai ta ektypwnoume
			
			if(output != NULL){
				sprintf(buff,"%s , %s \n", pair->item->id , rel_pair->item->id );			
				fwrite(buff,sizeof(char),strlen(buff),output);
			}
							
			if(test != NULL && valid != NULL){
				record = (Record*)malloc(sizeof(Record)); //Dhmiourgia record
				record->item1 = (FileStats*) HTfind(files,pair->item->id,'v');
				record->item2 = (FileStats*) HTfind(files,rel_pair->item->id,'v');
				record->value = 1;										// 1 logw related
				DatasetSplit(train, test, valid, record );
			}
			else if(comb != NULL){
				tmp = (char*)malloc(strlen(pair->item->id) + strlen(rel_pair->item->id) + 1);
				strcpy(tmp , pair->item->id);
				strcat(tmp , rel_pair->item->id);
				if( HTfind(comb, tmp, 'k') == NULL){
					strcpy(tmp , rel_pair->item->id);
					strcat(tmp , pair->item->id);
					if(HTfind(comb, tmp, 'k') == NULL){ //Den yparxei sto training set
						record = (Record*)malloc(sizeof(Record)); //Dhmiourgia record
						record->item1 = (FileStats*) HTfind(files,pair->item->id,'v');
						record->item2 = (FileStats*) HTfind(files,rel_pair->item->id,'v');
						record->value = 1;										// 1 logw related
						QueueInsert(train,(void**)&record);
					}
				}

				free(tmp);
			}
		}

		curr = curr->next;
	}

	
	
	printRelated(h->r,output,buff, train, test, valid, files,comb);	// Anadromika phgainoume deksia
	
	
	
	
}




void UpdateTFIDF( Link h,  int totalFiles , int fileWords){

	RBItem* t = h->rbitem;	
	double idf;	
    ModelStats* mstats;	

	
	if(h == z)			// Base-case
		return;
	
	UpdateTFIDF(h->l , totalFiles  , fileWords);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		mstats  = (ModelStats*)(t->obj);
		idf = log10((double) totalFiles) - log10((double)mstats->wstats->files.count);

		mstats->tfidf_val /= fileWords; //TF
		mstats->tfidf_val *= idf; //TF-IDF
		//printf("totalFiles:%d, fileWords:%d, nt:%d\n   ",totalFiles,fileWords,mstats->wstats->files.count);
		//printf("%s BOW:%d ,TF-IDF:%f\n  ",mstats->wstats->word,mstats->bow_val,mstats->tfidf_val);
		
	}
	
	
	UpdateTFIDF(h->r, totalFiles  , fileWords);	// Anadromika phgainoume deksia



}



void CreateTFIDF( Link h, int totalFiles){
	
	RBItem* t = h->rbitem;	
	int i;	
    FileStats* fstats;	
	
	if(h == z)			// Base-case
		return;
	
	CreateTFIDF(h->l , totalFiles);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		fstats  = (FileStats*)(t->obj);
		//printf("--------%s-------\n",fstats->item->id);
		for( i = 0; i < numBuckets; i++)
			UpdateTFIDF(fstats->words.buckets[i] , totalFiles, fstats->numOfWords);
		
	}
	
	
	CreateTFIDF(h->r, totalFiles);	// Anadromika phgainoume deksia
	
}

void SumTFIDF( Link h, Details* details){
	
	RBItem* t = h->rbitem;		
    FileStats* fstats;
	ModelStats* mstats;
	WordStats* wstats; 	
	
	if(h == z)			// Base-case
		return;
	
	SumTFIDF(h->l , details);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
		wstats = (WordStats*)(details->stats);
		fstats  = (FileStats*)(t->obj);
		mstats= (ModelStats*)HTfind(&(fstats->words) , wstats->word, 'v' );
		details->count += mstats->tfidf_val;
		
	}
	
	
	SumTFIDF(h->r, details);	// Anadromika phgainoume deksia
	
}



void InsertMStats(Link* oldTree, HashTable* words,  HashTable* newWords){
	
	RBItem* t = (*oldTree)->rbitem;
 			
    ModelStats* mstats;	

	
	if(*oldTree == z)			// Base-case
		return;
		
	InsertMStats(&((*oldTree)->l),words,newWords);	// Anadromika phgainoume aristera
	InsertMStats(&((*oldTree)->r),words,newWords);	// Anadromika phgainoume deksia

	
	if(t->obj != NULL){									// Den yparxoun diplotypa
	
		mstats  = (ModelStats*)(t->obj);
		if( HTfind(words,mstats->wstats->word,'k')) //An vrisketai stis shmantikoteres lekseis
			HTinsert(newWords,mstats->wstats->word,(void*)mstats);
		else
			free(mstats);

	}


	free((*oldTree)->rbitem);
	free(*oldTree);
	*oldTree = NULL;
	

}

void AdjustMStats(Link h,HashTable* words){
	HashTable* newWords;

	RBItem* t = h->rbitem;	
	int i;	
    FileStats* fstats;	
	
	if(h == z)			// Base-case
		return;
	
	AdjustMStats(h->l , words);	// Anadromika phgainoume aristera
	
	
	if(t->obj != NULL){									// Den yparxoun diplotypa
									
		fstats  = (FileStats*)(t->obj);
		newWords = (HashTable*)malloc(sizeof(HashTable)); //Dhmiourgia vohthitikou hashtable
		HTinit(newWords);
		
		for( i = 0; i < numBuckets; i++)
			InsertMStats(&(fstats->words.buckets[i])  ,words , newWords);
		
		for( i = 0; i < numBuckets; i++)	 //Antigrafh tou vohthitikou hashtable
			 fstats->words.buckets[i] = newWords->buckets[i];
		
		fstats->words.count = newWords->count;

		free(newWords->buckets);
		free(newWords);	
	}
	
	
	AdjustMStats(h->r, words);	// Anadromika phgainoume deksia

}



void RestorePairs(Link pairTree,int* id,char* buff){  //Epanafora Pairs
	
	RBItem* t = pairTree->rbitem;
	char* tmp;
 			
    Pair* pair;	

	
	if(pairTree == z)			// Base-case
		return;
		
	RestorePairs(pairTree->l,id,buff);	// Anadromika phgainoume aristera
	
	if(t->obj != NULL){	
		pair  = (Pair*)(t->obj);


		pair->cliq = (Clique*) malloc(sizeof(Clique));
		sprintf(buff,"%d",*id);
		tmp = (char*)malloc(strlen(buff) + 1 );
		strcpy(tmp,buff);
		pair->cliq->id = tmp;
		(*id)++;
		
		pair->printed = 0;

		pair->cliq->related = (Queue*)malloc(sizeof(Queue));
		QueueInit(pair->cliq->related);
		QueueInsert(pair->cliq->related, (void**)&pair); // Sthn arxh h related oura exei mono to idio to pair 
		HTinit(&(pair->cliq->unrelated));
		
	
	}

	RestorePairs(pairTree->r,id,buff);	// Anadromika phgainoume deksia

}




/*##################                  END OF HELPER FUNCTIONS                             ##########################*/


/*##################                  START OF THREADS                             ##########################*/

void t_perror_exit(char* s,int err){
	fprintf(stderr, "%s: %s\n", s, strerror(err));
	exit(1);
}

void initialize_schelduler(JobScheduler* schelduler,int num_threads,int buffer_size,void* (*thread_fun)(void*),int* times){ //Arxikpoihsh schelduler
	
	int error,i;
	
	pthread_mutex_init(&(schelduler->mux), NULL);
	pthread_mutex_init(&(schelduler->struct_mux), NULL);
	pthread_cond_init(&(schelduler->cond_nonempty), NULL); 
	pthread_cond_init(&(schelduler->cond_nonfull), NULL);
	pthread_cond_init(&(schelduler->cond_finished), NULL);


	//Arxikopoihsh buffer
	schelduler->buffer_size = buffer_size;
	schelduler->circular_buff =(CircularBuffer*)malloc(sizeof(CircularBuffer));
	schelduler->circular_buff->items=(BuffItem*)malloc(buffer_size*sizeof(BuffItem));
	schelduler->circular_buff->start=0;
	schelduler->circular_buff->end=-1;
	schelduler->circular_buff->count=0;
	
	//Arxikopoihsh twn threads
	schelduler->num_threads = num_threads;
	schelduler->tids=(pthread_t*)malloc(num_threads*sizeof(pthread_t));

	for(i = 0 ; i < num_threads ; i++)
		if((error = pthread_create(&(schelduler->tids[i]), NULL, thread_fun, (void*)times)))
			t_perror_exit("Failed to create thread", error);
			
			
	
}


void add_job(JobScheduler* schelduler,struct QueueNode* ptr){//Eisagwgh ston kykliko buffer
	
	pthread_mutex_lock(&(schelduler->mux));
	while(schelduler->circular_buff->count == schelduler->buffer_size) //Oso einai gematos o buffer
		pthread_cond_wait(&(schelduler->cond_nonfull), &(schelduler->mux));
		
	schelduler->circular_buff->end=(schelduler->circular_buff->end + 1) % schelduler->buffer_size;
	schelduler->circular_buff->items[schelduler->circular_buff->end].ptr=ptr;
	schelduler->circular_buff->count++;
	
	pthread_cond_signal(&(schelduler->cond_nonempty)); //Epeidh prostethike kati
	pthread_mutex_unlock(&(schelduler->mux));
}

void get_job(JobScheduler* schelduler,struct QueueNode** ptr){//Diagrafh apo ton kykliko buffer

	pthread_mutex_lock(&(schelduler->mux));
	while(schelduler->circular_buff->count == 0) //Oso einai adeios o buffer
		pthread_cond_wait(&(schelduler->cond_nonempty), &(schelduler->mux));
		
	*ptr=schelduler->circular_buff->items[schelduler->circular_buff->start].ptr;
	schelduler->circular_buff->start=(schelduler->circular_buff->start + 1) % schelduler->buffer_size;
	schelduler->circular_buff->count--;
	
	pthread_cond_signal(&(schelduler->cond_nonfull));//Epeidh afairethike kati
	pthread_mutex_unlock(&(schelduler->mux));
}


void destroy_schelduler(JobScheduler* schelduler){
	
	int error;
	
	free(schelduler->circular_buff->items);
	free(schelduler->circular_buff);
	free(schelduler->tids);

	
	

	if((error = pthread_mutex_destroy(&(schelduler->mux))))
		t_perror_exit("Failed to destroy mutex", error);
	if((error = pthread_mutex_destroy(&(schelduler->struct_mux))))
		t_perror_exit("Failed to destroy mutex", error);

	if((error = pthread_cond_destroy(&(schelduler->cond_nonempty))))
		t_perror_exit("Failed to destroy condition variable", error);
	if((error = pthread_cond_destroy(&(schelduler->cond_nonfull))))
		t_perror_exit("Failed to destroy condition variable", error);
	if((error = pthread_cond_destroy(&(schelduler->cond_finished))))
		t_perror_exit("Failed to destroy condition variable", error);


	
}

/*##################                  END OF THREADS                             ##########################*/
