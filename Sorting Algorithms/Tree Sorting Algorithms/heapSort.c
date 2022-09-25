/*
if root = index 0
parent = child - 1 / 2
left = 2(parent) +1
right = 2(parent) + 2
___________

if root = index 1
parent = child  / 2
left = 2(parent)
right = 2(parent) + 1
*/


#include<stdio.h>

#define SIZE 8
#define EMPTY 0

typedef struct{
    int Elem[SIZE];
    int last;
}Heap;

typedef Heap Tree;


void initializeTree(Tree *T);
void displayTree(Tree T);
void populateHeap(Tree *T);
void insert(Tree *T, int num);
void heapSort(Tree *T);
void heapify(Tree *T, int last, int parent);
void swap (int *x, int *y);

int main(){
    Tree T;

    initializeTree(&T);
    populateHeap(&T);
    insert(&T, 60);
    heapSort(&T);
    
    return 0;
}

void displayTree(Tree T){
    int x;
    if(T.last != -1){
        for(x = 0; x<= T.last ; x++){
            printf("%d, ", T.Elem[x]);
        }
        printf("\n");
    } else {
        printf("Heap is Empty\n");
    }
}


void initializeTree(Tree *T){
    int x;
    for(x=0; x<SIZE; x++){
        T->Elem[x] = EMPTY;

    }
    T->last = -1;
}

void populateHeap(Tree *T){
    insert(T, 50);
	insert(T, 30);
	insert(T, 20);
	insert(T, 15);
	insert(T, 10);
	insert(T, 8);
	insert(T, 16);
}

// insert an element at lowest level, swap until x is root and POT property is satisfied
void insert(Tree *T, int num){
    int x, last, parent;
    T->Elem[++T->last] = num;

    if(T->last != EMPTY){
        x = T->last;
        parent = (x-1) /2;
        while( x != EMPTY && num > T->Elem[parent]){ //Swap if the child is bigger than the parent
            T->Elem[x] = T->Elem[parent];
            x = parent;
            parent = (x - 1) / 2;
        }
        T->Elem[x] = num;
    }
}

void heapSort(Tree *T){
    int x;

    for(x = T->last /2 - 1; x >= 0; x--){
        heapify(T, T->last, x);

        for(x= T->last-1; x>=0; x--){
            swap(&T->Elem[0], &T->Elem[x]);
            heapify(T, x, 0);
        }
    }
}

void heapify(Tree *T, int last, int parent){
    int max = parent;
    int leftChild = parent * 2 + 1;
    int rightChild = parent * 2 + 2;

    if(leftChild < last && T->Elem[leftChild] > T->Elem[max]){
        max = leftChild;
    }

    if(rightChild < last && T->Elem[rightChild] > T->Elem[max]){
        max = rightChild;
    }

    if(max != parent){
        swap(&T->Elem[parent], &T->Elem[max]);

        heapify(T, last, parent);
    }
}

void swap (int *x, int *y){
    int temp = *y;
    *y = *x;
    *x = temp;
}