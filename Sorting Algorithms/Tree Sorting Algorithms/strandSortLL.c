#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 7

typedef struct node{
	int val;
	struct node *link;
}node, *list;

void initializeList(list *LL, int *arr);
void populateA(list *A, list *values);
void mergeList(list *A, list *B, list *C);
// take the first element populate the list with numbers greater than it
// merge the list

int main(){
	// 10, 8, 2, 9, 1, 4, 12
	list values, trav, A, B, C;
	int arr[] = {10, 8, 2, 9, 1, 4, 12};
	int ctr;
	
	values = A = B = C = NULL;
	initializeList(&values, arr);
	
	while(values!=NULL){
		populateA(&A, &values);
		mergeList(&A, &B, &C);
		if(values!=NULL){
			B = C;
			C = NULL;
		}
	}
	
	
	// Display
	printf("\nValues: ");
	for(trav=values; trav!=NULL; trav=trav->link){
		printf("%d, ", trav->val);
	}
	
	printf("\nA: ");
	for(trav=A; trav!=NULL; trav=trav->link){
		printf("%d, ", trav->val);
	}
	
	printf("\nB:");
	for(trav=B; trav!=NULL; trav=trav->link){
		printf("%d, ", trav->val);
	}
	
	printf("\nC:");
	for(trav=C; trav!=NULL; trav=trav->link){
		printf("%d, ", trav->val);
	}
	
	return 0;
}
// affected by equal to
void mergeList(list *A, list *B, list *C)
{
	list *trav;
	
	if(*B!=NULL){
		for(trav=C; *A!=NULL&&*B!=NULL;){
			if((*A)->val<(*B)->val){
				*trav = *A;
				*A = (*trav)->link;
			} else {
				*trav = *B;
				*B = (*trav)->link;
			}
			(*trav)->link = NULL;
			trav = &(*trav)->link;
		}
		if(*A==NULL){
			*trav=*B;
			*B=NULL;
		} else {
			*trav=*A;
			*A=NULL;
		}
	} else {
		*C = *A;
		*A = NULL;
	}
}

void initializeList(list *LL, int *arr)
{
	list *trav = LL;
	int ctr;
	
	for(ctr=0; ctr<MAX_SIZE; ctr++, trav=&(*trav)->link){
		*trav = (list)malloc(sizeof(node));
		(*trav)->val = arr[ctr];
		(*trav)->link = NULL;
	}
}

void populateA(list *A, list *values)
{
	list *trav, *last;
	
	*A = *values;
	*values = (*A)->link;
	(*A)->link = NULL;
	for(trav=values, last=A; *trav!=NULL&&*values!=NULL;){
		if((*trav)->val > (*last)->val){
			last = &(*last)->link;
			*last = *trav;
			*trav = (*trav)->link;
			(*last)->link = NULL;
		} else {
			trav = &(*trav)->link;
		}
	}
}
