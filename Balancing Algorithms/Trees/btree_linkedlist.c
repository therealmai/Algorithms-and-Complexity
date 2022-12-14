#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //to get min nodes for ceil()

//B-Tree settings
#define MAXKEYS 3
#define ORDER MAXKEYS+1
#define MIN (int)(ceil((ORDER)/2))-1

//Sentinel values
#define NL -1

typedef struct node{
	int count;					//number of keys used
	int elem[MAXKEYS];			//elements in the node
	struct node *link[ORDER];	//child pointers
}page, *BTree;

typedef struct{
	BTree node;
	int index;
}location;

typedef enum{
	TRUE,FALSE
}boolean;

typedef enum{
	LEFT = -1,RIGHT = 1
}sideType;

typedef struct{
	boolean isSuccess;	 //TRUE, FALSE
	boolean isPromote;   //TRUE, FALSE
	BTree newRChild;     //if isPromote == TRUE
	int newKey;          //if isPromote == TRUE
}insertStatus;

typedef struct{
	boolean isDeleted;
	int itemRemoved;
	int nodeCount;	//needed in case root needs to be removed
}deleteStatus;

typedef struct{
	int LSCount;  //-1 is does not exist
	int RSCount;  //-1 if does not exist
	BTree LS, RS;
}siblingStatus;

void initialize(BTree *B);

void display(BTree B, int node);	//mode: 1-inorder, 2-preorder
void displayInOrder(BTree B);		//recursive
void displayPreOrder(BTree B);		//recursive

void search(BTree B, int elem);				//initial call
location searchRecur(BTree B, int elem);	//recursive

void insertElem(BTree *B, int elem);					//initial call
insertStatus insertRecur(BTree *B, int elem);			//recursive
insertStatus split(BTree *B, int elem, BTree child);	//occurs if overflow
void createRoot(BTree *B, int newKey, BTree child);		//occurs if new root needed

void populate(BTree *B);

void deleteElem(BTree *B, int elem);
deleteStatus deleteRecur(BTree *B, int elem);	//recursive

int findMin(BTree B);
siblingStatus checkSiblings(BTree B, int ptrNdx);
void redistribute(BTree dest,BTree src,BTree parent,int parentNdx,sideType side);
void concatenate(BTree dest,BTree src,BTree parent,int parentNdx,sideType side);
int main(){
	BTree B;
	
	//initialize
	initialize(&B);
	printf("\n\n(1) After initialization:");
	display(B,1);
	
	//insert 1 element
	insertElem(&B,40);
	printf("\n\n(2) After inserting 40 (creating the first node):");
	display(B,1);
	
	//insert 2 elements
	insertElem(&B,10);
	insertElem(&B,20);
	printf("\n\n(3) After inserting 10,20 (arranging elements within a node):");
	display(B,1);
	
	//test the shifting and promotion
	insertElem(&B,50);
	printf("\n\n(4) After inserting 50 (with shifting and promotion):");
	display(B,2);
	
	//proceed with remaining elements
	populate(&B);
	printf("\n\n(5) After inserting 60,70,80,90,100,110,30:");
	display(B,1);
	display(B,2);
	
	//multiple promotions
	insertElem(&B,35);
	printf("\n\n(6) After inserting 35 (multiple promotions):");
	display(B,2);
	
	//final insertions
	insertElem(&B,5);
	insertElem(&B,15);
	printf("\n\n(6) After inserting 5,15:");
	display(B,1);
	display(B,2);
	
	//delete 50
	deleteElem(&B,50);
	printf("\n\n(7) After deleting 50 (no adjustments):");
	display(B,2);
	
	//delete 50
	deleteElem(&B,70);
	printf("\n\n(8) After deleting 70 (swap with succesor):");
	display(B,2);
	
	//delete 20
	deleteElem(&B,20);
	printf("\n\n(9) After deleting 20 (redistribution L to R):");
	display(B,2);
	
	//delete 60
	deleteElem(&B,35);
	printf("\n\n(10) After deleting 35 (concatenation R to L):");
	display(B,2);
	
	//delete 15
	deleteElem(&B,15);
	printf("\n\n(11) After deleting 15 (redistrubition R to L):");
	display(B,2);
	
	//delete 5
	deleteElem(&B,5);
	printf("\n\n(12) After deleting 5 (concatenation R to L):");
	display(B,1);
	display(B,2);
	
	return 0;
}

void initialize(BTree *B){
	*B = NULL;
}

void display(BTree B, int mode){
	if(B==NULL){
		printf("\nGiven B-Tree is empty");
	}else{
		switch(mode){
			case 1:
				printf("\n\n===================================================");
				printf("\nTraversing the tree in inorder...");
				printf("\n%-15s %-6s %-6s","Page Address","Index","Element");
				displayInOrder(B);
				printf("\n===================================================");
				break;
			case 2:
				printf("\n\n===================================================");
				printf("\nTraversing the tree in preorder...");
				printf("\n%-15s %-6s %-6s","Page Address","Index","Element");
				displayPreOrder(B);
				printf("\n===================================================");
				break;
		}
	}
}

void displayInOrder(BTree B){	//left, root, right
	int x;
	if(B!=NULL){
		for(x=0;x<=B->count;x++){
			displayInOrder(B->link[x]);
			if(x<B->count){
				printf("\n%-15x %-6d %-6d %-6d",B,x,B->elem[x],B->count);
			}
		}
	}
}

void displayPreOrder(BTree B){	//root, left, right
	int x;
	if(B!=NULL){
		for(x=0;x<B->count;x++){
			printf("\n%-15x %-6d %-6d %-6d",B,x,B->elem[x],B->count);
		}
		printf("\n");
		for(x=0;x<=B->count;x++){
			displayPreOrder(B->link[x]);
		}
	}
}

void search(BTree B, int elem){
	location loc;
	
	printf("\n\nSearching for element: %d",elem);
	loc = searchRecur(B,elem);
	if(loc.node == NULL){
		printf("\nElement %d not found.", elem);
	} else {
		printf("\nElement %d found at address %x, index %d.",loc.node,loc.index);
	}
}

location searchRecur(BTree B, int elem){
	location ret = {NULL, NL};
	int x;
	if(B!=NULL){
		for(x=0;x<B->count && B->elem[x] < elem;x++){}
		if(x<B->count && B->elem[x] == elem){ 						//element found
			ret.node = B;
			ret.index = x;
		} else { 													//RECURSIVE search
			ret = searchRecur(B->link[x],elem);
		}
	} 																//else NULL reached, element not found
	return ret;
}


void insertElem(BTree *B, int elem){
	insertStatus stat;
	printf("\n\nInserting element: %d",elem);
	stat = insertRecur(B,elem);
	if(stat.isPromote==TRUE){
		createRoot(B, stat.newKey, stat.newRChild);
		printf("\nInsertion successful, and created new root (Address: %x).",*B);
	} else if(stat.isSuccess == FALSE) {
		printf("\nInsertion failed - element already exists.");
	} else {
		printf("\nInsertion successful, within existing tree body");
	}
 	
}	
insertStatus insertRecur(BTree *B, int elem){
	insertStatus ret = {FALSE,FALSE,NULL,-1};
	
	int x;
	if(*B==NULL){												//leaf is reached, go back 1 level
		ret.isPromote = TRUE;
		ret.newKey = elem;
		ret.newRChild = ret.newRChild;
	} else { 
		for(x=0;x<(*B)->count && (*B)->elem[x] < elem;x++){}	//search in page
		if(x==(*B)->count || (*B)->elem[x] != elem){			//check if element does not exist
			ret = insertRecur(&(*B)->link[x],elem);				//RECURSIVE insert call
			if(ret.isPromote == TRUE){							//check if there are any values promoted
				if((*B)->count < MAXKEYS){						//check if there is free space
					for(x=(*B)->count; x>0 && (*B)->elem[x-1] > elem; x--){
						(*B)->elem[x] = (*B)->elem[x-1];		//shift existing elements and pointers
						(*B)->link[x+1] = (*B)->link[x];
					}
					(*B)->count++;								//insert the new element and pointer
					(*B)->elem[x] = ret.newKey;
					(*B)->link[x+1] = ret.newRChild;
					ret.isPromote = FALSE;
					ret.isSuccess = TRUE;	
				} else {
					ret = split(B,ret.newKey,ret.newRChild);	//perform splitting
				}
			} 													//else no promotion - either insertion done or failed
		} 														//else no insertion - element found
	}
	return ret;
}		

insertStatus split(BTree *B, int elem, BTree child){
	insertStatus ret = {FALSE,FALSE,NULL,-1};
	
	int tempKeys[MAXKEYS+1];									//create working page
	BTree tempChild[MAXKEYS+2];
	int x, mid;
	
	BTree temp = (BTree)calloc(1,sizeof(page));					//allocate new page
	if(temp != NULL){
		memcpy(tempKeys,(*B)->elem,(*B)->count*sizeof(int));	//copy everything from old page to working page
		memcpy(tempChild,(*B)->link,((*B)->count+1)*sizeof(BTree));

		for(x=(*B)->count; x>0 && (*B)->elem[x-1] > elem; x--){
			tempKeys[x] = tempKeys[x-1];						//shift existing elements and pointers
			tempChild[x+1] = tempChild[x];
		}
		tempKeys[x] = elem;										//insert the new element and pointer
		tempChild[x+1] = child;
		
		printf("\nOverflow detected - Temporary page: ");
		for(x=0;x<4;x++){
			printf("%d ",tempKeys[x]);
		}
		
		mid = MAXKEYS/2;										//move back first half at original
		memcpy((*B)->elem,tempKeys,(mid+1)*sizeof(int));
		memcpy((*B)->link,tempChild,(mid+2)*sizeof(BTree));
		(*B)->count = mid+1;
		
		ret.isPromote = TRUE;									//promote mid+1 and its child
		ret.newKey = tempKeys[mid+1];
		ret.newRChild = temp;		
		
		memcpy(temp->elem,tempKeys+mid+2,(MAXKEYS-mid-1)*sizeof(int));	//place rest of elements at new page
		memcpy(temp->link,tempChild+mid+2,(MAXKEYS-mid)*sizeof(BTree));
		temp->count = MAXKEYS-mid-1;
	}	
	
	return ret;
}

void createRoot(BTree *B, int elem, BTree child){
	BTree temp = (BTree)calloc(1,sizeof(page));
	temp->count++;
	temp->elem[0] = elem;
	temp->link[0] = *B;
	temp->link[1] = child;
	*B = temp;
}	

void populate(BTree *B){
	int arr[] = {60,70,80,90,100,110,30};	//list of elements
	int size = sizeof(arr)/sizeof(int);
	int x;
	
	for(x=0;x<size;x++){
		insertElem(B,arr[x]);	//insert call
	}
}


void deleteElem(BTree *B, int elem){
	deleteStatus stat;
	printf("\n\nDeleting element: %d",elem);
	stat = deleteRecur(B,elem);
	if(stat.isDeleted== FALSE){
		printf("\nDeletion failed - element does not exist.");
	} else if(stat.nodeCount==0) {
		//update root
		printf("\nDeletion successful, tree height decreased (New root address: %x).",*B);
	} else {
		printf("\nDeletion successful.");
	}
}

deleteStatus deleteRecur(BTree *B, int elem){
	deleteStatus ret = {FALSE,-1,-1};
	siblingStatus sib;
	int x, y, min, src, ndx;
	sideType side;
	if(*B!=NULL){
		for(x=0;x<(*B)->count && (*B)->elem[x] < elem;x++){}
		if(x<(*B)->count && (*B)->elem[x] == elem){ 							//element found
			ret.isDeleted = TRUE;
			for(y=0;y<ORDER && (*B)->link[y] == NULL; y++){}			
			if(y==ORDER){														//is leaf
				ret.itemRemoved = elem;
				ret.nodeCount = --(*B)->count;									
				for(y=x; y<(*B)->count; y++){
					(*B)->elem[y] = (*B)->elem[y+1];							//shift existing elements and pointers
					(*B)->link[y+1] = (*B)->link[y+2];
				}
				return ret;		
			} else {
				min = findMin((*B)->link[x+1]);
				(*B)->elem[x] = findMin((*B)->link[x+1]);
				ret = deleteRecur(&(*B)->link[x+1],min);
			}
			
		} else { 																//RECURSIVE search
			ret = deleteRecur(&(*B)->link[x],elem);
		}
		
		if(ret.isDeleted == TRUE && ret.nodeCount < MIN){						//not enough keys in manipulated node
			ndx = (ret.itemRemoved < (*B)->elem[x]) ? x : x+1;
			sib = checkSiblings(*B,ndx);										//check siblings
			printf("\nUnderflow detected!");
			printf("\nItem removed: %d",ret.itemRemoved);
			printf("\nNode count: %d",ret.nodeCount);
			printf("\nSiblings: %x %d - %x %d\n",sib.LS,sib.LSCount,sib.RS,sib.RSCount);
			src = (sib.LSCount > sib.RSCount) ? sib.LSCount : sib.RSCount;
			side = (sib.LSCount > sib.RSCount) ? LEFT : RIGHT;
			printf("\nSibling chosen: %s", side==LEFT ? "Left" : "Right");
			if(src >= MIN + 1){													//redistribution
				printf("\nPerforming redistribution:");
				redistribute((*B)->link[ndx],(*B)->link[ndx+side],*B,ndx,side);
			} else {															//concatenation
				printf("\nPerforming concatenation:");							
				concatenate((*B)->link[ndx],(*B)->link[ndx+side],*B,ndx,side);  
			}																	
		}
		ret.nodeCount = (*B)->count;
	} 																			//else NULL reached, element not found
	return ret;
}

int findMin(BTree B){
	int ret;
	if(B->link[0]==NULL){
		ret = B->elem[0];
	} else {
		ret = findMin(B->link[0]);
	}
	return ret;
}

siblingStatus checkSiblings(BTree B, int ptrNdx){
	siblingStatus ret;
	ret.LSCount = (ptrNdx>0) ? B->link[ptrNdx-1]->count : -1;
	ret.RSCount = (ptrNdx<B->count) ? B->link[ptrNdx+1]->count : -1;
	ret.LS = (ptrNdx>0) ? B->link[ptrNdx-1] : NULL;
	ret.RS = (ptrNdx<B->count) ? B->link[ptrNdx+1] : NULL;
	return ret;
}

void redistribute(BTree dest,BTree src,BTree parent,int parentNdx,sideType side){
	int x;													//in this code, only 1 element gets redistributed
	if(side==LEFT){ 										//destination shifts then source transfers
		for(x=dest->count;x>0;x--){
			dest->elem[x] = dest->elem[x-1];	
			dest->link[x+1] = dest->link[x];
		}
		dest->link[x+1] = dest->link[x];
		dest->elem[0] = parent->elem[parentNdx-1];
		dest->link[0] = src->link[src->count];
		parent->elem[parentNdx-1] = src->elem[src->count-1];
	}else{ 													//source transfer then source shifts
		dest->elem[dest->count] = parent->elem[parentNdx];
		dest->link[dest->count+1] = src->link[0];
		parent->elem[parentNdx] = src->elem[0];
		for(x=0;x<src->count-1;x++){
			src->elem[x] = src->elem[x+1];
			src->link[x] = src->link[x+1];
		}
		src->link[x] = src->link[x+1];
	}
	dest->count++;
	src->count--;
}

void concatenate(BTree dest,BTree src,BTree parent,int parentNdx,sideType side){
	int x,y;
	if(side==LEFT){
		for(x=dest->count;x>0;x--){
			dest->elem[x+src->count] = dest->elem[x-1];	
			dest->link[x+1+src->count] = dest->link[x];
		}
		dest->elem[src->count]=parent->elem[parentNdx];
		dest->link[1+src->count]=src->link[src->count];
		for(x=src->count-1;x>=0;x--){
			dest->elem[x]=src->elem[x];
			dest->link[x]=src->link[x];
		}
		
		dest->count += src->count + 1;
		parent->count--;		
		free(parent->link[parentNdx]);
		parent->link[parentNdx] = NULL;
		for(x=parentNdx;x<parent->count;x++){
			parent->elem[x] = parent->elem[x+1];
			parent->link[x] = parent->link[x+1];
		}
		parent->link[x]=parent->link[x+1];
		
		
	}else{
		dest->elem[dest->count] = parent->elem[parentNdx];
		dest->link[dest->count+1] = src->link[0];
		y=dest->count+1;
		for(x=0;x<src->count;x++){
			dest->elem[y] = src->elem[x];
			dest->link[y+1] = src->link[x+1];
		}
		
		dest->count += src->count + 1;
		parent->count--;		
		free(parent->link[parentNdx+1]);
		parent->link[parentNdx+1] = NULL;
		for(x=parentNdx;x<parent->count;x++){
			parent->elem[x] = parent->elem[x+1];
			parent->link[x+1] = parent->link[x+2];
		}
		
	}
}